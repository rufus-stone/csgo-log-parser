message(STATUS "Building tests...")

add_library(catch_main STATIC catch_main.cpp)

add_executable(tests tests.cpp)
target_compile_features(tests PRIVATE cxx_std_17)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# In case we need to fetch any missing libraries
include(FetchContent)

# Find the PlatformFolders library
find_package(platform_folders)
if(NOT platform_folders_FOUND)
  FetchContent_Declare(
    platform_folders
    GIT_REPOSITORY https://github.com/sago007/PlatformFolders.git
    GIT_TAG d318731b37ebbeb6ff8fd03e4de3e6b45130b189)
  FetchContent_MakeAvailable(platform_folders)
endif()

# Find the Hamarr library
find_package(hamarr CONFIG)
if(NOT hamarr_FOUND)
  FetchContent_Declare(
    hamarr
    GIT_REPOSITORY https://github.com/rufus-stone/hamarr.git
    GIT_TAG 902048cdb1ab27587e7271cc7e82cd595798a8d6)
  FetchContent_MakeAvailable(hamarr)
endif()

# Find the docopt library
find_package(docopt)
if(NOT docopt_FOUND)
  message("Failed to find docopt!")
  FetchContent_Declare(
    docopt
    GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
    GIT_TAG 42ebcec9dc2c99a1b3a4542787572045763ad196) # 0.6.3
  FetchContent_MakeAvailable(docopt)
endif()

# Find the spdlog library
find_package(spdlog)
if(NOT spdlog_FOUND)
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG cbe9448650176797739dbab13961ef4c07f4290f)
  FetchContent_MakeAvailable(spdlog)
endif()

# Add the include directory to the target
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include
                                         ${PROJECT_SOURCE_DIR}/external)

# Link libraries to executable
target_link_libraries(
  tests PRIVATE docopt spdlog::spdlog sago::platform_folders
                          hamarr::hamarr)
