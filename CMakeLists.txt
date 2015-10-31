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

include_directories("${PROJECT_BINARY_DIR}")

add_executable(raytracer main.cpp)
