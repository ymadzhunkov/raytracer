cmake_minimum_required(VERSION 2.8)

project (raytracer)
# The version number.
set (raytracer_VERSION_MAJOR 0)
set (raytracer_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   set(CMAKE_CXX_FLAGS -Wno-c++11-extensions)
else()
   set(CMAKE_CXX_FLAGS -Wsuggest-attribute=const)
endif()

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/system")
include_directories("${PROJECT_SOURCE_DIR}/sampling")
include_directories("${PROJECT_SOURCE_DIR}/kernels")
include_directories("${PROJECT_SOURCE_DIR}/managers")
add_subdirectory(kernels)
add_subdirectory(mintomic)
add_subdirectory(managers)
add_executable(raytracer main.cpp kernel_factory.cpp)
target_link_libraries(raytracer 
   -Wl,--whole-archive kernels_sse2 -Wl,--no-whole-archive
   -Wl,--whole-archive kernels_sse3 -Wl,--no-whole-archive
   -Wl,--whole-archive kernels_ssse3 -Wl,--no-whole-archive
   -Wl,--whole-archive kernels_sse41 -Wl,--no-whole-archive
   -Wl,--whole-archive kernels_sse42 -Wl,--no-whole-archive
   stdc++
   Mintomic
)
enable_testing()
add_subdirectory(tests)
