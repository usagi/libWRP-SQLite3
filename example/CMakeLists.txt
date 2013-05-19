cmake_minimum_required(VERSION 2.8.10)

project(example)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_GENERATOR "Ninja")

# use clang++ with threading is very hard for now
# set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS       "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS            "-Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-pedantic-errors ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS          "-Werror ${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -march=native ${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_PROFILE "-pg ${CMAKE_CXX_FLAGS_PROFILE}")
set(CMAKE_LD_FLAGS_PROFILE "-lgmon ${CMAKE_LD_FLAGS_PROFILE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(example_01 "example_01.cxx")

target_link_libraries(example_01 sqlite3)
target_link_libraries(example_01 debug glog)

add_executable(example_02 "example_02.cxx")

target_link_libraries(example_02 sqlite3)
target_link_libraries(example_02 debug glog)

