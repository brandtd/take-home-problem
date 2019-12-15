file(COPY DataSheetCalibrationPoints.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(DATASHEET_JSON_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/DataSheetCalibrationPoints.json)
configure_file(calibration_file_location.cpp.in calibration_file_location.cpp @ONLY)

add_executable(take_home_problem_tests
   ${CMAKE_CURRENT_BINARY_DIR}/calibration_file_location.cpp

   test_take_home_problem.cpp
)
target_include_directories(take_home_problem_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(take_home_problem_tests
   requested-interface
   gtest_main
)
add_test(NAME take_home_test_points COMMAND take_home_problem_tests)