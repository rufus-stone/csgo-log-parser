#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

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

TEST_CASE("Simulation", "[simulation]")
{
  // Create a csgoparser with a barebones config
  // the actual log_dir path doesn't matter as we'll be feeding in pre-canned log lines, but it expects a real location so we'll use the current working directory, as that's guaranteed to exist!
  auto config = json::parse(R"###({"log_dir":")###" + std::filesystem::current_path().string() + R"###(", "simulate":true})###");
  auto csgo = csgoprs::csgoparser{config};

  // Load in the sample logs - these simulate a complete competitive match on cs_agency
  auto sample_logs = std::istringstream{csgoprs::log_samples::competitive_cs_agency.data()};
  auto lines = std::vector<std::string>{};
  auto line = std::string{};
  while (std::getline(sample_logs, line))
  {
    lines.push_back(line);
  }

  // Play back the logs and parse the events
  for (const auto &log_line : lines)
  {
    csgo.parse_event(log_line);
  }

  // Check the game map and mode were correctly identified
  REQUIRE(csgo.game_state["game_map"].get<std::string>() == "cs_agency");
  REQUIRE(csgo.game_state["game_mode"].get<std::string>() == "competitive");

  // Check the CT and TERRORIST team members were correctly identified
  auto is_member_of_team = [&csgo](const auto &player, const auto &team) -> bool
  {
    auto pos = std::find_if(std::begin(csgo.game_state["teams"][team]), std::end(csgo.game_state["teams"][team]), [&player](const json &team_member)
    {
      return team_member["player"] == player;
    });

    return (pos != std::end(csgo.game_state["teams"][team]));
  };

  REQUIRE(is_member_of_team("Dean", "CT") == true);
  REQUIRE(is_member_of_team("James", "CT") == true);
  REQUIRE(is_member_of_team("Sam", "CT") == true);

  REQUIRE(is_member_of_team("Alice", "TERRORIST") == true);
  REQUIRE(is_member_of_team("Bob", "TERRORIST") == true);
  REQUIRE(is_member_of_team("Mark", "TERRORIST") == true);

  // TODO - Check that the winning team was correctly identified
  //game_state["event_buffer"]
}
