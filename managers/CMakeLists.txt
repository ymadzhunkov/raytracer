cmake_minimum_required(VERSION 2.8)



#add_executable(raytracer main.cpp)
set(MANAGERS_SOURCES threadmanager.cpp)
add_library(managers  STATIC ${MANAGERS_SOURCES})

#target_compile_options(kernels_sse3  PUBLIC -msse3)

