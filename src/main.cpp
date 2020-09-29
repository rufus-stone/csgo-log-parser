#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>

#include "csgoparse.hpp"
#include "config.hpp"
#include "geo.hpp"

static constexpr auto usage =
  R"(CS:GO Server Log Parser.

  Usage:
    csgoparse [options]

  Options:
    -h, --help                  Show this screen.
    -v, --version               Show version.
    -c <path>, --config <path>  Path to your config.json config file. This will override the default location.
    -g <path>, --geo <path>     Path to your maps.json geo details file. This will override the default location.
    -d <path>, --log_dir <path> Path to the directory containing the CS:GO game logs. This will override the path specified (if any) in the config.json.
    -t, --test                  Perform a dry run to test log parsing, without dispatching any events to, e.g. elasticsearch
    -i, --ignore                Ignore Steam ID -> Name translations.
)";


int main(int argc, char const **argv)
{
  auto args = docopt::docopt(usage, {std::next(argv), std::next(argv, argc)},
    true, // show help if requested
    "csgoparse 1.0"); // version string


  // Optional custom config path
  auto custom_config_path = std::filesystem::path{};
  if (args["--config"].isString())
  {
    custom_config_path = args["--config"].asString();
    spdlog::info("Custom config file path: {}", custom_config_path.string());
  }

  // Optional custom map geo path
  auto custom_geo_path = std::filesystem::path{};
  if (args["--geo"].isString())
  {
    custom_geo_path = args["--geo"].asString();
    spdlog::info("Custom map geo file path: {}", custom_geo_path.string());
  }

  // Load the config JSON from file
  auto config_json = csgoprs::cfg::load_config(custom_config_path);

  // Load the map geo JSON from file
  auto geo_json = csgoprs::geo::load_map_geo(custom_geo_path);

  // Determine where to look for the server logs
  // If specified on the command line, override the path to the log directory
  auto log_dir_path = std::filesystem::path{};
  if (args["--log_dir"].isString())
  {
    auto const log_dir = args["--log_dir"].asString();
    log_dir_path = std::filesystem::path{log_dir};

    spdlog::info("Overriding log dir path - looking in: {}", log_dir_path.string());

    // Otherwise go with whatever is in the config
  } else if (config_json["log_dir"].is_string())
  {
    log_dir_path = std::filesystem::path{config_json["log_dir"].get<std::string>()};

    spdlog::info("Using log dir path from config - looking in: {}", log_dir_path.string());

  } else
  {
    spdlog::error("No valid log dir path specified in config, or provided via command line argument!");
    return EXIT_FAILURE;
  }

  // Is this a test run? - Update the config either way
  auto const test_run = args["--test"].asBool();
  config_json["simulate"] = test_run;

  // Are we ignoring Steam ID => translations? - override the config if so
  if (args["--ignore"].asBool() == true)
  {
    config_json["steam_id_translation"]["active"] = false;
  }

  // Create the csgoparser and begin!
  auto csgo = csgoprs::csgoparser{config_json, geo_json};
  csgo.track_stats();

  return EXIT_SUCCESS;
}
