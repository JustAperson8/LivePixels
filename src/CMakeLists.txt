project(LivePixelsLib VERSION 0.0.1)

set(MATH_FILES
    LivePixels/math/quaternion.cpp
    LivePixels/math/quaternion.hpp
    LivePixels/math/functions.cpp
    LivePixels/math/functions.hpp
    LivePixels/math.hpp)

set(SDFS_FILES
    LivePixels/SDFs/ISDF.hpp
    LivePixels/SDFs/sphere.cpp
    LivePixels/SDFs/sphere.hpp
    LivePixels/SDFs.hpp)

set(LIVE_PIXELS_FILES
    LivePixels/camera.cpp
    LivePixels/camera.hpp)

add_library(LivePixelsLib
        ${MATH_FILES} ${SDFS_FILES} ${LIVE_PIXELS_FILES})

target_include_directories(LivePixelsLib PUBLIC .)
