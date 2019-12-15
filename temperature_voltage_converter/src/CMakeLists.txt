add_library(temperature-voltage-converter)
target_sources(temperature-voltage-converter
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
target_include_directories(temperature-voltage-converter
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
   )
target_link_libraries(temperature-voltage-converter
   nlohmann_json::nlohmann_json
   units
   )
target_compile_options(temperature-voltage-converter
   PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
         -Wall -Wextra -Werror>
      $<$<CXX_COMPILER_ID:MSVC>:
         /W4 /WX>
   )