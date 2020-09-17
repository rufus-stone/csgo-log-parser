#pragma once

#include <string_view>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>

#include <hamarr/format.hpp>

namespace csgoprs
{

////////////////////////////////////////////////////////////////
auto dtg_to_epoch_millis(std::string_view dtg) -> uint64_t
{
  auto tmt = tm{};
  strptime(dtg.data(), "%m/%d/%Y - %H:%M:%S", &tmt);

  const auto epoch_secs = static_cast<uint64_t>(mktime(&tmt));

  return epoch_secs * 1000;
}


////////////////////////////////////////////////////////////////
auto metres_between_points(std::string_view p_pos, std::string_view v_pos) -> std::string
{
  const auto player_xyz = hmr::format::split(p_pos, ' ');
  const auto victim_xyz = hmr::format::split(v_pos, ' ');

  // The player and victim positions should always have an X Y and Z component
  if (player_xyz.size() != 3 || victim_xyz.size() != 3)
  {
    return std::string{};
  }

  const auto p_x = std::stoi(player_xyz[0].data());
  const auto p_y = std::stoi(player_xyz[1].data());
  const auto p_z = std::stoi(player_xyz[2].data());

  const auto v_x = std::stoi(victim_xyz[0].data());
  const auto v_y = std::stoi(victim_xyz[1].data());
  const auto v_z = std::stoi(victim_xyz[2].data());

  // Find the Euclidean distance between the player and victim
  const double distance = std::hypot(p_x - v_x, p_y - v_y, p_z - v_z);

  // According to the Source SDK (https://developer.valvesoftware.com/wiki/Dimensions), in-game distances are
  // measured at 16 grid points per foot. This is equivalent to 16 points per 0.3048 metres, or 52.49343832 points per metre
  // We'll round the result to 2 decimal places

  std::ostringstream ss;
  ss << std::fixed << std::setprecision(2);
  ss << (distance / 52.49343832);

  return ss.str();
}

} // namespace csgoprs
