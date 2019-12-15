file(COPY LoadFileTest_ValidFile.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY LoadFileTest_InvalidFile.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(VALID_JSON_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/LoadFileTest_ValidFile.json)
set(INVALID_JSON_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/LoadFileTest_InvalidFile.json)
configure_file(test_file_locations.cpp.in test_file_locations.cpp @ONLY)

add_executable(unit_tests
   ${CMAKE_CURRENT_BINARY_DIR}/test_file_locations.cpp

   calibration_point_file_tests.cpp
   test_cases_multipoint_temperature_interpolation.cpp
   test_cases_multipoint_voltage_interpolation.cpp
   test_cases_out_of_order_calibration_points.cpp
   test_cases_two_point_temperature_interpolation.cpp
   test_cases_two_point_voltage_interpolation.cpp
   test_converts_temperature_to_voltage.cpp
   test_converts_voltage_to_temperature.cpp
   test_not_enough_calibration_points.cpp
)
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(unit_tests
   temperature-voltage-converter
   gtest_main
)
add_test(NAME converter_tests COMMAND unit_tests)