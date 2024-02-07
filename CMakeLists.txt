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
  PRIVATE ${AW_CC}
)

target_link_libraries(arrow-wrapper Arrow)

target_include_directories(arrow-wrapper
  PRIVATE
      # where the library itself will look for its internal headers
      ${CMAKE_CURRENT_SOURCE_DIR}/src
  PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
    src/api.h
)

set_target_properties(arrow-wrapper PROPERTIES PUBLIC_HEADER "${public_headers}")

include(GNUInstallDirs)

# install the target and create export-set
install(TARGETS arrow-wrapper
    EXPORT "${PROJECT_NAME}Targets"
    # these get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)