#include <iostream>

#include "csgoparse.hpp"

int main()
{
  auto csgo = csgoprs::csgoparser{"/path/to/logs/dir"};

  csgo.track_stats();

  return 0;
}
