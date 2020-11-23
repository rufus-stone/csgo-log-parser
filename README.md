# csgo-log-parser

![Build and Test](https://github.com/rufus-stone/csgo-log-parser/workflows/Build%20and%20Test/badge.svg)

A log parser for Counter Strike: Global Offensive

## Motivation

CS:GO dedicated servers can write game logs to a file. These contain details about actions that occured in the game, such as a player attacking another player, getting a kill or assist, planting/defusing the bomb, rescuing a hostage, etc. Even chicken deaths are logged!

## Installation

The simplest way to build from source is using CMake (version 3.15 or above is required). For example:

```sh
git clone git@github.com:rufus-stone/csgo-log-parser.git

cd csgo-log-parser

# Get CMake to create a new build directory
cmake -S . -B build

# Build the app
cmake --build build
```

### Requirements

csgoparse requires the following libraries:

- [platform_folders](https://github.com/sago007/PlatformFolders)
- [hamarr](https://github.com/rufus-stone/hamarr)
- [docopt](https://github.com/docopt/docopt.cpp)
- [spdlog](https://github.com/gabime/spdlog)

If these are not already installed on your system, CMake will fetch them from GitHub for you

## Configuration

csgoparse loads settings from a config.json file, which, if necessary, it creates the first time the program runs.

### Barebones

The barebones config.json looks like this:

```json
{
  "log_dir": null
}
```

Out of the box, this requires modification by the user to tell csgoparse which directory contains your game server logs (e.g. `<server install dir>/server/logs`), so update the `"log_dir"` entry with a string specifying the path to your server log directory (fully qualified paths only; no '~' appreviations or similar!). For example, on Linux:

```json
{
  "log_dir": "/home/somebody/csgo/server/logs"
}
```

### Steam ID translation

Because CS:GO server logs use a player's Steam ID to differentiate between players, and because a player can freely change their display name in-game, csgoparse also uses the Steam ID to identify players when tracking stats. However, should you wish, you can tell csgoparse to translate specific Steam IDs into some other text, as this may make player-specific searches in programs like Elasticsearch/Kibana easier. In this way, it does not matter whether a player changes their in-game display name, csgoparse will continue to track their stats via their Steam ID, but output events containing whatever alternative name you specified in the config.json file. For example:

```json
{
  "log_dir": "/home/somebody/csgo/server/logs",
  "steam_id_translation": {
    "active": true,
    "translations": {
      "STEAM_1:0:12345678": "Alice",
      "STEAM_1:1:87654321": "Bob"
    }
  }
}
```

The config above will ensure that, should csgoparse process a server log line containing references to Steam ID "STEAM_1:0:12345678", it will replace this with the name "Alice" when generating output JSON. Likewise, "STEAM_1:1:87654321" will be translated to "Bob". The `"active"` setting can be changed to `false` in order to disable the Steam ID translation functionality.

### Elasticsearch setup -- WORK IN PROGRESS !!

You can configure csgoparse to connect to an elasticsearch instance of your choosing. For example:

```json
{
  "log_dir": "/home/somebody/csgo/server/logs",
  "elasticsearch": {
    "cloud_id": "<your elastic cloud_id>",
    "port": 9243,
    "username": "<your elasticsearch username>",
    "password": "<your elasticsearch password>",
    "index": "<elasticsearch index name>"
  }
}
```


## CS:GO server configuration

csgoparse currently expects CS:GO server logs to be created using the maximum logging verbosity level
