cmake_minimum_required(VERSION 3.0.0)
project(puzzles VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

include_directories( include 
                     build/googletest-src/googletest/include 
                     build/googletest-src/googlemock/include
                    )

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(puzzles
               intersection.cpp
               to_and_from_roman.cpp
              )
           
target_link_libraries(puzzles gtest_main)
# add_test(NAME puzzles COMMAND puzzles)
