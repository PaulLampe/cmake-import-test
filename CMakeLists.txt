cmake_minimum_required(VERSION 3.25)
project(arrow-wrapper VERSION 0.0.1)

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

file(GLOB_RECURSE AW_CC src/**.cpp src/**/**.cpp)
file(GLOB_RECURSE AW_HH src/**.hpp src/**/**.hpp)

set(AW_PUBLIC_HEADERS src/api.h)

add_library(${PROJECT_NAME} STATIC)

target_sources(
  ${PROJECT_NAME}
  PRIVATE ${AW_CC} ${AW_HH}
  PUBLIC ${AW_PUBLIC_HEADERS}
)

target_link_libraries(arrow-wrapper Arrow)

install(TARGETS arrow-wrapper
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(DIRECTORY ${AW_PUBLIC_INCLUDE_DIR}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")