add_library(take-home)
target_sources(take-home
   PRIVATE
      calibration_point_file.cpp
      calibration_point.cpp
      temperature_voltage_converter.cpp
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/calibration_point_file.h
      ${CMAKE_CURRENT_LIST_DIR}/calibration_point.h
      ${CMAKE_CURRENT_LIST_DIR}/result_code_enum.h
      ${CMAKE_CURRENT_LIST_DIR}/i_temperature_voltage_converter.h
      ${CMAKE_CURRENT_LIST_DIR}/temperature_voltage_converter.h
   )
target_include_directories(take-home
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
   )
target_link_libraries(take-home
   nlohmann_json::nlohmann_json
   units
   )
target_compile_options(take-home
   PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
         -Wall -Wextra -Werror>
      $<$<CXX_COMPILER_ID:MSVC>:
         /W4 /WX>
   )

add_executable(value-convert
   example_main.cpp)
target_link_libraries(value-convert
   nlohmann_json::nlohmann_json
   units
   take-home)
target_compile_options(value-convert PRIVATE
   $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall -Wextra -Werror>
   $<$<CXX_COMPILER_ID:MSVC>:
      /W4 /WX>
   )