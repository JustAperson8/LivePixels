cmake_minimum_required(VERSION 3.5)

project(LivePixels LANGUAGES CXX)
project(LivePixelsTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(apps)
