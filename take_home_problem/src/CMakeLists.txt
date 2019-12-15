add_library(requested-interface)
target_sources(requested-interface
   PRIVATE
      requested_converter_interface.cpp
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/requested_converter_interface.h
   )
target_include_directories(requested-interface
   PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}
   )
target_link_libraries(requested-interface
   temperature-voltage-converter
   )
target_compile_options(requested-interface
   PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
         -Wall -Wextra -Werror>
      $<$<CXX_COMPILER_ID:MSVC>:
         /W4 /WX>
   )

add_executable(example-main
   example_main.cpp)
target_link_libraries(example-main
   requested-interface)
target_compile_options(example-main PRIVATE
   $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall -Wextra -Werror>
   $<$<CXX_COMPILER_ID:MSVC>:
      /W4 /WX>
   )