cmake_minimum_required(VERSION 3.0.0)
project(unit_tests VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

include_directories( include build/googletest-src/googletest/include build/googletest-src/googlemock/include)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(unit_tests 
            bst.cpp
            sll.cpp
            test_heap.cpp)
           
target_link_libraries(unit_tests gtest_main)
add_test(NAME unit_tests COMMAND unit_tests)
