#include <iostream>
#include <sstream>

#include <spdlog/spdlog.h>
#include <docopt.h>

#include "csgoparse.hpp"
#include "config.hpp"
#include "geo.hpp"
#include "elasticsearch.hpp"

#include <hamarr/base64.hpp>


static constexpr auto usage =
  R"(Welcome to csgoparse, a CS:GO server log parser with Elasticsearch integration!

Use csgoparse to read your CS:GO dedicated server game logs, and turn them into rich JSON.
Dispatch these logs directly into your Elasticsearch instance, or pipe them elsewhere.

Usage:
  csgoparse track [--es_index <name>] [options]
  csgoparse check [--es_index <name>] [options]
  csgoparse sample [--es_index <name>] [options]
  csgoparse create [--es_index <name>] [options]
  csgoparse delete [--es_index <name>] [options]
  csgoparse ping [options]
  csgoparse info [<username>] [options]

Options:
  -h, --help                    Show this screen
  -v, --version                 Show app version
  -V, --verbose                 Enable verbose logging (for debugging purposes - incompatible with quiet mode)
  -q, --quiet                   Enable quiet mode. Only errors will be logged (incompatible with verbose mode)
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
)";


int main(int argc, char const **argv)
{
  auto args = docopt::docopt(usage, {std::next(argv), std::next(argv, argc)},
    true,               // show help if requested
    "csgoparse 0.2.0"); // version string


  bool const verbose = args["--verbose"].asBool();
  bool const quiet = args["--quiet"].asBool();
  // Can't have verbose mode AND quiet mode!
  if (verbose && quiet)
  {
    spdlog::error("Cannot enable verbose logging AND quiet mode at the same time!");
    return EXIT_FAILURE;
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Enabled verbose logging...");
  }

  if (verbose)
  {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Enabled verbose logging...");
  } else if (quiet)
  {
    spdlog::set_level(spdlog::level::err);
    spdlog::debug("Enabled quiet logging...");
  }

  // Print out the args if in debug mode
  for (auto const &kvp : args)
  {
    std::stringstream ss;
    ss << kvp.second;

    spdlog::debug("{} == {}", kvp.first, ss.str());
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

  // Any Elasticsearch config? - override the config if so
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

  // Prefer API key over username/password if both were given
  if (args["--es_api_key"].isString())
  {
    auto const es_api_key = args["--es_api_key"].asString();

    spdlog::info("Using Elasticsearch API key: {}", es_api_key);

    // Override the api_key value in the config.json, and remove any username/password
    config_json["elasticsearch"]["api_key"] = es_api_key;
    config_json["elasticsearch"].erase("username");
    config_json["elasticsearch"].erase("password");

  } else if (args["--es_user"].isString() && args["--es_pass"].isString())
  {
    auto const es_user = args["--es_user"].asString();
    auto const es_pass = args["--es_pass"].asString();

    spdlog::info("Using Elasticsearch username: {} / password: {}", es_user, es_pass);

    // Override the username/password values in the config.json, and remove any API Key
    config_json["elasticsearch"]["username"] = es_user;
    config_json["elasticsearch"]["password"] = es_pass;
    config_json["elasticsearch"].erase("api_key");
  }

  if (args["--es_index"].isString())
  {
    auto const es_index = args["--es_index"].asString();

    spdlog::info("Using Elasticsearch index: {}", es_index);

    config_json["elasticsearch"]["index"] = es_index;
  }


  // +---------------------------+
  // | What commands were given? |
  // +---------------------------+

  // Start tracking game logs?
  if (args["track"].asBool())
  {
    spdlog::info("Starting stats tracking...");

    // Create the csgoparser and begin!
    auto csgo = csgoprs::csgoparser{config_json, geo_json};
    csgo.track_stats();

    return EXIT_SUCCESS;
  }


  // Check the index exists?
  if (args["check"].asBool())
  {
    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const index_name = es_client->index_name();

    spdlog::info("Checking if Elasticsearch index '{}' exists...", index_name);

    auto const response = es_client->index_exists();

    if (response.status_code == 200)
    {
      spdlog::info("Confirmed: Elasticsearch index '{}' exists", index_name);

    } else if (response.status_code == 404)
    {
      spdlog::error("Index '{}' not found!", index_name);

    } else
    {
      spdlog::error("Unknown error checking if index '{}' exists! Response status code: {}", index_name, response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  // Sample some data from the Elasticsearch index?
  if (args["sample"].asBool())
  {
    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const index_name = es_client->index_name();

    spdlog::info("Sampling data from Elasticsearch index '{}'...", index_name);

    auto const response = es_client->sample_index();

    if (response.status_code == 200)
    {
      spdlog::info("Successfully sampled data from Elasticsearch index '{}'...", index_name);
      spdlog::info(response.text);
    } else
    {
      spdlog::error("Error sampling data from Elasticsearch index '{}'! Response status code: {}", index_name, response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  // Create a new Elasticsearch index?
  if (args["create"].asBool())
  {
    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const index_name = es_client->index_name();

    spdlog::info("Creating new Elasticsearch index '{}'...", index_name);

    auto const response = es_client->create_index_with_mappings();

    if (response.status_code == 200)
    {
      spdlog::info("Successfully created index '{}'", index_name);
      spdlog::debug(response.text);
    } else
    {
      spdlog::error("Problem creating index '{}'?? Response status code: {}", index_name, response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  // Delete the Elasticsearch index?!
  if (args["delete"].asBool())
  {
    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const index_name = es_client->index_name();

    spdlog::warn("Deleting Elasticsearch index '{}'...", index_name);

    auto const response = es_client->delete_index();

    if (response.status_code == 200)
    {
      spdlog::info("Successfully deleted index '{}'", index_name);
      spdlog::debug(response.text);
    } else
    {
      spdlog::error("Problem deleting index '{}'?? Response status code: {}", index_name, response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  // Ping the Elasticsearch cluster?
  if (args["ping"].asBool())
  {
    spdlog::info("Checking connection to Elasticsearch endpoint...");

    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const response = es_client->ping();

    if (response.status_code == 200)
    {
      spdlog::info("Established connection to Elasticsearch.");
    } else
    {
      spdlog::error("Unable to establish connection to Elasticsearch endpoint! Response status code: {}", response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  // Check info about an Elasticsearch user?
  if (args["info"].isBool())
  {
    if (args["info"].asBool())
    {
      spdlog::info("Checking info on all Elasticsearch users...");

      auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

      auto const response = es_client->get_user_info();

      if (response.status_code == 200)
      {
        spdlog::info("Retrieved all user info:");
        spdlog::info(response.text);
      } else
      {
        spdlog::error("Unable to establish connection to Elasticsearch endpoint! Response status code: {}", response.status_code);
        spdlog::debug(response.text);
      }

      return EXIT_SUCCESS;
    }
  } else if (args["info"].isString())
  {
    auto const username = args["info"].asString();

    spdlog::info("Checking info on Elasticsearch user '{}'...", username);

    auto es_client = std::make_unique<csgoprs::es::client>(config_json["elasticsearch"]);

    auto const response = es_client->get_user_info(username);

    if (response.status_code == 200)
    {
      spdlog::info("Retrieved user info for '{}':", username);
      spdlog::info(response.text);
    } else
    {
      spdlog::error("Unable to establish connection to Elasticsearch endpoint! Response status code: {}", response.status_code);
      spdlog::debug(response.text);
    }

    return EXIT_SUCCESS;
  }


  return EXIT_SUCCESS;
}
