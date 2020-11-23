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


////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////
TEST_CASE("Standard Config", "[competitive][cs_agency]")
{
  // Create a csgoparser with a barebones config
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto config = json::parse(R"({"log_dir":")" + std::filesystem::current_path().string() + R"(", "simulate":true})");

  auto map_geo = json::parse(csgoprs::geo::default_map_geo);
  auto csgo = csgoprs::csgoparser{config, map_geo};

  // Load in the sample logs - these simulate a complete competitive match on cs_agency
  auto lines = load_sample_log(csgoprs::log_samples::competitive_cs_agency);

  // Play back the logs and parse the events
  for (auto const &log_line : lines)
  {
    csgo.parse_event(log_line);
  }

  // Check the game map and mode were correctly identified
  REQUIRE(csgo.game_state["game_map"] == "cs_agency");
  REQUIRE(csgo.game_state["game_mode"] == "competitive");

  // Lambda to check if a given player is on a given team
  auto is_member_of_team = [&csgo](auto const &player, auto const &team) -> bool {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member) {
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


////////////////////////////////////////////////////////////////
TEST_CASE("Steam ID -> Hash translation", "[competitive][cs_agency]")
{
  // Create a csgoparser with a barebones config, configured to do Steam ID translation using MD5 hashes
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto const config_text = R"(
    {
      "log_dir": "",
      "simulate": true,
      "steam_id_translation": {
        "active": true,
        "hash": "md5"
      }
    }
  )"s;

  auto config = json::parse(config_text);
  config["log_dir"] = std::filesystem::current_path().string();

  auto map_geo = json::parse(csgoprs::geo::default_map_geo);
  auto csgo = csgoprs::csgoparser{config, map_geo};

  // Load in the sample logs - these simulate a complete competitive match on cs_agency
  auto lines = load_sample_log(csgoprs::log_samples::competitive_cs_agency);

  // Play back the logs and parse the events
  for (auto const &log_line : lines)
  {
    csgo.parse_event(log_line);
  }

  // Lambda to check the player_id for a given player
  auto player_id_for_player_on_team = [&csgo](auto const &player, auto const &team) -> json {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member) {
      return team_member["player"] == player;
    });

    return (pos != std::end(csgo.game_state["teams"][team]) ? (*pos)["player_id"] : json{});
  };

  // Check the Steam ID -> hash translation worked
  REQUIRE(player_id_for_player_on_team("Dean", "CT") == "9760941ecf292eb309f2c360bbd198ba");  // STEAM_1:1:00000004
  REQUIRE(player_id_for_player_on_team("James", "CT") == "db65f3c28323f569abba7f49332f075d"); // STEAM_1:0:00000005
  REQUIRE(player_id_for_player_on_team("Sam", "CT") == "09932be4550c7f202b78869d15952ac7");   // STEAM_1:0:00000003

  REQUIRE(player_id_for_player_on_team("Alice", "TERRORIST") == "7f0d8cfacb69cb2660794801a571c504"); // STEAM_1:1:00000001
  REQUIRE(player_id_for_player_on_team("Bob", "TERRORIST") == "07f668c1c0ac558a29436925122167f3");   // STEAM_1:0:00000002
  REQUIRE(player_id_for_player_on_team("Mark", "TERRORIST") == "b13a60171d9a5617358d17b2ef2d8291");  // STEAM_1:1:00000006
}


////////////////////////////////////////////////////////////////
TEST_CASE("Steam ID -> Name translation", "[competitive][cs_agency]")
{
  // Create a csgoparser with a barebones config, configured to do Steam ID -> Name translations
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto const config_text = R"(
    {
      "log_dir": "",
      "simulate": true,
      "steam_id_translation": {
        "active": true,
        "translations": {
          "STEAM_1:1:00000004": "Dean Alternative",
          "STEAM_1:0:00000005": "James Alternative",
          "STEAM_1:0:00000003": "Sam Alternative",
          "STEAM_1:1:00000001": "Alice Alternative",
          "STEAM_1:0:00000002": "Bob Alternative",
          "STEAM_1:1:00000006": "Mark Alternative"
        }
      }
    }
  )"s;

  auto config = json::parse(config_text);
  config["log_dir"] = std::filesystem::current_path().string();

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

  // Lambda to check the player_id for a given player
  auto player_id_for_player_on_team = [&csgo](auto const &player, auto const &team) -> json {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member) {
      return team_member["player"] == player;
    });

    return (pos != std::end(csgo.game_state["teams"][team]) ? (*pos)["player_id"] : json{});
  };

  // Check the Steam ID -> Name translation worked
  REQUIRE(player_id_for_player_on_team("Dean", "CT") == "Dean Alternative");   // STEAM_1:1:00000004
  REQUIRE(player_id_for_player_on_team("James", "CT") == "James Alternative"); // STEAM_1:0:00000005
  REQUIRE(player_id_for_player_on_team("Sam", "CT") == "Sam Alternative");     // STEAM_1:0:00000003

  REQUIRE(player_id_for_player_on_team("Alice", "TERRORIST") == "Alice Alternative"); // STEAM_1:1:00000001
  REQUIRE(player_id_for_player_on_team("Bob", "TERRORIST") == "Bob Alternative");     // STEAM_1:0:00000002
  REQUIRE(player_id_for_player_on_team("Mark", "TERRORIST") == "Mark Alternative");   // STEAM_1:1:00000006
}


////////////////////////////////////////////////////////////////
TEST_CASE("Steam ID -> Name + Hash translation", "[competitive][cs_agency]")
{
  // Create a csgoparser with a barebones config, configured to do Steam ID -> Name translations for some players, and SHA1 hash translations for others
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto const config_text = R"(
    {
      "log_dir": "",
      "simulate": true,
      "steam_id_translation": {
        "active": true,
        "hash": "sha1",
        "translations": {
          "STEAM_1:1:00000004": "Dean Alternative",
          "STEAM_1:0:00000005": "James Alternative",
          "STEAM_1:0:00000003": "Sam Alternative"
        }
      }
    }
  )"s;

  auto config = json::parse(config_text);
  config["log_dir"] = std::filesystem::current_path().string();

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

  // Lambda to check the player_id for a given player
  auto player_id_for_player_on_team = [&csgo](auto const &player, auto const &team) -> json {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member) {
      return team_member["player"] == player;
    });

    return (pos != std::end(csgo.game_state["teams"][team]) ? (*pos)["player_id"] : json{});
  };

  // Check the Steam ID -> Name/Hash translation worked
  REQUIRE(player_id_for_player_on_team("Dean", "CT") == "Dean Alternative");   // STEAM_1:1:00000004
  REQUIRE(player_id_for_player_on_team("James", "CT") == "James Alternative"); // STEAM_1:0:00000005
  REQUIRE(player_id_for_player_on_team("Sam", "CT") == "Sam Alternative");     // STEAM_1:0:00000003

  REQUIRE(player_id_for_player_on_team("Alice", "TERRORIST") == "562bcef8703e13c9c8bd4e887d5463a17ccc92d0"); // STEAM_1:1:00000001
  REQUIRE(player_id_for_player_on_team("Bob", "TERRORIST") == "5d4273998aab606d7c2ab0e6f77f71321d3d7bc6");   // STEAM_1:0:00000002
  REQUIRE(player_id_for_player_on_team("Mark", "TERRORIST") == "a5f1bb7645a7515df83b7eb5b11e126c343fe0cc");  // STEAM_1:1:00000006
}


////////////////////////////////////////////////////////////////
SCENARIO("Geo tests", "[geo][cs_agency][de_dust2]")
{
  GIVEN("A game played on cs_agency")
  {
    auto const map_origin = csgoprs::geo::point{-2947.0, 2492.0};
    auto const map_scale = 5.0;

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
    auto const map_scale = 4.4;

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
