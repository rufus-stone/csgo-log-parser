message(STATUS "Building csgoparse_tests...")

add_library(catch_main STATIC catch_main.cpp)

add_executable(csgoparse_tests tests.cpp)
target_compile_features(csgoparse_tests PRIVATE cxx_std_17)


if(NOT platform_folders_FOUND)
message("No platform_folders_FOUND for tests!")
endif()

# Add the include directory to the target
target_include_directories(csgoparse_tests PRIVATE ${PROJECT_SOURCE_DIR}/include
                                         ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  csgoparse_tests PRIVATE docopt spdlog::spdlog sago::platform_folders
                          hamarr::hamarr)

get_target_property(csgoparse_tests_INCLUDE_DIRS csgoparse_tests INCLUDE_DIRECTORIES)
message("csgoparse_tests_INCLUDE_DIRS: ${csgoparse_tests_INCLUDE_DIRS}")