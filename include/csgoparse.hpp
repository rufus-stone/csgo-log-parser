#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <regex>

#include <spdlog/spdlog.h>
#include <hamarr/crypto.hpp>

#include "nlohmann/json.hpp"
#include "logfile/reader.hpp"

#include "utils.hpp"
#include "geo.hpp"


namespace csgoprs
{

using namespace std::string_literals;

// Build regex like this: std::regex{R"###(actual regex goes here)###", std::regex::optimize};
static auto const base_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): (.+)$)###", std::regex::optimize};

static auto const match_start_rgx = std::regex{R"###(^L \d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}: World triggered "Match_Start" on "([^"]+)")###", std::regex::optimize};
static auto const game_over_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): Game Over: ([^\s]+).+?score (\d+):(\d+) after (\d+) min)###", std::regex::optimize};

static auto const switched_team_rgx = std::regex{R"###(^L \d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}: "([^<]+)<\d{1,3}><(STEAM[^>]+)>" switched from team <(?:Unassigned|CT|TERRORIST)> to <(CT|TERRORIST)>)###", std::regex::optimize};

static auto const attack_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] attacked "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] with "([^"]+)" \(damage "(\d+)"\) \(damage_armor "(\d+)"\) \(health "(\d+)"\) \(armor "(\d+)"\) \(hitgroup "([^"]+)"\))###", std::regex::optimize};
static auto const killed_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] killed "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[(-?\d{1,5} -?\d{1,5} -?\d{1,5})\] with "([^"]+)"(?: \(([^)]+)\))?)###", std::regex::optimize};
static auto const assist_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" assisted killing "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>")###", std::regex::optimize};

static auto const suicide_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[-?\d{1,5} -?\d{1,5} -?\d{1,5}\] committed suicide with "[a-zA-Z0-9]{1,20}")###", std::regex::optimize};
static auto const blinded_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" blinded for (\d\.\d{2}) by "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" from flashbang entindex [0-9\s]{1,5})###", std::regex::optimize};

static auto const bomb_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Got_The_Bomb|Dropped_The_Bomb|Planted_The_Bomb|Begin_Bomb_Defuse_With(?:out)?_Kit|Defused_The_Bomb)")###", std::regex::optimize};
static auto const hostage_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Touched_A_Hostage|Rescued_A_Hostage|Killed_A_Hostage)")###", std::regex::optimize};

static auto const chicken_rgx = std::regex{R"###(^L (\d{2}/\d{2}/\d{4} - \d{2}:\d{2}:\d{2}): "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" .+? killed other "chicken.+? with "([^"]+)")###", std::regex::optimize};


////////////////////////////////////////////////////////////////
using json = nlohmann::json;

class csgoparser
{
private:
  const json config;
  const json maps;
  const csgoprs::logs::reader log_reader;
  const bool simulate;

public:
  json game_state;

  csgoparser() = delete;
  csgoparser(const json &cfg, const json &geo);
  ~csgoparser() = default;

  auto translate_steam_id(std::string const &input) -> std::string;

  auto parse_match_start(std::string const &input) -> bool;
  auto parse_switched_teams(std::string const &input) -> bool;
  auto parse_attack(std::string const &input) -> bool;
  auto parse_kill(std::string const &input) -> bool;
  auto parse_assist(std::string const &input) -> bool;
  auto parse_blinded(std::string const &input) -> bool;
  auto parse_suicide(std::string const &input) -> bool;
  auto parse_bomb(std::string const &input) -> bool;
  auto parse_hostage(std::string const &input) -> bool;
  auto parse_chicken(std::string const &input) -> bool;
  auto parse_game_over(std::string const &input) -> json;

  auto parse_event(std::string const &input) -> json;
  void track_stats();
};

////////////////////////////////////////////////////////////////
csgoparser::csgoparser(const json &cfg, const json &geo) : config(cfg), maps(geo), log_reader(config["log_dir"].get<std::string>()), game_state(json{}), simulate(config["simulate"].get<bool>())
{
  spdlog::info("Active config:\n{}", config.dump(2));
}


////////////////////////////////////////////////////////////////
auto csgoparser::translate_steam_id(std::string const &input) -> std::string
{
  if (this->config["steam_id_translation"]["translations"].contains(input))
  {
    //return hmr::crypto::md5(input);
    return this->config["steam_id_translation"]["translations"][input].get<std::string>();
  } else
  {
    return input;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_match_start(std::string const &input) -> bool
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
auto csgoparser::parse_switched_teams(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, switched_team_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();

    auto const player_json = json{{"player", player}, {"player_id", player_id}};

    // Make sure to remove them from their old team if necessary
    auto const other_team = player_team == "CT"s ? "TERRORIST"s : "CT"s;
    auto const pos = std::find_if(std::begin(this->game_state["teams"][other_team]), std::end(this->game_state["teams"][other_team]), [&player_json](auto const &entry) {
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
auto csgoparser::parse_attack(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, attack_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto player_pos = match[5].str();
    auto victim = match[6].str();
    auto victim_id = match[7].str();
    auto victim_team = match[8].str();
    auto victim_pos = match[9].str();
    auto weapon = match[10].str();
    auto damage_health = match[11].str();
    auto damage_armor = match[12].str();
    auto health_remaining = match[13].str();
    auto armor_remaining = match[14].str();
    auto hitgroup = match[15].str();

    json event = {
      {"event_type", "attack"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"player_position", csgoprs::geo::pos_to_lat_lon(player_pos, this->game_state["game_map"].get<std::string>(), this->maps)},
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"victim_position", csgoprs::geo::pos_to_lat_lon(victim_pos, this->game_state["game_map"].get<std::string>(), this->maps)},
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
auto csgoparser::parse_kill(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, killed_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto player_pos = match[5].str();
    auto victim = match[6].str();
    auto victim_id = match[7].str();
    auto victim_team = match[8].str();
    auto victim_pos = match[9].str();
    auto weapon = match[10].str();
    auto flair = match[11].str();

    json event = {
      {"event_type", "kill"},
      {"timestamp", epoch},
      {"player", player},
      {"player_id", player_id},
      {"player_team", player_team},
      {"player_position", csgoprs::geo::pos_to_lat_lon(player_pos, this->game_state["game_map"].get<std::string>(), this->maps)},
      {"victim", victim},
      {"victim_id", victim_id},
      {"victim_team", victim_team},
      {"victim_position", csgoprs::geo::pos_to_lat_lon(victim_pos, this->game_state["game_map"].get<std::string>(), this->maps)},
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
auto csgoparser::parse_assist(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, assist_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto victim = match[5].str();
    auto victim_id = match[6].str();
    auto victim_team = match[7].str();

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
auto csgoparser::parse_suicide(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, suicide_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();

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
auto csgoparser::parse_blinded(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, blinded_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto victim = match[2].str();
    auto victim_id = match[3].str();
    auto victim_team = match[4].str();
    auto duration = match[5].str();
    auto player = match[6].str();
    auto player_id = match[7].str();
    auto player_team = match[8].str();

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
auto csgoparser::parse_bomb(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, bomb_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto bomb_action = match[5].str();

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
auto csgoparser::parse_hostage(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, hostage_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto hostage_action = match[5].str();

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
auto csgoparser::parse_chicken(std::string const &input) -> bool
{
  if (auto match = std::smatch{}; std::regex_match(input, match, chicken_rgx))
  {
    auto epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto player = match[2].str();
    auto player_id = match[3].str();
    auto player_team = match[4].str();
    auto weapon = match[5].str();

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
auto csgoparser::parse_game_over(std::string const &input) -> json
{
  if (auto match = std::smatch{}; std::regex_match(input, match, game_over_rgx))
  {
    auto const epoch = csgoprs::dtg_to_epoch_millis(match[1].str());
    auto const game_mode = match[2].str();
    auto const ct_score = match[3].str();
    auto const terrorist_score = match[4].str();
    auto const duration = match[5].str();

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
        for (auto const &team : this->game_state["teams"])
        {
          for (auto const &player : team)
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
        auto const winning_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "CT"s : "TERRORIST"s;
        auto const losing_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "TERRORIST"s : "CT"s;

        // Add the winners
        for (auto const &player : this->game_state["teams"][winning_team])
        {
          json win_event = {
            {"event_type", "won"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"player_team", winning_team},
            {"game_map", this->game_state["game_map"]}};

          this->game_state["event_buffer"].push_back(win_event);
        }

        // Now add the losers
        for (auto const &player : this->game_state["teams"][losing_team])
        {
          json lose_event = {
            {"event_type", "lost"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"player_team", losing_team},
            {"game_map", this->game_state["game_map"]}};

          this->game_state["event_buffer"].push_back(lose_event);
        }
      }
    }

    // Now update all the buffered events with the game mode that was just played, and perform any Steam ID -> Name translations (if enabled)
    bool const translate = this->config.contains("steam_id_translation") && this->config["steam_id_translation"]["active"] ? true : false;

    for (auto &buffered_event : this->game_state["event_buffer"])
    {
      buffered_event["game_mode"] = game_mode;

      // Perform Steam ID translations
      if (translate)
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
auto csgoparser::parse_event(std::string const &input) -> json
{
  // Match start - use this to set the current game map
  if (parse_match_start(input))
  {
    return json{};
  }

  // Switched teams - use this to track who is on which team
  if (parse_switched_teams(input))
  {
    return json{};
  }

  // Attack
  if (parse_attack(input))
  {
    return json{};
  }

  // Kill
  if (parse_kill(input))
  {
    return json{};
  }

  // Assist
  if (parse_assist(input))
  {
    return json{};
  }

  // Suicide
  if (parse_suicide(input))
  {
    return json{};
  }

  // Blinded
  if (parse_blinded(input))
  {
    return json{};
  }

  // Bomb
  if (parse_bomb(input))
  {
    return json{};
  }

  // Hostage
  if (parse_hostage(input))
  {
    return json{};
  }

  // Chicken
  if (parse_chicken(input))
  {
    return json{};
  }

  // Game Over - use this to track which game mode was being played, who won the game, and to trigger the dispatch of all events from the now-complete match
  auto game_over = parse_game_over(input);
  if (!game_over.is_null())
  {
    return game_over;
  }

  // Or did nothing match?
  return json{};
}


////////////////////////////////////////////////////////////////
void csgoparser::track_stats()
{
  using namespace std::literals::chrono_literals;

  std::streamoff offset = 0;

  while (true)
  {
    auto const [lines, pos] = this->log_reader.get_latest_bundle(offset);

    if (!lines.empty())
    {
      for (auto const &line : lines)
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

    // Wait for a few seconds to avoid hammering the CPU
    std::this_thread::sleep_for(3s);
  }
}

} // namespace csgoprs
