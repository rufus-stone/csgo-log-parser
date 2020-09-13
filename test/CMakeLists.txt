message(STATUS "Building tests...")

add_library(catch_main STATIC catch_main.cpp)

add_executable(tests tests.cpp)
target_compile_features(tests PRIVATE cxx_std_17)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Find the PlatformFolders library
find_package(platform_folders REQUIRED)

# Find the Hamarr library
find_package(hamarr CONFIG REQUIRED)

# Add the include directory to the target
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include
                                         ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  tests PRIVATE CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog
                sago::platform_folders catch_main)
