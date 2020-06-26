#pragma once

#include <fstream> // For file i/o
#include <filesystem> // For filesystem stuff
#include <cstdlib> // For getting the path to the home directory

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
  std::filesystem::path log_dir_path;
  std::filesystem::path log_path;

public:
  reader() = delete;
  reader(const std::filesystem::path &log_dir);
  ~reader() = default;

  auto get_latest_bundle(std::streamoff offset) -> bundle;
};

reader::reader(const std::filesystem::path &log_dir) : log_dir_path(log_dir)
{
  // Does the path actually exist/can we see it?
  if (!std::filesystem::exists(log_dir_path))
  {
    std::cerr << "Couldn't find " << log_dir_path << " !!\n";
    return;
  }

  // Is it actually a directory?
  if (!std::filesystem::is_directory(log_dir_path))
  {
    std::cerr << log_dir_path << " is not a directory !!\n";
    return;
  }

  // List the files in the directory
  auto files = std::vector<std::filesystem::path>{};
  for (const auto &entry : std::filesystem::directory_iterator(log_dir_path))
  {
    if (std::filesystem::is_regular_file(entry))
    {
      files.push_back(entry.path());
    }
  }

  // Did we find any files?
  if (files.empty())
  {
    std::cerr << log_dir_path << " does not contain any regular files !!\n";
    return;
  }

  // Sort the files by name descending in order to find the most recent log file (CS:GO log files include the date at the start of the filename)
  std::sort(std::begin(files), std::end(files), std::greater<>());
  std::cout << files[0] << '\n';
  
  this->log_path = files[0];
}

auto reader::get_latest_bundle(std::streamoff start_position) -> bundle
{
  using namespace std::chrono_literals;

  auto logfile = std::ifstream{this->log_path, std::ios::binary};

  int file_length = 0;
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
    if (start_position > file_length)
    {
      std::cerr << "Start position " << start_position << " is greater than file size " << file_length << " !!\n";
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