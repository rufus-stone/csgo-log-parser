#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

#include <iostream>

#include "catch.hpp"

#include "nlohmann/json.hpp"
#include "csgoparse.hpp"

#include "sample_logs.hpp"

using namespace std::string_literals;

using json = nlohmann::json;


namespace csgoprs::test
{
struct player
{
  std::string player;
  std::string player_id;
};
} // namespace csgoprs::test


auto load_sample_log(std::string_view sample_log) -> std::vector<std::string>
{
  auto sample_logs = std::istringstream{sample_log.data()};
  auto lines = std::vector<std::string>{};
  auto line = std::string{};
  while (std::getline(sample_logs, line))
  {
    lines.push_back(line);
  }

  return lines;
}


TEST_CASE("Game 1", "[competitive][cs_agency]")
{
  // Create a csgoparser with a barebones config
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto config = json::parse(R"###({"log_dir":")###" + std::filesystem::current_path().string() + R"###(", "simulate":true})###");

  auto map_geo = json::parse(csgoprs::geo::default_map_geo);
  auto csgo = csgoprs::csgoparser{config, map_geo};

  // Load in the sample logs - these simulate a complete competitive match on cs_agency
  auto lines = load_sample_log(csgoprs::log_samples::competitive_cs_agency);

  // Play back the logs and parse the events
  std::size_t i = 0;
  for (auto const &log_line : lines)
  {
    csgo.parse_event(log_line);
  }

  // Check the game map and mode were correctly identified
  REQUIRE(csgo.game_state["game_map"] == "cs_agency");
  REQUIRE(csgo.game_state["game_mode"] == "competitive");

  // Lambda to check if a given player is on a given team
  auto is_member_of_team = [&csgo](auto const &player, auto const &team) -> bool
  {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member)
    {
      return team_member["player"] == player;
    });

    return (pos != std::end(csgo.game_state["teams"][team]));
  };

  // Were the team members correctly identified?
  REQUIRE(is_member_of_team("Dean", "CT") == true);
  REQUIRE(is_member_of_team("James", "CT") == true);
  REQUIRE(is_member_of_team("Sam", "CT") == true);

  REQUIRE(is_member_of_team("Alice", "TERRORIST") == true);
  REQUIRE(is_member_of_team("Bob", "TERRORIST") == true);
  REQUIRE(is_member_of_team("Mark", "TERRORIST") == true);

  // Was the timestamp of the final event correctly identified?
  REQUIRE(csgo.game_state["event_buffer"][csgo.game_state["event_buffer"].size() - 1]["timestamp"] == 1588629767000);

  // Was the losing team correctly identified?
  REQUIRE(csgo.game_state["event_buffer"][csgo.game_state["event_buffer"].size() - 1]["event_type"] == "lost");
  REQUIRE(csgo.game_state["event_buffer"][csgo.game_state["event_buffer"].size() - 1]["player_team"] == "TERRORIST");
}



SCENARIO("Geo tests", "[geo][cs_agency][de_dust2]")
{
  GIVEN("A game played on cs_agency")
  {
    auto const map_origin = csgoprs::geo::point{-2947.0, 2492.0};
    auto const map_scale  = 5.0;

    WHEN(" a player is located at grid position -1290.0,-708.0")
    {
      auto const player_pos = csgoprs::geo::point{-1290.0, -708.0};

      THEN(" their lat/lon coordinates are approximately 40.97990,-63.49219")
      {
        auto const [lat, lon] = csgoprs::geo::xy_to_lat_lon(player_pos, map_origin, map_scale);

        REQUIRE(lat == Approx(40.98).margin(0.01));
        REQUIRE(lon == Approx(-63.49).margin(0.01));
      }
    }
  }

  GIVEN("A game played on de_dust2")
  {
    auto const map_origin = csgoprs::geo::point{-2476.0, 3239.0};
    auto const map_scale  = 4.4;

    WHEN(" a player is located at grid position 1139.0,891.0")
    {
      auto const player_pos = csgoprs::geo::point{1139.0, 891.0};

      THEN(" their lat/lon coordinates are approximately 7.58429,108.84055")
      {
        auto const [lat, lon] = csgoprs::geo::xy_to_lat_lon(player_pos, map_origin, map_scale);

        REQUIRE(lat == Approx(7.58).margin(0.01));
        REQUIRE(lon == Approx(108.84).margin(0.01));
      }
    }
  }
}