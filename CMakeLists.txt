cmake_minimum_required(VERSION 3.0.0)
project(value-convert VERSION 0.1.0)

# Need c++11 for the JSON library
# Need c++14 for the units library
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_TESTS OFF CACHE INTERNAL "")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(3rdParty/json)
add_subdirectory(3rdParty/units)
add_subdirectory(3rdParty/gtest)

include(CTest)
enable_testing()

add_subdirectory(temperature_voltage_converter)
add_subdirectory(take_home_problem)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
