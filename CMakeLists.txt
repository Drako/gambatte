cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(gambatte VERSION 0.1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(libgambatte)
add_subdirectory(gambatte_sdl)
