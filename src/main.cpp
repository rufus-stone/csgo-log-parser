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
    -d <path>, --log_dir <path> Path to the directory containing the CS:GO game logs (probably <CS:GO install dir>/server/logs).
    -t, --test                  Perform a dry run to test log parsing, without dispatching any events to, e.g. elasticsearch
    -c <path>, --config <path>  Path to your csgoparse.json config file
)";


int main(int argc, const char **argv)
{
  auto args = docopt::docopt(usage, {std::next(argv), std::next(argv, argc)},
    true, // show help if requested
    "CS:GO Log Parser 1.0"); // version string


  auto custom_config_path = std::filesystem::path{};
  // A path to the log directory is required (for now)
  if (args["--config"].isString())
  {
    custom_config_path = args["--config"].asString();
    spdlog::info("Custom config file path: {}", custom_config_path.string());
  }

  auto const config_path = csgoprs::cfg::find_config_file(custom_config_path);

  // A path to the log directory is required (for now)
  if (!args["--log_dir"].isString())
  {
    spdlog::error("Must specify a path to the log directory");
    return EXIT_FAILURE;
  }

  // Where are the logs stored?
  auto const log_dir = args["--log_dir"].asString();
  spdlog::info("Log directory: {}", log_dir);

  // Is this a test run?
  auto const test_run = args["--test"].asBool();

  auto csgo = csgoprs::csgoparser{log_dir, test_run};

  csgo.track_stats();

  return EXIT_SUCCESS;
}
