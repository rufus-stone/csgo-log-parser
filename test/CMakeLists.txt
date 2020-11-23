message(STATUS "Building csgoparse_tests...")

add_library(catch_main STATIC catch_main.cpp)

add_executable(csgoparse_tests tests.cpp)
target_compile_features(csgoparse_tests PRIVATE cxx_std_17)

# Add the include directory and external directory to the target
target_include_directories(
  csgoparse_tests PRIVATE ${PROJECT_SOURCE_DIR}/include
                          ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  csgoparse_tests PRIVATE docopt spdlog::spdlog sago::platform_folders
                          hamarr::hamarr cpr::cpr)
