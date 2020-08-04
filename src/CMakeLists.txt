include_directories(${PROJECT_SOURCE_DIR}/include)

# Generic test that uses conan libs
add_executable(csgoparse main.cpp)
target_link_libraries(
  csgoparse PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt CONAN_PKG::spdlog)