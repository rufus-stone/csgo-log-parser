#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt.h>

#include "csgoparse.hpp"
#include "config.hpp"
#include "geo.hpp"
#include "elasticsearch.hpp"

#include <hamarr/base64.hpp>


static constexpr auto usage =
  R"(CS:GO Server Log Parser.

  Usage:
    csgoparse [options]

  Options:
    -h, --help                    Show this screen
    -v, --version                 Show app version
    -V, --verbose                 Enable verbose logging (for debugging purposes)
    -c <path>, --config <path>    Path to config.json config file
    -g <path>, --geo <path>       Path to maps.json geo details file
    -d <path>, --log_dir <path>   Path to directory containing the CS:GO game logs
    -t, --test                    Perform dry run to test log parsing, without dispatching any events to, e.g. elasticsearch
    -i, --ignore                  Ignore Steam ID -> Name translations
    --hash <algo>                 Enable Steam ID -> Hash translations using specified hashing algorithm (must be one of: md5, sha1, sha256)
    --es_endpoint <url>           Elasticsearch endpoint
    --es_cloud_id <id>            Elasticsearch Cloud ID (in the format "name:base64_string")
    --es_port <port>              Elasticsearch port number for endpoint (needed if using Cloud ID)
    --es_user <user>              Elasticsearch username
    --es_pass <pass>              Elasticsearch password
    --es_api_key <key>            Elasticsearch API key (in the format "id:key")
    --es_index <name>             Elasticsearch index name
    --es_create_index             Create new Elasticsearch index (uses the index name given in config.json, but can override using --es_index)
    --es_delete_index             Delete Elasticsearch index (uses the index name given in config.json, but can override using --es_index)
    --es_check_exists             Check whether Elasticsearch index exists (uses the index name given in config.json, but can override using --es_index)
)";


int main(int argc, char const **argv)
{
  auto args = docopt::docopt(usage, {std::next(argv), std::next(argv, argc)},
    true,               // show help if requested
    "csgoparse 0.2.0"); // version string


  bool const verbose = args["--verbose"].asBool();
  if (verbose)
  {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Enabled verbose logging...");
  }

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

    spdlog::debug("Using log dir path from config - looking in: {}", log_dir_path.string());

  } else
  {
    spdlog::error("No valid log dir path specified in config, or provided via command line argument!");
    return EXIT_FAILURE;
  }

  // Is this a test run? - Update the config either way
  auto const test_run = args["--test"].asBool();
  config_json["simulate"] = test_run;

  // Are we ignoring Steam ID => Name translations? - override the config if so
  if (args["--ignore"].asBool() == true)
  {
    spdlog::info("Ignoring Steam ID translations");
    config_json["steam_id_translation"]["active"] = false;
  }

  // Force a particular Steam ID => Hash translation? - override the config if so
  if (args["--hash"].isString())
  {
    auto const hash_type = args["--hash"].asString();

    if (hash_type == "md5" || hash_type == "sha1" || hash_type == "sha256")
    {
      spdlog::info("Enabled Steam ID -> Hash translation ({})", hash_type);
      config_json["steam_id_translation"]["hash"] = hash_type;
    } else
    {
      spdlog::error("Invalid hash type specified: \"{}\" - must be one of: \"md5\", \"sha1\", \"sha256\"!", hash_type);
      return EXIT_FAILURE;
    }
  }

  // Any Elasticsearch config?
  // Prefer Cloud ID over Endpoint if both were given
  if (args["--es_cloud_id"].isString() && args["--es_port"].isString())
  {
    auto const es_cloud_id = args["--es_cloud_id"].asString();
    auto const es_port = args["--es_port"].asString();

    spdlog::info("Using Elasticsearch Cloud ID: {}", es_cloud_id);
    spdlog::info("Using Elasticsearch port num: {}", es_port);

    config_json["elasticsearch"]["cloud_id"] = es_cloud_id;
    config_json["elasticsearch"]["port"] = es_port;

  } else if (args["--es_endpoint"].isString())
  {
    auto const es_endpoint = args["--es_endpoint"].asString();

    spdlog::info("Using Elasticsearch endpoint: {}", es_endpoint);

    config_json["elasticsearch"]["endpoint"] = es_endpoint;

    // If an endpoint was given on the command line, assume the user wants to use this instead of any Cloud ID/port that might have been specified in the config.json
    config_json["elasticsearch"].erase("cloud_id");
    config_json["elasticsearch"].erase("port");
  }

  // Prefer API key over username/password  if both were given
  if (args["--es_api_key"].isString())
  {
    auto const es_api_key = args["--es_api_key"].asString();

    spdlog::info("Using Elasticsearch API key: {}", es_api_key);

  } else if (args["--es_user"].isString() && args["--es_pass"].isString())
  {
    auto const es_user = args["--es_user"].asString();
    auto const es_pass = args["--es_pass"].asString();

    spdlog::info("Using Elasticsearch username: {} / password: {}", es_user, es_pass);
  }

  if (args["--es_index"].isString())
  {
    auto const es_index = args["--es_index"].asString();

    spdlog::info("Using Elasticsearch index: {}", es_index);

    config_json["elasticsearch"]["index"] = es_index;
  }


  // Were any Elasticsearch index commands given? If so, run these and then exit
  if (args["--es_check_exists"].asBool())
  {
    spdlog::info("Checking status of Elasticsearch index...");

    auto csgo = csgoprs::csgoparser{config_json, geo_json};

    auto status_code = csgo.es_client->index_exists().status_code;

    if (status_code == 200)
    {
      spdlog::info("Index exists: {}", config_json["elasticsearch"]["index"].get<std::string>());

    } else if (status_code == 404)
    {
      spdlog::info("Index does NOT exist: {}", config_json["elasticsearch"]["index"].get<std::string>());
    } else
    {
      spdlog::info("Unable to determine whether index exists: {}", config_json["elasticsearch"]["index"].get<std::string>());
    }

    return EXIT_SUCCESS;
  }


  // Create the csgoparser and begin!
  auto csgo = csgoprs::csgoparser{config_json, geo_json};
  return EXIT_SUCCESS;

  csgo.track_stats();

  return EXIT_SUCCESS;
}
