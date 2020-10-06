cmake_minimum_required(VERSION 3.15...3.18)

# Set up our project
project(
  csgoparse
  VERSION 0.2.0
  DESCRIPTION "A log parser for CS:GO server logs"
  HOMEPAGE_URL "https://github.com/rufus-stone/csgo-log-parser"
  LANGUAGES CXX)

# Create our executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Disallow in-source builds
include(cmake/PreventInSourceBuilds.cmake)

# Enable cache system
include(cmake/Cache.cmake)

# We're using C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set our compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

# Enable sanitizers if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_NAME})

# Allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# In case we need to fetch any missing libraries
include(FetchContent)

# Find the PlatformFolders library
find_package(platform_folders QUIET)
if(NOT platform_folders_FOUND)
  message("Failed to find platform_folders! Fetching it instead...")

  # Get a specific release of PlatformFolders
  # (d318731b37ebbeb6ff8fd03e4de3e6b45130b189)
  FetchContent_Declare(
    platform_folders
    GIT_REPOSITORY https://github.com/sago007/PlatformFolders.git
    GIT_TAG d318731b37ebbeb6ff8fd03e4de3e6b45130b189)

  FetchContent_MakeAvailable(platform_folders)

  message("platform_folders_SOURCE_DIR: ${platform_folders_SOURCE_DIR}")

  # When installed at the system level, platform_folders is normally included
  # like this: #include <sago/platform_folders.h> When using FetchContent, for
  # some reason platform_folders is normally included like this: #include
  # <platform_folders.h> If we include_directories() for the
  # platform_folders_SOURCE_DIR when FetchContent has been used, we can preserve
  # the format: #include <sago/platform_folders.h>
  include_directories(${platform_folders_SOURCE_DIR})
endif()

# Find the Hamarr library
find_package(hamarr CONFIG QUIET)
if(NOT hamarr_FOUND)
  message("Failed to find Hamarr! Fetching it instead...")

  # Don't build the Hamarr tests
  set(BUILD_HAMARR_TESTS
      OFF
      CACHE INTERNAL "")

  # Get the most recent version of Hamarr available
  FetchContent_Declare(hamarr
                       GIT_REPOSITORY https://github.com/rufus-stone/hamarr.git)

  FetchContent_MakeAvailable(hamarr)
  message("hamarr_SOURCE_DIR: ${hamarr_SOURCE_DIR}")
endif()

# Find the docopt library
find_package(docopt QUIET)
if(NOT docopt_FOUND)
  message("Failed to find docopt! Fetching it instead...")

  # Get a specific release of docopt (42ebcec9dc2c99a1b3a4542787572045763ad196)
  FetchContent_Declare(
    docopt
    GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
    GIT_TAG 42ebcec9dc2c99a1b3a4542787572045763ad196)

  FetchContent_MakeAvailable(docopt)

  message("docopt_SOURCE_DIR: ${docopt_SOURCE_DIR}")
endif()

# Find the spdlog library
find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
  message("Failed to find spdlog! Fetching it instead...")

  # Get a specific release of spdlog (cbe9448650176797739dbab13961ef4c07f4290f)
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG cbe9448650176797739dbab13961ef4c07f4290f)

  FetchContent_MakeAvailable(spdlog)

  message("spdlog_SOURCE_DIR: ${spdlog_SOURCE_DIR}")
endif()

# Add the include directory and external directory to the target
target_include_directories(
  ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                          ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  ${PROJECT_NAME} PRIVATE docopt spdlog::spdlog sago::platform_folders
                          hamarr::hamarr)

include(CTest) # This adds the BUILD_TESTING option (ON by default)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test ${PROJECT_BUILD_DIR})
endif()

get_target_property(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_NAME}
                    INCLUDE_DIRECTORIES)
message("${PROJECT_NAME}_INCLUDE_DIRS: ${${PROJECT_NAME}_INCLUDE_DIRS}")
