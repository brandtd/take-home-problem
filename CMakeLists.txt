cmake_minimum_required(VERSION 3.0.0)
project(value-convert VERSION 0.1.0)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(3rdParty/json)

set(BUILD_TESTS OFF CACHE INTERNAL "")
add_subdirectory(3rdParty/units)

include(CTest)
enable_testing()

# Need c++11 for the JSON library
# Need c++14 for the units library
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(value-convert
   main.cpp
   data-point.cpp)
target_link_libraries(value-convert
   nlohmann_json::nlohmann_json
   units)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
