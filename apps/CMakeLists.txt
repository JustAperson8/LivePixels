add_executable(LivePixels LivePixels.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(LivePixels sfml-graphics sfml-audio LivePixelsLib)

add_executable(LivePixelsTest LivePixelsTest.cpp)