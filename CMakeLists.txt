cmake_minimum_required(VERSION 3.25)
project(cmake-test-arrow VERSION 0.0.1)

# -------------------------------------------------------------------------------
# C++ build options
# -------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")
add_compile_options(-march=native -Wall -Wextra)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------------------------------------
# Dependencies
# -------------------------------------------------------------------------------

include("${CMAKE_SOURCE_DIR}/libs/arrow.cmake")

# -------------------------------------------------------------------------------
# Library build
# -------------------------------------------------------------------------------

file(GLOB_RECURSE AW_SRC src/**.cpp)
file(GLOB_RECURSE AW_HH include/**.hpp)

add_library(
  arrow-wrapper
  ${AW_SRC}
  ${AW_HH}
)

target_include_directories(arrow-wrapper PRIVATE include)

target_link_libraries(arrow-wrapper Arrow)