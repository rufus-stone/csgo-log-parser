#pragma once

#include <chrono>
#include <thread>

#include <string>
#include <string_view>
#include <vector>
#include <map>

#include <regex>
#include <ctime>
#include <sstream>
#include <iomanip>

#include <filesystem>
#include <optional>

#include <spdlog/spdlog.h>

#include "nlohmann/json.hpp"
#include "logfile/reader.hpp"

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

static const auto suicide_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" \[-?\d{1,5} -?\d{1,5} -?\d{1,5}\] committed suicide)###", std::regex::optimize};
static const auto blinded_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" blinded for (\d\.\d{2}) by "([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>")###", std::regex::optimize};

static const auto bomb_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Got_The_Bomb|Dropped_The_Bomb|Planted_The_Bomb|Begin_Bomb_Defuse_With(?:out)?_Kit|Defused_The_Bomb)")###", std::regex::optimize};
static const auto hostage_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" triggered "(Touched_A_Hostage|Rescued_A_Hostage|Killed_A_Hostage)")###", std::regex::optimize};

static const auto chicken_rgx = std::regex{R"###("([^<]+)<\d{1,3}><(STEAM[^>]+)><(CT|TERRORIST)>" .+? killed other "chicken.+? with "([^"]+)")###", std::regex::optimize};


using event_t = std::map<std::string, std::string>;
using player_t = std::pair<std::string, std::string>;

using json = nlohmann::json;

class csgoparser
{
private:
  csgoprs::logs::reader log_reader;
  bool simulate;

public:
  json game_state;

  csgoparser() = delete;
  csgoparser(const std::filesystem::path &log_dir, bool simulate = false);
  ~csgoparser() = default;

  uint64_t csgo_dtg_to_epoch_millis(std::string_view dtg);
  std::string csgo_distance_to_metres(std::size_t dist);

  auto parse_event(const std::string &input);
  void track_stats();

  auto parse_base(const std::string &input);
  auto parse_match_start(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_switched_teams(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_game_over(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_attack(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_kill(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_assist(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_blinded(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_suicide(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_bomb(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_hostage(uint64_t epoch, const std::string &input) -> std::optional<json>;
  auto parse_chicken(uint64_t epoch, const std::string &input) -> std::optional<json>;
};

csgoparser::csgoparser(const std::filesystem::path &log_dir, bool test_run) : log_reader(log_dir), game_state(json{}), simulate(simulate) {}

////////////////////////////////////////////////////////////////
uint64_t csgoparser::csgo_dtg_to_epoch_millis(std::string_view dtg)
{
  auto tmt = tm{};
  strptime(dtg.data(), "%m/%d/%Y - %H:%M:%S", &tmt);

  auto epoch_secs = static_cast<uint64_t>(mktime(&tmt));

  return epoch_secs * 1000;
}


////////////////////////////////////////////////////////////////
std::string csgoparser::csgo_distance_to_metres(std::size_t dist)
{
  // According to the Source SDK (https://developer.valvesoftware.com/wiki/Dimensions), in-game distances are
  // measured at 16 grid points per foot. This is equivalent to 16 points per 0.3048 metres, or 52.49343832 points per metre
  // We'll round the result to 2 decimal places

  std::ostringstream ss;
  ss << std::fixed << std::setprecision(2);
  ss << (static_cast<double>(dist) / 52.49343832);

  return ss.str();
}



auto csgoparser::parse_base(const std::string &input)
{
  if (auto base_m = std::smatch{}; std::regex_match(input, base_m, base_rgx))
  {
    auto timestamp = base_m[1].str();
    auto msg = base_m[2].str();

    auto epoch = csgo_dtg_to_epoch_millis(timestamp);

    return std::make_optional(std::make_tuple(epoch, msg));
  } else
  {
    return std::optional<std::tuple<uint64_t, std::string>>{};
  }
}


auto csgoparser::parse_match_start([[maybe_unused]] uint64_t epoch, const std::string &input) -> std::optional<json>
{
  auto event = json{};

  if (auto match_start_m = std::smatch{}; std::regex_match(input, match_start_m, match_start_rgx))
  {
    // Update the game state object
    game_state["game_map"] = match_start_m[1];
    game_state["game_mode"].clear();
    game_state["event_buffer"].clear();
    game_state["teams"]["CT"].clear();
    game_state["teams"]["TERRORIST"].clear();

    return std::make_optional(event);
  }

  // Don't return any actual events yet
  return std::nullopt;
}

auto csgoparser::parse_switched_teams([[maybe_unused]] uint64_t epoch, const std::string &input) -> std::optional<json>
{
  auto event = json{};

  if (auto match = std::smatch{}; std::regex_match(input, match, switched_team_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();

    auto player_json = json{{"player", player}, {"player_id", player_id}};

    // Make sure to remove them from their old team if necessary
    auto other_team = player_team == "CT"s ? "TERRORIST"s : "CT"s;
    auto pos = std::find_if(std::begin(game_state["teams"][other_team]), std::end(game_state["teams"][other_team]), [&player_json](const auto &entry)
    {
      return entry.is_object() && entry == player_json;
    });

    if (pos != std::end(game_state["teams"][other_team]))
    {
      game_state["teams"][other_team].erase(pos);
    }

    // Then add them to their new team - TODO: we should probably just use player ID as key, to allow for player name changes mid-game
    game_state["teams"][player_team].push_back(player_json);

    return std::make_optional(event);
  } else
  {
    return std::nullopt;
  }
}

auto csgoparser::parse_game_over(uint64_t epoch, const std::string &input) -> std::optional<json>
{
  if (auto match = std::smatch{}; std::regex_match(input, match, game_over_rgx))
  {
    auto game_mode = match[1].str();
    auto ct_score = match[2].str();
    auto terrorist_score = match[3].str();
    auto duration = match[4].str();

    game_state["game_mode"] = game_mode;

    json event = {
      {"event_type", "game_over"},
      {"timestamp", epoch},
      {"game_map", game_state["game_map"]},
      {"game_duration", duration}
    };

    game_state["event_buffer"].push_back(event);

    // Now update all the buffered events with the game mode that was just played
    for (auto &buffered_event : game_state["event_buffer"])
    {
      buffered_event["game_mode"] = game_mode;
    }

    // Now add events for winning/losing for each player - ignore Armsrace games as these don't have a winning team and we can calculate Armsrace wins by the total 'knifegg' kills
    // Also, Deathmatch mode doesn't track the winning team for some reason!
    if (game_mode != "gungameprogressive" && game_mode != "deathmatch")
    {
      // Was it a draw?
      if (std::stoi(ct_score) == std::stoi(terrorist_score))
      {
        for (const auto &team : game_state["teams"])
        {
          for (const auto &player : team)
          {
            json draw_event = {
              {"event_type", "draw"},
              {"timestamp", epoch},
              {"player", player["player"]},
              {"player_id", player["player_id"]},
              {"game_map", game_state["game_map"]},
              {"game_mode", game_state["game_mode"]}
            };

            game_state["event_buffer"].push_back(draw_event);
          }
        }
      } else
      {
        auto winning_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "CT"s : "TERRORIST"s;
        auto losing_team = (std::stoi(ct_score) > std::stoi(terrorist_score)) ? "TERRORIST"s : "CT"s;

        // Add the winners
        for (const auto &player : game_state["teams"][winning_team])
        {
          json win_event = {
            {"event_type", "won"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"game_map", game_state["game_map"]},
            {"game_mode", game_state["game_mode"]}
          };

          game_state["event_buffer"].push_back(win_event);
        }

        // Now add the losers
        for (const auto &player : game_state["teams"][losing_team])
        {
          json lose_event = {
            {"event_type", "lost"},
            {"timestamp", epoch},
            {"player", player["player"]},
            {"player_id", player["player_id"]},
            {"game_map", game_state["game_map"]},
            {"game_mode", game_state["game_mode"]}
          };

          game_state["event_buffer"].push_back(lose_event);
        }
      }
      
    }

    // Now that the match is over, return the event buffer (this will get cleared when the next match begins)
    return std::make_optional(game_state["event_buffer"]);
  } else
  {
    return std::nullopt;
  }
}

auto csgoparser::parse_attack([[maybe_unused]] uint64_t epoch, const std::string &input) -> std::optional<json>
{
  auto event = json{};

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

    return std::make_optional(event);
  } else
  {
    return std::nullopt;
  }
}


////////////////////////////////////////////////////////////////
auto csgoparser::parse_event(const std::string &input)
{
  auto base = parse_base(input);
  if (base.has_value())
  {
    auto [epoch, msg] = base.value();

    // Match start - use this to set the current game map
    auto match_start = parse_match_start(epoch, msg);
    if (match_start.has_value())
    {
      auto event = match_start.value();
      return event;
    }

    // Switched teams - use this to track who is on which team
    auto switched_teams = parse_switched_teams(epoch, msg);
    if (switched_teams.has_value())
    {
      auto event = switched_teams.value();
      return event;
    }

    // Game Over - use this to track which game mode was being played, who won the game, and to trigger the dispatch of all events from the now-complete match
    auto game_over = parse_game_over(epoch, msg);
    if (game_over.has_value())
    {
      auto event = game_over.value();
      return event;
    }

    // Attack
    auto attack = parse_attack(epoch, msg);
    if (attack.has_value())
    {
      auto event = attack.value();
      return event;
    }

    /*
    // Kill
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Assist
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Blinded
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Suicide
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Bomb
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Hostage
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }

    // Chicken
    auto kill_m = parse_kill(epoch, msg);
    if (kill_m.has_value())
    {
      auto event = kill_m.value();
      return event;
    }*/
  }

  return nlohmann::json{};
}


////////////////////////////////////////////////////////////////
void csgoparser::track_stats()
{
  using namespace std::literals::chrono_literals;

  std::streamoff offset = 0;

  while (true)
  {
    auto [lines, pos] = this->log_reader.get_latest_bundle(offset);

    if (!lines.empty())
    {
      for (const auto &line : lines)
      {
        auto event_json = this->parse_event(line);

        if (!event_json.is_null())
        {
          spdlog::info(event_json.dump());
        }

        // This is where we'll need to yield the events if possible
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
