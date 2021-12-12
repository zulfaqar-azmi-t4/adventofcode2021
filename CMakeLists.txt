cmake_minimum_required(VERSION 3.17)
project(advent_of_code)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
# If dependencies are managed with conan, we prepend the current build folder
# to the CMake module path, where CMake looks for dependencies.
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
  list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
endif()
find_package(DataFrame)
find_package(range-v3)
find_package(fmt)
find_package(Boost)

include_directories(
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/input)

add_executable(day1 src/day1.cpp)
add_executable(day2 src/day2.cpp)
add_executable(day3 src/day3.cpp)
add_executable(day4 src/day4.cpp)

target_compile_features(day2
  PRIVATE
  cxx_std_20
  )
target_link_libraries(day2
  PRIVATE
  DataFrame::DataFrame
  fmt::fmt
  range-v3::range-v3
  )

target_compile_features(day3
  PRIVATE
  cxx_std_20
  )
target_link_libraries(day3
  PRIVATE
  DataFrame::DataFrame
  fmt::fmt
  range-v3::range-v3
  )

target_compile_features(day4
  PRIVATE
  cxx_std_20
  )
target_link_libraries(day4
  PRIVATE
  DataFrame::DataFrame
  fmt::fmt
  range-v3::range-v3
  Boost::boost
  )
