cmake_minimum_required(VERSION 3.0.0)
project(unit_tests VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories( ${CMAKE_SOURCE_DIR}/include )
add_executable(unit_tests bst.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
