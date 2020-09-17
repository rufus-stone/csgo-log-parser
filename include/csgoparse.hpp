#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <regex>

#include <spdlog/spdlog.h>

#include "nlohmann/json.hpp"
#include "logfile/reader.hpp"

#include "utils.hpp"


namespace csgoprs
{

using namespace std::string_literals;

// Build regex like this: std::regex{R"###(actual regex goes here)###", std::regex::optimize};
static const auto base_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): (.+)$)###", std::regex::optimize};

static const auto match_start_rgx = std::regex{R"###(World triggered "Match_Start" on "([^"]+)")###", std::regex::optimize};
static const auto game_over_rgx = std::regex{R"###(Game Over: ([^\s]+).+?score (\d+):(\d+) after (\d+) min)###", std::regex::optimize};

static const auto switched_team_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)>" switched from team <(?:Unassigned|CT|TERRORIST)> to <(CT|TERRORIST)>)###", std::regex::optimize};

static const auto attack_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] attacked "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] with "([^"]+)" \(damage "(\d+)"\) \(damage_armor "(\d+)"\) \(health "(\d+)"\) \(armor "(\d+)"\) \(hitgroup "([^"]+)"\))###", std::regex::optimize};
static const auto killed_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] killed "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] with "([^"]+)"(?: \(([^)]+)\))?)###", std::regex::optimize};
static const auto assist_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" assisted killing "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>")###", std::regex::optimize};

static const auto suicide_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[-?\d{1,5} -?\d{1,5} -?\d{1,5}\] committed suicide with "[a-zA-Z0-9]{1,20}")###", std::regex::optimize};
static const auto blinded_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" blinded for (\d\.\d{2}) by "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" from flashbang entindex [0-9\s]{1,5})###", std::regex::optimize};

static const auto bomb_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Got_The_Bomb|Dropped_The_Bomb|Planted_The_Bomb|Begin_Bomb_Defuse_With(?:out)?_Kit|Defused_The_Bomb)")###", std::regex::optimize};
static const auto hostage_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Touched_A_Hostage|Rescued_A_Hostage|Killed_A_Hostage)")###", std::regex::optimize};

static const auto chicken_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" .+? killed other "chicken.+? with "([^"]+)")###", std::regex::optimize};


////////////////////////////////////////////////////////////////
using json = nlohmann::json;

class csgoparser
{
private:
  const json config;
  const csgoprs::logs::reader log_reader;
  const bool simulate;

public:
  json game_state;

  csgoparser() = delete;
  csgoparser(const json &cfg);
  ~csgoparser() = default;

  auto translate_steam_id(const std::string &input) -> std::string;

  auto parse_base(const std::string &input);
  auto parse_match_start(const std::string &input) -> bool;
  auto parse_switched_teams(const std::string &input) -> bool;
  auto parse_attack(uint64_t epoch, const std::string &input) -> bool;
  auto parse_kill(uint64_t epoch, const std::string &input) -> bool;
  auto parse_assist(uint64_t epoch, const std::string &input) -> bool;
  auto parse_blinded(uint64_t epoch, const std::string &input) -> bool;
  auto parse_suicide(uint64_t epoch, const std::string &input) -> bool;
  auto parse_bomb(uint64_t epoch, const std::string &input) -> bool;
  auto parse_hostage(uint64_t epoch, const std::string &input) -> bool;
  auto parse_chicken(uint64_t epoch, const std::string &input) -> bool;
  auto parse_game_over(uint64_t epoch, const std::string &input) -> json;

  auto parse_event(const std::string &input) -> json;
  void track_stats();
};

////////////////////////////////////////////////////////////////
csgoparser::csgoparser(const json &cfg) : config(cfg), log_reader(config["log_dir"].get<std::string>()), game_state(json{}), simulate(config["simulate"].get<bool>())
{
  spdlog::info("Active config:\n{}", config.dump(2));
}


////////////////////////////////////////////////////////////////
auto csgoparser::translate_steam_id(const std::string &input) -> std::string
{
  if (this->config["steam_id_translation"]["translations"].contains(input))
  {
    return this->config["steam_id_translation"]["translations"][input].get<std::string>();
  } else
  {
    return input;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_base(const std::string &input)
{
  if (auto base_m = std::smatch{}; std::regex_match(input, base_m, base_rgx))
  {
    const auto timestamp = base_m[1].str();
    const auto msg = base_m[2].str();

    const auto epoch = csgoprs::dtg_to_epoch_millis(timestamp);

    return std::make_optional(std::make_tuple(epoch, msg));
  } else
  {
    return std::optional<std::tuple<uint64_t, std::string>>{};
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_match_start(const std::string &input) -> bool
{
  if (auto match_start_m = std::smatch{}; std::regex_match(input, match_start_m, match_start_rgx))
  {
    // Update the game state object
    this->game_state["game_map"] = match_start_m[1];
    this->game_state["game_mode"].clear();
    this->game_state["event_buffer"].clear();
    this->game_state["teams"]["CT"].clear();
    this->game_state["teams"]["TERRORIST"].clear();

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_switched_teams(const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, switched_team_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();

    const auto player_json = json{{"player", player}, {"player_id", player_id}};

    // Make sure to remove them from their old team if necessary
    const auto other_team = player_team == "CT"s ? "TERRORIST"s : "CT"s;
    const auto pos = std::find_if(std::begin(this->game_state["teams"][other_team]), std::end(this->game_state["teams"][other_team]), [&player_json](const auto &entry) {
      return entry.is_object() && entry == player_json;
    });

    if (pos != std::end(this->game_state["teams"][other_team]))
    {
      this->game_state["teams"][other_team].erase(pos);
    }

    // Then add them to their new team - TODO: we should probably just use player ID as key, to allow for player name changes mid-game
    this->game_state["teams"][player_team].push_back(player_json);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_attack(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, attack_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto player_pos = match[4].str();
    auto victim = match[5].str();
    auto victim_id = match[6].str();
    auto victim_team = match[7].str();
    auto victim_pos = match[8].str();
    auto weapon = match[9].str();
    auto damage_health = match[10].str();
    auto damage_armor = match[11].str();
    auto health_remaining = match[12].str();
    auto armor_remaining = match[13].str();
    auto hitgroup = match[14].str();

    json event = {
      {"event_type", "attack"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"player_position", "TODO"}, // maputils.project_coordinates(pos=np.asarray(p_pos[:2]), game_map=game.map)
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"victim_position", "TODO"}, // maputils.project_coordinates(pos=np.asarray(v_pos[:2]), game_map=game.map)
      {"distance", csgoprs::metres_between_points(player_pos, victim_pos)},
      {"weapon", weapon},
      {"damage_health", damage_health},
      {"damage_armor", damage_armor},
      {"health_remaining", health_remaining},
      {"armor_remaining", armor_remaining},
      {"bodypart_hit", hitgroup},
      {"game_map", this->game_state["game_map"]}};

    // Was it self-inflicted?
    if (player_id == victim_id)
    {
      event["self_inflicted"] = "true";
    }

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_kill(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, killed_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto player_pos = match[4].str();
    auto victim = match[5].str();
    auto victim_id = match[6].str();
    auto victim_team = match[7].str();
    auto victim_pos = match[8].str();
    auto weapon = match[9].str();
    auto flair = match[10].str();

    json event = {
      {"event_type", "kill"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"player_position", "TODO"}, // maputils.project_coordinates(pos=np.asarray(p_pos[:2]), game_map=game.map)
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"victim_position", "TODO"}, // maputils.project_coordinates(pos=np.asarray(v_pos[:2]), game_map=game.map)
      {"distance", csgoprs::metres_between_points(player_pos, victim_pos)},
      {"weapon", weapon},
      {"game_map", this->game_state["game_map"]}};
    
    // Add on any flair (noscope, headshot, revenge, etc.)
    if (!flair.empty())
    {
      if (flair.find("headshot") != std::string::npos)
      {
        event["bodypart_hit"] = "head";
      }

      event["flair"] = flair;
    }

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_assist(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, assist_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto victim = match[4].str();
    auto victim_id = match[5].str();
    auto victim_team = match[6].str();

    json event = {
      {"event_type", "assist"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_suicide(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, suicide_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();

    json event = {
      {"event_type", "suicide"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_blinded(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, blinded_rgx))
  {
    auto victim = match[1].str();
    auto victim_id = match[2].str();
    auto victim_team = match[3].str();
    auto duration = match[4].str();
    auto player = match[5].str();
    auto player_id = match[6].str();
    auto player_team = match[7].str();

    json event = {
      {"event_type", "blinded"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"blinded", duration},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_bomb(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, bomb_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto bomb_action = match[4].str();

    json event = {
      {"event_type", bomb_action},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_hostage(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, hostage_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto hostage_action = match[4].str();

    json event = {
      {"event_type", hostage_action},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_chicken(uint64_t epoch, const std::string &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, chicken_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();
    auto weapon = match[4].str();

    json event = {
      {"event_type", "chicken"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"weapon", weapon},
      {"game_map", this->game_state["game_map"]}};

    // Add event to the event buffer
    this->game_state["event_buffer"].push_back(event);

    return true;
  } else
  {
    return false;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_game_over(uint64_t epoch, const std::string &input) -> json
{
  if (auto match = std::smatch{}; std::regex_match(input, match, game_over_rgx))
  {
    const auto game_mode = match[1].str();
    const auto ct_score = match[2].str();
    const auto terrorist_score = match[3].str();
    const auto duration = match[4].str();

    this->game_state["game_mode"] = game_mode;

    json event = {
      {"event_type", "game_over"},
      {"timestamp", epoch},
      {"game_map", this->game_state["game_map"]},
      {"game_duration", duration}};

    this->game_state["event_buffer"].push_back(event);

    // Now add events for winning/losing for each player - ignore Armsrace games as these don't have a winning team and we can calculate Armsrace wins by the total 'knifegg' kills
    // Also, Deathmatch mode doesn't track the winning team for some reason!
    if (game_mode != "gungameprogressive" && game_mode != "deathmatch")
    {
      // Was it a draw?
      if (std::stoi(ct_score) == std::stoi(terrorist_score))
      {
        for (const auto &team : this->game_state["teams"])
        {
          for (const auto &player : team)
          {
            json draw_event = {
              {"event_type", "draw"},
              {"timestamp", epoch},
              {"player", player["player"]},
              {"player_id", player["player_id"]},
              {"game_map", this->game_state["game_map"]}};

            this->game_state["event_buffer"].push_back(draw_event);
          }
        }
      } else
      {
        const auto winning_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "CT"s : "TERRORIST"s;
        const auto losing_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "TERRORIST"s : "CT"s;

        // Add the winners
        for (const auto &player : this->game_state["teams"][winning_team])
        {
          json win_event = {
            {"event_type", "won"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"game_map", this->game_state["game_map"]}};

          this->game_state["event_buffer"].push_back(win_event);
        }

        // Now add the losers
        for (const auto &player : this->game_state["teams"][losing_team])
        {
          json lose_event = {
            {"event_type", "lost"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"game_map", this->game_state["game_map"]}};

          this->game_state["event_buffer"].push_back(lose_event);
        }
      }
    }

    // Now update all the buffered events with the game mode that was just played, and perform any Steam ID -> Name translations (if enabled)
    for (auto &buffered_event : this->game_state["event_buffer"])
    {
      buffered_event["game_mode"] = game_mode;

      // Perform Steam ID translations
      if (this->config["steam_id_translation"]["active"])
      {
        if (buffered_event.contains("player_id"))
        {
          buffered_event["player_id"] = this->translate_steam_id(buffered_event["player_id"].get<std::string>());
        }

        if (buffered_event.contains("victim_id"))
        {
          buffered_event["victim_id"] = this->translate_steam_id(buffered_event["victim_id"].get<std::string>());
        }
      }
    }

    // Now that the match is over, return the event buffer (this will get cleared when the next match begins)
    return this->game_state["event_buffer"];
  } else
  {
    return json{};
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_event(const std::string &input) -> json
{
  auto base = parse_base(input);
  if (base.has_value())
  {
    const auto [epoch, msg] = base.value();

    // Match start - use this to set the current game map
    if (parse_match_start(msg))
    {
      return json{};
    }

    // Switched teams - use this to track who is on which team
    if (parse_switched_teams(msg))
    {
      return json{};
    }

    // Attack
    if (parse_attack(epoch, msg))
    {
      return json{};
    }

    // Kill
    if (parse_kill(epoch, msg))
    {
      return json{};
    }

    // Assist
    if (parse_assist(epoch, msg))
    {
      return json{};
    }

    // Suicide
    if (parse_suicide(epoch, msg))
    {
      return json{};
    }

    // Blinded
    if (parse_blinded(epoch, msg))
    {
      return json{};
    }

    // Bomb
    if (parse_bomb(epoch, msg))
    {
      return json{};
    }

    // Hostage
    if (parse_hostage(epoch, msg))
    {
      return json{};
    }

    // Chicken
    if (parse_chicken(epoch, msg))
    {
      return json{};
    }

    // Game Over - use this to track which game mode was being played, who won the game, and to trigger the dispatch of all events from the now-complete match
    auto game_over = parse_game_over(epoch, msg);
    if (!game_over.is_null())
    {
      return game_over;
    }
  } else
  {
    return json{};
  }
}


////////////////////////////////////////////////////////////////
void csgoparser::track_stats()
{
  using namespace std::literals::chrono_literals;

  std::streamoff offset = 0;

  while (true)
  {
    const auto [lines, pos] = this->log_reader.get_latest_bundle(offset);

    if (!lines.empty())
    {
      for (const auto &line : lines)
      {
        auto events = this->parse_event(line);

        // parse_event() should only ever return actual events when a match ends, and this should be in the form of a JSON array
        if (!events.is_null() && events.is_array())
        {
          for (auto &event : events)
          {
            if (!event.is_null())
            {
              // This is where we'll need to dispatch the events if possible
              spdlog::info(event.dump());
            }
          }
        }
      }
    }

    offset = pos;

    spdlog::info("All caught up...");
    std::exit(EXIT_SUCCESS);

    // Wait for a few seconds to avoid hammering the CPU
    std::this_thread::sleep_for(3s);
  }
}

} // namespace csgoprs
