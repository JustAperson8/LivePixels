#include <iostream>
#include <LivePixels/math.hpp>
#include <LivePixels/SDFs.hpp>
#include <LivePixels/camera.hpp>
#include <cmath>
#include <vector>

using lp::angleToRadian;
using std::sin;
using std::cos;
using Qtr = lp::Quaternion<float>;

/*
class PerspectiveDisplay
{
private:
    Camera m_camera;
    size_t m_width, m_height;
    float m_pw, m_ph;

public:
    PerspectiveDisplay(const Camera &camera, size_t width, size_t height, float pw = 1, float ph = 1)
        : m_camera(camera), m_width(width), m_height(height), m_pw(pw), m_ph(ph)
    {}
};
*/

int main(int argc, char **argv)
{
    std::vector<lp::SDFs::ISDF *> testMap;
    testMap.push_back(new lp::SDFs::Sphere(0, 100, 100, 0, 50));
    lp::Camera camera(testMap);
    std::cout << camera.rayMarching({cos(angleToRadian(45 / 2)), 0, 0, sin(angleToRadian(45 / 2))}) << std::endl;
    for (auto *obj: testMap)
        delete obj;
    return 0;
}
