# csgo-log-parser
Log parser for Counter Strike: Global Offensive

## Configuration

csgoparse loads settings from a config.json file, which, if necessary, it creates the first time the program runs.

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

Because CS:GO server logs use a player's Steam ID as a unique identifier to differentiate between players, and because a player can freely change their display name in-game, csgoparse also uses the Steam ID to identify players when tracking stats. However, should you wish, you can tell csgoparse to translate specific Steam IDs into some other text, as this may make player-specific queries in tools like Elasticsearch/Kibana easier. In this way, it does not matter whether a player changes their in-game display name, csgoparse will continue to track their stats via their Steam ID, but output events containing whatever alternative name you specified in the config.json file. For example:

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

The config above will ensure that, should csgoparse process a server log line containing references to Steam ID "STEAM_1:0:12345678", it will replace this with the name "Alice" when outputing events. Likewise, "STEAM_1:1:87654321" will be translated to "Bob". The `"active"` setting can be changed to `false` in order to disable the Steam ID translation functionality.
