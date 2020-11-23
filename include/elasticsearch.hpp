#pragma once

#include <string>
#include <string_view>

#include <cpr/cpr.h>
#include <hamarr/format.hpp>
#include <hamarr/base64.hpp>

#include "nlohmann/json.hpp"

namespace csgoprs::es
{

using namespace std::string_literals;
using namespace std::string_view_literals;

using json = nlohmann::json;

constexpr auto csgo_mappings = R"({
  "mappings" : {
    "properties" : {
      "timestamp" : {
        "type" : "date",
        "format" : "epoch_millis"
      },
      "event_type" : {"type" : "keyword", "index" : "true"},
      "player" : {"type" : "keyword", "index" : "true"},
      "player_id" : {"type" : "keyword", "index" : "true"},
      "player_team" : {"type" : "keyword", "index" : "true"},
      "player_position" : {"type" : "geo_point"},
      "victim" : {"type" : "keyword", "index" : "true"},
      "victim_id" : {"type" : "keyword", "index" : "true"},
      "victim_team" : {"type" : "keyword", "index" : "true"},
      "victim_position" : {"type" : "geo_point"},
      "distance" : {"type" : "integer"},
      "weapon" : {"type" : "keyword", "index" : "true"},
      "damage_health" : {"type" : "integer"},
      "damage_armor" : {"type" : "integer"},
      "health_remaining" : {"type" : "integer"},
      "armor_remaining" : {"type" : "integer"},
      "bodypart_hit" : {"type" : "keyword", "index" : "true"},
      "self_inflicted" : {"type" : "boolean", "index" : "true"},
      "flair" : {"type" : "keyword"},
      "game_map" : {"type" : "keyword", "index" : "true"},
      "game_mode" : {"type" : "keyword", "index" : "true"},
      "game_duration" : {"type" : "integer"},
      "blinded" : {"type" : "float"},
    }
  }
})"sv;


class client
{
private:
  cpr::Url endpoint;
  cpr::Header auth;
  std::string index;

  // HTTP Methods
  auto get(cpr::Url url) -> cpr::Response;
  auto post(cpr::Url url, cpr::Payload payload) -> cpr::Response;
  auto post(cpr::Url url, cpr::Body body) -> cpr::Response;
  auto put(cpr::Url url, cpr::Payload payload) -> cpr::Response;
  auto put(cpr::Url url, cpr::Body body) -> cpr::Response;
  auto del(cpr::Url url) -> cpr::Response;
  auto head(cpr::Url url) -> cpr::Response;

public:
  client() = delete;
  client(json const &cfg);
  ~client() = default;

  auto ping() -> cpr::Response;

  // Create
  auto create_index_with_mappings(json index_mappings = csgo_mappings) -> cpr::Response;

  // Read
  auto get_indices() -> cpr::Response;
  auto get_mapping() -> cpr::Response;
  auto index_exists() -> cpr::Response;
  auto sample_index() -> cpr::Response;

  // Update
  auto index_event(json event_json) -> cpr::Response;
  auto index_bulk_events(json events_json) -> cpr::Response;

  // Delete
  auto delete_index() -> cpr::Response;
};

////////////////////////////////////////////////////////////////
client::client(json const &cfg)
{
  spdlog::debug(cfg.dump(2));

  auto get_value = [&cfg](std::string const &key) {
    if (cfg.contains(key))
    {
      return cfg[key].get<std::string>();
    } else
    {
      return std::string{};
    }
  };

  // Endpoint config
  auto const cfg_cloud_id = get_value("cloud_id");
  auto const cfg_port = get_value("port");
  auto const cfg_endpoint = get_value("endpoint");

  // Auth config
  auto const cfg_username = get_value("username");
  auto const cfg_password = get_value("password");
  auto const cfg_api_key = get_value("api_key");

  // Index config
  auto const cfg_index = get_value("index");
  this->index = cfg_index;

  // Prefer cloud_id + port over endpoint
  if (!cfg_cloud_id.empty() && !cfg_port.empty())
  {
    auto const cloud_id_parts = hmr::format::split(hmr::base64::decode(hmr::format::split(cfg_cloud_id, ':')[1]), '$');

    if (cloud_id_parts.size() == 3)
    {
      this->endpoint = cpr::Url{"https://" + cloud_id_parts[1] + "." + cloud_id_parts[0] + ":" + cfg_port + "/"};
      spdlog::debug("Cloud ID Endpoint: {}", this->endpoint.str());
    }

  } else if (!cfg_endpoint.empty())
  {
    this->endpoint = cpr::Url{cfg_endpoint};
    spdlog::debug("Regular Endpoint: {}", this->endpoint.str());

  } else
  {
    spdlog::warn("Elasticsearch client requires either cloud_id + port or endpoint!");
  }

  // Prefer API Key over username/password
  if (!cfg_api_key.empty())
  {
    this->auth = cpr::Header{{"Authorization", "ApiKey "s + hmr::base64::encode(cfg_api_key)}};

    spdlog::debug("API Key: {}", cfg_api_key);

  } else if (!cfg_username.empty() && !cfg_password.empty())
  {
    this->auth = cpr::Header{{"Authorization", "Basic " + hmr::base64::encode(cfg_username + ":" + cfg_password)}};

    spdlog::debug("Username: {} / Password: {}", cfg_username, cfg_password);

  } else
  {
    spdlog::warn("Elasticsearch client requires either an API key or username + password!");
  }
}


////////////////////////////////////////////////////////////////
auto client::get(cpr::Url url) -> cpr::Response
{
  return cpr::Get(url, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::post(cpr::Url url, cpr::Payload payload) -> cpr::Response
{
  return cpr::Post(url, payload, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::post(cpr::Url url, cpr::Body body) -> cpr::Response
{
  return cpr::Post(url, body, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::put(cpr::Url url, cpr::Payload payload) -> cpr::Response
{
  return cpr::Put(url, payload, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::put(cpr::Url url, cpr::Body body) -> cpr::Response
{
  return cpr::Put(url, body, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::del(cpr::Url url) -> cpr::Response
{
  return cpr::Delete(url, this->auth, cpr::VerifySsl{false});
}

////////////////////////////////////////////////////////////////
auto client::head(cpr::Url url) -> cpr::Response
{
  return cpr::Head(url, this->auth, cpr::VerifySsl{false});
}


////////////////////////////////////////////////////////////////
auto client::ping() -> cpr::Response
{
  auto r = this->get(this->endpoint);

  spdlog::debug(r.status_code);
  spdlog::debug(r.text);

  return r;
}


////////////////////////////////////////////////////////////////
auto client::create_index_with_mappings(json index_mappings) -> cpr::Response
{
  auto r = this->put(this->endpoint + this->index, cpr::Body{index_mappings.dump(2)});

  spdlog::debug(r.status_code);
  spdlog::debug(r.text);

  return r;
}


////////////////////////////////////////////////////////////////
auto client::index_bulk_events(json events_json) -> cpr::Response
{
  if (!events_json.is_null() && events_json.is_array())
  {
    spdlog::debug("Indexing {} events...", events_json.size());
  }

  return cpr::Response{};
}


////////////////////////////////////////////////////////////////
auto client::get_indices() -> cpr::Response
{
  auto r = this->get(this->endpoint + "_cat/indices");

  spdlog::debug(r.text);

  return r;
}


////////////////////////////////////////////////////////////////
auto client::get_mapping() -> cpr::Response
{
  auto r = this->get(this->endpoint + this->index + "/_mapping");

  spdlog::debug(r.status_code);
  spdlog::debug(r.text);

  return r;
}


////////////////////////////////////////////////////////////////
auto client::sample_index() -> cpr::Response
{
  auto r = this->get(this->endpoint + this->index + "/_search");

  spdlog::debug(r.status_code);
  spdlog::debug(r.text);

  return r;
}


////////////////////////////////////////////////////////////////
auto client::index_exists() -> cpr::Response
{
  auto r = this->head(this->endpoint + this->index);

  spdlog::debug(r.status_code);

  return r;
}

////////////////////////////////////////////////////////////////
auto client::delete_index() -> cpr::Response
{
  auto r = this->del(this->endpoint + this->index);

  spdlog::debug(r.status_code);
  spdlog::debug(r.text);

  return r;
}

} // namespace csgoprs::es
