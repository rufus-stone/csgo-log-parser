#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>

#include "csgoparse.hpp"

static constexpr auto USAGE =
    R"(CS:GO Server Log Parser.

  Usage:
    csgoparse [options]

  Options:
    -h --help                    Show this screen.
    -v --version                 Show version.
    -d <path>, --log_dir <path>  Path to the directory containing the CS:GO game logs (probably <CS:GO install dir>/server/logs).
    -t, --test                   Perform a dry run to test log parsing, without dispatching any events to, e.g. elasticsearch
)";



int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  auto args = docopt::docopt(USAGE,
                             {std::next(argv), std::next(argv, argc)},
                             true,                    // show help if requested
                             "CS:GO Log Parser 1.0"); // version string


  const auto log_dir = args["--log_dir"].asString();
  spdlog::info("Log directory: {}", log_dir);

  auto csgo = csgoprs::csgoparser{log_dir};

  csgo.track_stats();

  return 0;
}
