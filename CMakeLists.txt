cmake_minimum_required(VERSION 3.0.0)
project(csgoparse VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)

add_executable(csgoparse main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_compile_features(csgoparse PUBLIC cxx_std_17)
