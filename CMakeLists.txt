cmake_minimum_required(VERSION 3.15...3.18)

# Set up our project
project(
  csgoparse
  VERSION 0.1.0
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

# Find the PlatformFolders library
find_package(platform_folders REQUIRED)

# Find the Hamarr library
find_package(hamarr CONFIG REQUIRED)

# Get Conan up and running
include(cmake/Conan.cmake)
run_conan()

# Add the include directory to the target
target_include_directories(
  ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                          ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog
          sago::platform_folders hamarr::hamarr)
