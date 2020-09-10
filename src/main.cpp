#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>

#include "csgoparse.hpp"
#include "config.hpp"

static constexpr auto usage =
  R"(CS:GO Server Log Parser.

  Usage:
    csgoparse [options]

  Options:
    -h --help                   Show this screen.
    -v --version                Show version.
    -d <path>, --log_dir <path> Path to the directory containing the CS:GO game logs. This will override the path specified (if any) in the config.json.
    -c <path>, --config <path>  Path to your config.json config file. This will override the default location.
    -t, --test                  Perform a dry run to test log parsing, without dispatching any events to, e.g. elasticsearch
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

  // Load the config JSON from file
  auto const config_json = csgoprs::cfg::load_config(custom_config_path);

  // Determine where to look for the server logs
  // If specified on the command line, override the path to the log directory
  auto log_dir_path = std::filesystem::path{};
  if (args["--log_dir"].isString())
  {
    auto const log_dir = args["--log_dir"].asString();
    log_dir_path = std::filesystem::path{log_dir};

    spdlog::info("Overriding log dir path - looking in: {}", log_dir_path.string());

    // Otherwise go with whatever is in the config
  } else if (config_json["log_dir"].is_string()) //!config_json["log_dir"].is_null()
  {
    log_dir_path = std::filesystem::path{config_json["log_dir"].get<std::string>()};

    spdlog::info("Using log dir path from config - looking in: {}", log_dir_path.string());
  } else
  {
    spdlog::error("No valid log dir path specified in config, or provided via command line argument!");
    return EXIT_FAILURE;
  }

  // Is this a test run?
  auto const test_run = args["--test"].asBool();

  auto csgo = csgoprs::csgoparser{log_dir_path, test_run};

  csgo.track_stats();

  return EXIT_SUCCESS;
}
