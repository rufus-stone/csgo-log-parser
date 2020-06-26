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

#include <optional>

#include "json.hpp"
#include "logfile/reader.hpp"

namespace csgoprs
{

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


struct game_state_t
{
  std::map<std::string, std::vector<player_t>> teams;
  std::string map;
  std::vector<event_t> event_buffer;

  friend std::ostream& operator<<(std::ostream &os, game_state_t &game_state);
};

std::ostream& operator<<(std::ostream &os, game_state_t &game_state)
{
  //os << 
  return os;
}


class csgoparser
{
private:
  csgoprs::logs::reader log_reader;

public:
  game_state_t game_state;

  csgoparser() = delete;
  csgoparser(const std::filesystem::path &log_dir);
  ~csgoparser() = default;

  uint64_t csgo_dtg_to_epoch_millis(std::string_view dtg);
  std::string csgo_distance_to_metres(std::size_t dist);

  std::optional<event_t> parse_event(const std::string &input);
  void track_stats();

  auto parse_base(const std::string &input);
  auto parse_match_start(const std::string &input);
  auto parse_switched_teams(const std::string &input);
  auto parse_game_over(const std::string &input);
  auto parse_attack(const std::string &input);
  auto parse_kill(const std::string &input);
  auto parse_assist(const std::string &input);
  auto parse_blinded(const std::string &input);
  auto parse_suicide(const std::string &input);
  auto parse_bomb(const std::string &input);
  auto parse_hostage(const std::string &input);
  auto parse_chicken(const std::string &input);
};

csgoparser::csgoparser(const std::filesystem::path &log_dir) : log_reader(log_dir), game_state(game_state_t{}) {}

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
  ss << (dist / 52.49343832);

  return ss.str();
}




auto csgoparser::parse_base(const std::string &input)
{
  auto base_m = std::smatch{};
  if (std::regex_match(input, base_m, base_rgx))
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

auto csgoparser::parse_match_start(const std::string &input)
{
  auto match = std::smatch{};
  if (std::regex_match(input, match, match_start_rgx))
  {
    auto map = match[1].str();

    return std::make_optional(std::make_tuple(map));
  } else
  {
    return std::optional<std::tuple<std::string>>{};
  }
}

auto csgoparser::parse_switched_teams(const std::string &input)
{
  auto match = std::smatch{};
  if (std::regex_match(input, match, switched_team_rgx))
  {
    auto player = match[1].str();
    auto player_id = match[2].str();
    auto player_team = match[3].str();

    return std::make_optional(std::make_tuple(player, player_id, player_team));
  } else
  {
    return std::optional<std::tuple<std::string, std::string, std::string>>{};
  }
}

auto csgoparser::parse_game_over(const std::string &input)
{
  auto match = std::smatch{};
  if (std::regex_match(input, match, game_over_rgx))
  {
    auto game_mode = match[1].str();
    auto ct_score = match[2].str();
    auto terrorist_score = match[3].str();
    auto duration = match[4].str();

    return std::make_optional(std::make_tuple(game_mode, ct_score, terrorist_score, duration));
  } else
  {
    return std::optional<std::tuple<std::string, std::string, std::string, std::string>>{};
  }
}

auto csgoparser::parse_attack(const std::string &input)
{
  auto match = std::smatch{};
  if (std::regex_match(input, match, attack_rgx))
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

    return std::make_optional(std::make_tuple(player, player_id));
  } else
  {
    return std::optional<std::tuple<std::string, std::string>>{};
  }
}


////////////////////////////////////////////////////////////////
std::optional<event_t> csgoparser::parse_event(const std::string &input)
{
  if (parse_base(input).has_value())
  {
    auto [epoch, msg] = parse_base(input).value();
    std::cout << "Epoch:: " << epoch << '\n';

    // Match start - use this to set the current game map
    auto match_start_m = std::smatch{};
    if (std::regex_match(msg, match_start_m, match_start_rgx))
    {
      // Update the game state object
      std::cout << "Starting match on: " << match_start_m[1] << '\n';
      game_state.map = match_start_m[1];

      // Don't return any events just yet
      return std::nullopt;
    }
  }

  return std::nullopt;
}


////////////////////////////////////////////////////////////////
void csgoparser::track_stats()
{
  using namespace std::literals::chrono_literals;

  int offset = 0;

  while (true)
  {
    auto [lines, pos] = this->log_reader.get_latest_bundle(offset);

    if (!lines.empty())
    {
      for (const auto &line : lines)
      {
        auto e = this->parse_event(line);

        // This is where we'll need to yield the events if possible
      }
    }

    offset = pos;

    // Wait for a few seconds to avoid hammering the CPU
    std::this_thread::sleep_for(3s);
  }
}

} // namespace csgoprs
