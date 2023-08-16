cmake_minimum_required(VERSION 3.22.1)
project(echo CXX)

message("configuration begin")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "debug")
endif()
message("cmake build type: ${CMAKE_BUILD_TYPE}")

if(NOT MUDUO_PATH)
  set(MUDUO_PATH "$ENV{HOME}/build/${CMAKE_BUILD_TYPE}-install-cpp11")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_GENERATOR "Ninja")

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -Wall
 -Wextra
 # -m32
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -finline-limit=1000 -DNDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2  -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message(STATUS "exe output path: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "lib output path: ${LIBRARY_OUTPUT_PATH}")

find_path(Muduo_INCLUDE_DIR muduo "${MUDUO_PATH}/include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${MUDUO_PATH}/lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
message(STATUS "muduo include path: ${Muduo_INCLUDE_DIR}")
message(STATUS "muduo library path: ${Muduo_LIBRARY_DIR}")


include_directories(${Muduo_INCLUDE_DIR})
find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
message(STATUS "muduo base: ${muduo_base}")
message(STATUS "muduo net: ${muduo_net}")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})

add_executable(echo ../src/echo.cc)
target_link_libraries(echo ${muduo_net})
target_link_libraries(echo ${muduo_base})
target_link_libraries(echo pthread rt)

add_executable(hello-server ../src/hello-server.cc)
add_executable(hello-client ../src/hello-client.cc)

message("configuration end")


