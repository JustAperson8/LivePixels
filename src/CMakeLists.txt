project(LivePixelsLib VERSION 0.0.1)

set(MATH_FILES
    LivePixels/math/Quaternion.cpp
    LivePixels/math/Quaternion.hpp
    LivePixels/math/functions.cpp
    LivePixels/math/functions.hpp
    LivePixels/math.hpp)

set(SDFS_FILES
    LivePixels/SDFs/ISDF.hpp
    LivePixels/SDFs/Sphere.cpp
    LivePixels/SDFs/Sphere.hpp
    LivePixels/SDFs.hpp)

set(LIVE_PIXELS_FILES
    LivePixels/Ray.cpp
    LivePixels/Ray.hpp LivePixels/constants.hpp)

add_library(LivePixelsLib
        ${MATH_FILES} ${SDFS_FILES} ${LIVE_PIXELS_FILES})

target_include_directories(LivePixelsLib PUBLIC .)
