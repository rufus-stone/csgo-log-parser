#pragma once

#include <fstream> // For file i/o
#include <filesystem> // For filesystem stuff
#include <cstdlib> // For getting the path to the home directory

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

#include <spdlog/spdlog.h>
#include <sago/platform_folders.h>

#include "nlohmann/json.hpp"

namespace csgoprs::cfg
{

using namespace std::string_view_literals;

// TODO: Fill this out with a sane default config
constexpr auto default_config = "ddasdf"sv;


auto find_config_file = [](const std::filesystem::path &custom_path = std::filesystem::path{}) -> std::filesystem::path
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

  spdlog::info("Looking for config file at: {}", config_path.string());

  // Check if the path exists
  if (!std::filesystem::exists(config_path))
  {
    spdlog::warn("Cannot find config file at: {} ... Attempting to create one...", config_path.string());

    // Create a csgoparse directory if it does not already exist
    try
    {
      std::filesystem::create_directories(config_path.parent_path());
    } catch (const std::filesystem::filesystem_error &e)
    {
      spdlog::error(e.what());
      return std::filesystem::path{};
    }

    // Write the default config to file
    auto config_file = std::ofstream{config_path};
    config_file << default_config;
    config_file.close();
  }

  return config_path;
};


using json = nlohmann::json;

auto read_config(std::filesystem::path path) -> json
{
  // Does the path actually exist/can we see it?
  if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
  {
    spdlog::error("Couldn't find config file at: {}", path.string());
    return json{};
  }

  // Open the config file
  auto config = std::ifstream{path};

  auto config_json = json::parse(config);

  if (config.is_open())
  {
    spdlog::info("File still open!");
  }

  return config_json;
}

} // namespace csgoprs::cfg
