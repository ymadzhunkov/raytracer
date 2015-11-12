cmake_minimum_required(VERSION 2.8)


#include_directories("${PROJECT_BINARY_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}/system")
include_directories("${PROJECT_SOURCE_DIR}/kernels")

#add_executable(raytracer main.cpp)
set(KERNEL_SOURCES kernel_vectors.cpp)
add_library(kernels_sse2  STATIC ${KERNEL_SOURCES})
add_library(kernels_sse3  STATIC ${KERNEL_SOURCES})
add_library(kernels_ssse3 STATIC ${KERNEL_SOURCES})
add_library(kernels_sse41 STATIC ${KERNEL_SOURCES})
add_library(kernels_sse42 STATIC ${KERNEL_SOURCES})

target_compile_options(kernels_sse2  PUBLIC -msse2)
target_compile_options(kernels_sse3  PUBLIC -msse3)
target_compile_options(kernels_ssse3 PUBLIC -mssse3)
target_compile_options(kernels_sse41 PUBLIC -msse4.1)
target_compile_options(kernels_sse42 PUBLIC -msse4.2)
