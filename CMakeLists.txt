cmake_minimum_required(VERSION 3.25.0)
project(AnimWallpapers VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

# Create logging directory.
file(MAKE_DIRECTORY logs)
