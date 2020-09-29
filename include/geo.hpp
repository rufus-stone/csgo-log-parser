#pragma once

#include <fstream> // For file i/o
#include <filesystem> // For filesystem stuff
#include <cstdlib> // For getting the path to the home directory
#include <cmath>
#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>

#include <spdlog/spdlog.h>
#include <sago/platform_folders.h>
#include <hamarr/format.hpp>

#include "nlohmann/json.hpp"

namespace csgoprs::geo
{

using namespace std::string_view_literals;

using json = nlohmann::json;

// Geo details for the stock maps
constexpr auto default_map_geo = R"###({"maps":{"ar_baggage":{"pos_x":-2150,"pos_y":2280,"scale":4.0},"ar_dizzy":{"pos_x":-2512,"pos_y":1536,"scale":3.0},"ar_monastery":{"pos_x":-1687,"pos_y":1640,"scale":3.0},"ar_shoots":{"pos_x":-2150,"pos_y":2582,"scale":4},"coop_cementplant":{"pos_x":-5160,"pos_y":5859,"scale":12},"coop_kasbah":{"pos_x":-5160,"pos_y":5859,"scale":12},"cs_agency":{"pos_x":-2947,"pos_y":2492,"scale":5},"cs_assault":{"pos_x":4041,"pos_y":7838,"scale":4.6},"cs_backalley":{"pos_x":-2485,"pos_y":3200,"scale":3.50},"cs_insertion":{"pos_x":-4888,"pos_y":4884,"scale":10},"cs_italy":{"pos_x":-2647,"pos_y":2592,"scale":4.6},"cs_militia":{"pos_x":-1474,"pos_y":2296,"scale":4.5},"cs_office":{"pos_x":-1838,"pos_y":1858,"scale":4.1},"cs_rush":{"pos_x":-2950,"pos_y":3350,"scale":5.2},"cs_siege":{"pos_x":-1193,"pos_y":3515,"scale":6.5},"cs_workout":{"pos_x":-2176,"pos_y":3165,"scale":6.06},"de_abbey":{"pos_x":-6204,"pos_y":5111,"scale":6.5},"de_ali":{"pos_x":-2064,"pos_y":2920,"scale":5},"de_anubis":{"pos_x":-2796,"pos_y":3328,"scale":5.22},"de_austria":{"pos_x":-2877,"pos_y":2930,"scale":5.80},"de_aztec":{"pos_x":-3200,"pos_y":2841,"scale":6},"de_bazaar":{"pos_x":-2434,"pos_y":2179,"scale":5.0},"de_biome":{"pos_x":-2129,"pos_y":2368,"scale":5.00},"de_blackgold":{"pos_x":-1100,"pos_y":1425,"scale":5.30},"de_breach":{"pos_x":-2950,"pos_y":2886,"scale":5.5},"de_cache":{"pos_x":-2000,"pos_y":3250,"scale":5.5},"de_canals":{"pos_x":-2496,"pos_y":1792,"scale":4},"de_castle":{"pos_x":-3378,"pos_y":2756,"scale":5.5},"de_chinatown":{"pos_x":-1735,"pos_y":3232,"scale":4},"de_chlorine":{"pos_x":2076,"pos_y":1272,"scale":5.25},"de_coast":{"pos_x":-3028,"pos_y":4122,"scale":5.50},"de_dust2":{"pos_x":-2476,"pos_y":3239,"scale":4.4},"de_dust":{"pos_x":-2850,"pos_y":4073,"scale":6},"de_empire":{"pos_x":-2165,"pos_y":2000,"scale":4.5},"de_facade":{"pos_x":-90,"pos_y":5659,"scale":6},"de_gwalior":{"pos_x":-1145,"pos_y":2688,"scale":5},"de_inferno":{"pos_x":-2087,"pos_y":3870,"scale":4.9},"de_lite":{"pos_x":-2012,"pos_y":2928,"scale":5},"de_log":{"pos_x":-411,"pos_y":759,"scale":6.50},"de_marquis":{"pos_x":-1877,"pos_y":3199,"scale":5.0},"de_mikla":{"pos_x":711,"pos_y":2383,"scale":4.1},"de_mirage":{"pos_x":-3230,"pos_y":1713,"scale":5.00},"de_mist":{"pos_x":-5150,"pos_y":2080,"scale":4.8},"de_nuke":{"pos_x":-3453,"pos_y":2887,"scale":7},"de_overgrown_b7":{"pos_x":-3376,"pos_y":5563,"scale":7},"de_overpass":{"pos_x":-4831,"pos_y":1781,"scale":5.2},"Rails":{"pos_x":-2199,"pos_y":2874,"scale":4.5},"de_resort":{"pos_x":-506,"pos_y":2713,"scale":5.5},"de_royal":{"pos_x":-2343,"pos_y":2644,"scale":4},"de_ruby":{"pos_x":-1079,"pos_y":3093,"scale":4.50},"de_ruins":{"pos_x":-2443,"pos_y":2485,"scale":6.25},"de_safehouse":{"pos_x":-240,"pos_y":2650,"scale":4.52},"Santorini":{"pos_x":-2135,"pos_y":1400,"scale":4},"de_seaside":{"pos_x":-4161,"pos_y":3680,"scale":7},"de_season":{"pos_x":-1003,"pos_y":2521,"scale":5.00},"de_shipped":{"pos_x":-2432,"pos_y":2663,"scale":5.80},"de_shortdust":{"pos_x":-2318,"pos_y":2337,"scale":3.6},"de_shortnuke":{"pos_x":-3453,"pos_y":2887,"scale":7},"de_shorttrain":{"pos_x":-2477,"pos_y":2392,"scale":4.7},"de_stmarc":{"pos_x":-9383,"pos_y":9099,"scale":4},"de_studio":{"pos_x":-3248,"pos_y":2968,"scale":6.17},"de_subzero":{"pos_x":-2438,"pos_y":3690,"scale":5.0},"de_sugarcane":{"pos_x":-4015,"pos_y":2000,"scale":4.25},"de_thrill":{"pos_x":-3276,"pos_y":2973,"scale":5.5},"de_train":{"pos_x":-2477,"pos_y":2392,"scale":4.7},"de_tulip":{"pos_x":3402,"pos_y":5583,"scale":5.50},"de_vertigo":{"pos_x":-3168,"pos_y":1762,"scale":4.0},"de_zoo":{"pos_x":-2435,"pos_y":6116,"scale":7},"dz_blacksite":{"pos_x":-8604,"pos_y":8804,"scale":17.0},"dz_junglety":{"pos_x":-8504,"pos_y":8741,"scale":17.0},"dz_sirocco":{"pos_x":-8604,"pos_y":8804,"scale":17.0},"de_bank":{"pos_x":-2000,"pos_y":1493,"scale":4},"de_cbble":{"pos_x":-3840,"pos_y":3072,"scale":6},"gd_crashsite":{"pos_x":-2212,"pos_y":1437,"scale":3.5},"de_lake":{"pos_x":1200,"pos_y":-700,"scale":5.2},"ar_lunacy":{"pos_x":-1536,"pos_y":1536,"scale":3.0},"gd_rialto":{"pos_x":-1260,"pos_y":1836,"scale":3.0},"training1":{"pos_x":-2510,"pos_y":2000,"scale":5}}})###"sv;

struct point
{
  double x;
  double y;
};

constexpr auto earth_radius = 6378137.0;
constexpr auto origin_shift = (2.0 * M_PI * earth_radius) / 2.0;
constexpr auto tile_size = 256;
constexpr auto initial_resolution = (2.0 * M_PI * earth_radius) / tile_size; // 156543.03392804062 for a tile_size of 256

// Resolution (metres/pixel) for the given zoom level (measured at Equator)
auto resolution(std::size_t zoom) -> double
{
    return initial_resolution / std::pow(2, zoom);
}

auto pixels_to_metres(csgoprs::geo::point pixels, std::size_t zoom) -> csgoprs::geo::point
{
  auto const metres_x = (pixels.x * resolution(zoom)) - origin_shift;
  auto const metres_y = 0 - (pixels.y * resolution(zoom)) - origin_shift;

  return csgoprs::geo::point{metres_x, metres_y};
}

auto csgo_grid_to_pixels(csgoprs::geo::point xy, csgoprs::geo::point map_origin_xy, double map_scale) -> csgoprs::geo::point
{
  // Convert the in-game coordinate system to the X/Y pixel position for a 1024x1024 pixel image
  auto const pixels_x = ((xy.x + (0 - map_origin_xy.x)) / map_scale);
  auto const pixels_y = ((xy.y + (0 - map_origin_xy.y)) / map_scale);

  return csgoprs::geo::point{pixels_x, pixels_y};
}

auto metres_to_lat_lon(csgoprs::geo::point metres) -> point
{
  auto lon = (metres.x / origin_shift) * 180.0;
  auto lat = (metres.y / origin_shift) * 180.0;

  lat = 180 / M_PI * (2 * std::atan(std::exp(lat * M_PI / 180.0)) - M_PI / 2.0);

  return csgoprs::geo::point{lat, lon};
}

////////////////////////////////////////////////////////////////
auto xy_to_lat_lon(csgoprs::geo::point pos_xy, csgoprs::geo::point map_origin_xy, double map_scale) -> csgoprs::geo::point
{
  // Convert the CS:GO grid positions to X/Y pixel positions on a 1024x1024 image
  auto const pixels = csgo_grid_to_pixels(pos_xy, map_origin_xy, map_scale);

  // According to https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/
  // At zoom level 2 using Spherical Mercator projection, the map will be 1024x1024 pixels, which fits our game map images
  // The EPSG projection caps latitude values at 85.0511287798066 and -85.05112877980659, as the projection rapidly tends towards infinity beyond this point
  auto const metres = pixels_to_metres(pixels, 2);

  //auto const [lat, lon] = metres_to_lat_lon(metres);
  //spdlog::info("Map origin XY: {},{} ::: Grid XY: {},{} -> pixels XY: {},{} -> metres XY: {},{} -> lat/lon: {},{}", map_origin_xy.x, map_origin_xy.y, pos_xy.x, pos_xy.y, pixels.x, pixels.y, metres.x, metres.y, lat, lon);

  return metres_to_lat_lon(metres);
}

////////////////////////////////////////////////////////////////
auto pos_to_lat_lon(std::string_view pos, std::string const &game_map, json const &map_json) -> std::string
{
  // Is the specified map in the map geo JSON?
  if (map_json["maps"].contains(game_map))
  {
    auto const player_xyz = hmr::format::split(pos, ' ');

    // The player and victim positions should always have an X Y and Z component
    if (player_xyz.size() != 3)
    {
      return "0.00,0.00";
    }

    // We only care about the X and Y components of the CS:GO grid position for mapping purposes
    auto const pos_x  = static_cast<double>(std::stoi(player_xyz[0].data()));
    auto const pos_y  = static_cast<double>(std::stoi(player_xyz[1].data()));
    auto const pos_xy = csgoprs::geo::point{pos_x, pos_y};

    auto const map_origin_x  = static_cast<double>(map_json["maps"][game_map]["pos_x"].get<int>());
    auto const map_origin_y  = static_cast<double>(map_json["maps"][game_map]["pos_y"].get<int>());
    auto const map_origin_xy = csgoprs::geo::point{map_origin_x, map_origin_y};

    auto const map_scale  = map_json["maps"][game_map]["scale"].get<double>();

    auto const [lat, lon] = xy_to_lat_lon(pos_xy, map_origin_xy, map_scale);

    // Turn the lat/lon point into a string, rounding to 2 decimal places
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << lat << "," << lon;
    return ss.str();
  }
  
  return "0.00,0.00";
}


////////////////////////////////////////////////////////////////
auto locate_map_details(const std::filesystem::path &custom_path = std::filesystem::path{}) -> std::filesystem::path
{
  auto map_geo_path = std::filesystem::path{};

  // Are we using a custom file location?
  if (!custom_path.empty())
  {
    map_geo_path = custom_path;
  } else
  {
    // Try to find the default location for a csgoparse map geo file for this platform
    try
    {
      map_geo_path = sago::getConfigHome(); // ~/.config on Linux,
    } catch (...)
    {
      spdlog::error("Failed to find config location!");
      return std::filesystem::path{};
    }

    map_geo_path = map_geo_path / "csgoparse" / "maps.json";
  }

  spdlog::info("Looking for map geo file at: {}", map_geo_path.string());

  // Check if the path exists
  if (!std::filesystem::exists(map_geo_path))
  {
    spdlog::warn("Cannot find map geo file at: {} ... Attempting to create one...", map_geo_path.string());

    // Create a csgoparse directory if it does not already exist
    try
    {
      std::filesystem::create_directories(map_geo_path.parent_path());
    } catch (const std::filesystem::filesystem_error &e)
    {
      spdlog::error(e.what());
      return std::filesystem::path{};
    }

    // Write the default map geo to file
    auto const default_map_geo_json = json::parse(default_map_geo);
    auto map_geo_file = std::ofstream{map_geo_path};
    map_geo_file << default_map_geo_json.dump(2);
    map_geo_file.close();
  }

  return map_geo_path;
}


////////////////////////////////////////////////////////////////
auto load_map_geo(const std::filesystem::path &custom_path = std::filesystem::path{}) -> json
{
  auto const path = locate_map_details(custom_path);

  // Does the path actually exist/can we see it?
  if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
  {
    spdlog::error("Couldn't find map geo file at: {}", path.string());
    return json{};
  }

  // Open the map geo file
  auto map_geo = std::ifstream{path};

  try
  {
    auto const map_geo_json = json::parse(map_geo);

    // Just in case we need to tidy up
    if (map_geo.is_open())
    {
      map_geo.close();
    }

    spdlog::info("Loaded map geo from file:\n{}", map_geo_json.dump(2));

    return map_geo_json;

  } catch (nlohmann::detail::parse_error const &e)
  {
    spdlog::warn("Failed to parse map geo JSON! : {}", e.what());
    spdlog::warn("Falling back to built-in map geo defaults...");

    // Fall back on the built-in defaults
    return json::parse(default_map_geo);
  }
}

} // namespace csgoprs::geo
