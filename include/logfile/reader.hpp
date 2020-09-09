#pragma once

#include <fstream> // For file i/o
#include <filesystem> // For filesystem stuff
#include <cstdlib> // For getting the path to the home directory

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <optional>

#include <spdlog/spdlog.h>

namespace csgoprs::logs
{

struct bundle
{
  std::vector<std::string> lines;
  std::streamoff pos;
};

class reader
{
private:
  std::filesystem::path log_path;

public:
  reader() = delete;
  reader(const std::filesystem::path &log_dir);
  ~reader() = default;

  auto get_latest_bundle(std::streamoff offset) -> bundle;
};

reader::reader(const std::filesystem::path &log_dir)
{
  // Does the path actually exist/can we see it?
  if (!std::filesystem::exists(log_dir))
  {
    spdlog::error("Couldn't find log directory: {}", log_dir.string());
    return;
  }

  // Is it actually a directory?
  if (!std::filesystem::is_directory(log_dir))
  {
    spdlog::error("{} is not a directory", log_dir.string());
    return;
  }

  // List all the regular files in the directory
  auto files = std::vector<std::filesystem::path>{};
  for (const auto &entry : std::filesystem::directory_iterator(log_dir))
  {
    if (std::filesystem::is_regular_file(entry))
    {
      files.push_back(entry.path());
    }
  }

  // Did we find any files?
  if (files.empty())
  {
    spdlog::error("{} does not contain any regular files", log_dir.string());
    return;
  }

  // Sort the files by name descending in order to find the most recent log file (CS:GO log files include the date at the start of the filename)
  std::sort(std::begin(files), std::end(files), std::greater<>());
  spdlog::info("Most recent log file: {} ", files[0].string());

  this->log_path = files[0];
}

auto reader::get_latest_bundle(std::streamoff start_position) -> bundle
{
  using namespace std::chrono_literals;

  auto logfile = std::ifstream{this->log_path, std::ios::binary};

  std::size_t file_length = 0;
  std::streamoff pos;

  auto line = std::string{};
  auto lines = std::vector<std::string>{};

  // Open the file if needed
  if (!logfile.is_open())
  {
    logfile = std::ifstream{this->log_path, std::ios::binary};
  }

  if (logfile.is_open())
  {
    // Check how big the file is now
    file_length = std::filesystem::file_size(this->log_path);

    // Double check nothing funky has happened to the file size
    if (start_position > static_cast<std::streamoff>(file_length))
    {
      spdlog::error("Start position {} is greater than file size {}", start_position, file_length);
      std::exit(EXIT_FAILURE);
    }

    // Skip ahead to where we stopped reading last time around
    logfile.seekg(start_position, logfile.beg);

    // Add each line to the lines vector
    while (std::getline(logfile, line))
    {
      lines.push_back(line);
      pos = logfile.tellg();
    }

    // Close the file
    logfile.close();

    // Return the bundle
    return bundle{lines, pos};
  }

  return bundle{};
}

} // namespace csgoprs::logs