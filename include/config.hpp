#pragma once

#include <fstream>    // For file i/o
#include <filesystem> // For filesystem stuff
#include <cstdlib>    // For getting the path to the home directory

#include <string>
#include <string_view>

#include <spdlog/spdlog.h>
#include <sago/platform_folders.h>

#include "nlohmann/json.hpp"

namespace csgoprs::cfg
{

using namespace std::string_view_literals;

// A barebones default config that will need filling out with the path to the directory where the CS:GO server logs are located
//constexpr auto default_config = R"###({"log_dir":null, "steam_id_translation":{"active":false, "translations":[{"STEAM_1:0:12345678":"Player 1"}, {"STEAM_1:1:87654321":"Player 2"}]}})###"sv;
constexpr auto default_config = R"###({"log_dir":null})###"sv;

////////////////////////////////////////////////////////////////
auto locate_config(std::filesystem::path const &custom_path = std::filesystem::path{}) -> std::filesystem::path
{
  auto config_path = std::filesystem::path{};

  // Are we using a custom config location?
  if (!custom_path.empty())
  {
    config_path = custom_path;
  } else
  {
    // Try to find the default location for a csgoparse config file for this platform
    try
    {
      config_path = sago::getConfigHome(); // ~/.config on Linux,
    } catch (...)
    {
      spdlog::error("Failed to find config location!");
      return std::filesystem::path{};
    }

    config_path = config_path / "csgoparse" / "config.json";
  }

  spdlog::debug("Looking for config file at: {}", config_path.string());

  // Check if the path exists
  if (!std::filesystem::exists(config_path))
  {
    spdlog::warn("Cannot find config file at: {} ... Attempting to create one...", config_path.string());

    // Create a csgoparse directory if it does not already exist
    try
    {
      std::filesystem::create_directories(config_path.parent_path());
    } catch (std::filesystem::filesystem_error const &e)
    {
      spdlog::error(e.what());
      return std::filesystem::path{};
    }

    // Write the default config to file
    auto const default_config_json = json::parse(default_config);
    auto config_file = std::ofstream{config_path};
    config_file << default_config_json.dump(2);
    config_file.close();
  }

  return config_path;
}


////////////////////////////////////////////////////////////////
auto load_config(std::filesystem::path const &custom_path = std::filesystem::path{}) -> json
{
  auto const path = locate_config(custom_path);

  using json = nlohmann::json;

  // Does the path actually exist/can we see it?
  if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
  {
    spdlog::error("Couldn't find config file at: {}", path.string());
    return json{};
  }

  // Open the config file
  auto config = std::ifstream{path};

  try
  {
    auto const config_json = json::parse(config);

    // Just in case we need to tidy up
    if (config.is_open())
    {
      config.close();
    }

    spdlog::debug("Loaded config from file:\n{}", config_json.dump(2));

    return config_json;

  } catch (nlohmann::detail::parse_error const &e)
  {
    spdlog::error("Failed to parse config JSON! : {}", e.what());
    return json{};
  }
}

} // namespace csgoprs::cfg
