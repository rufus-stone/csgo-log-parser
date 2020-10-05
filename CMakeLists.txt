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
find_package(platform_folders)
if(NOT platform_folders_FOUND)
  message("Failed to find platform_folders! Fetching it instead...")
  FetchContent_Declare(
    platform_folders
    GIT_REPOSITORY https://github.com/sago007/PlatformFolders.git
    GIT_TAG d318731b37ebbeb6ff8fd03e4de3e6b45130b189)
  FetchContent_MakeAvailable(platform_folders)
endif()

# Find the Hamarr library
find_package(hamarr CONFIG)
if(NOT hamarr_FOUND)
  message("Failed to find Hamarr! Fetching it instead...")
  set(BUILD_HAMARR_TESTS
      OFF
      CACHE INTERNAL "")
  FetchContent_Declare(
    hamarr
    GIT_REPOSITORY https://github.com/rufus-stone/hamarr.git
    GIT_TAG 902048cdb1ab27587e7271cc7e82cd595798a8d6)
  FetchContent_MakeAvailable(hamarr)
endif()

# Find the docopt library
find_package(docopt)
if(NOT docopt_FOUND)
  message("Failed to find docopt! Fetching it instead...")
  FetchContent_Declare(
    docopt
    GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
    GIT_TAG 42ebcec9dc2c99a1b3a4542787572045763ad196)
  FetchContent_MakeAvailable(docopt)
endif()

# Find the spdlog library
find_package(spdlog)
if(NOT spdlog_FOUND)
  message("Failed to find spdlog! Fetching it instead...")
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG cbe9448650176797739dbab13961ef4c07f4290f)
  FetchContent_MakeAvailable(spdlog)
endif()

# Add the include directory to the target
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
