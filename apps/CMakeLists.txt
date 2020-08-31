add_executable(LivePixels LivePixels.cpp)
add_executable(LivePixelsTest LivePixelsTest.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(LivePixels sfml-graphics sfml-audio LivePixelsLib)
target_link_libraries(LivePixelsTest sfml-graphics sfml-audio LivePixelsLib)
