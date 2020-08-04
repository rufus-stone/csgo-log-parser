#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>

#include "csgoparse.hpp"

static constexpr auto USAGE =
    R"(CS:GO Server Log Parser.

  Usage:
    csgoparse --log_dir <path>
        
  Options:
    -h --help     Show this screen.
    -v --version  Show version.
    -d --log_dir  Path to the directory containing the CS:GO game logs (probably <CS:GO install dir>/server/log).
)";

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  auto args = docopt::docopt(USAGE,
                             {std::next(argv), std::next(argv, argc)},
                             true,                    // show help if requested
                             "CS:GO Log Parser 1.0"); // version string

  for (auto const &arg : args)
  {
    spdlog::info("{} == {}", arg.first, arg.second.asString());
  }

  auto csgo = csgoprs::csgoparser{"/path/to/logs/dir"};

  csgo.track_stats();

  return 0;
}
