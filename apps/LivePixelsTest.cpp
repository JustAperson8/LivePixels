#include <iostream>
#include <LivePixels/math.hpp>
#include <LivePixels/SDFs.hpp>
#include <cmath>
#include <vector>

using lp::angleToRadian;
using std::sin;
using std::cos;
using Qtr = lp::Quaternion<float>;

class Camera
{
private:
    std::vector<lp::SDFs::ISDF *> m_map;
    lp::Quaternion<float> m_pos;
    float m_dephOfRender;
    size_t m_iterations;

public:
    Camera(std::vector<lp::SDFs::ISDF *> map,
           const lp::Quaternion<float> &position = {0, 0, 0, 0},
           float dephOfRender = 2000,
           size_t iterations = 10)
        : m_map(map),  m_pos(position), m_dephOfRender(dephOfRender), m_iterations(iterations)
    {}

    virtual ~Camera() = default;
    
private:
    float minDistance(lp::Quaternion<float> &point)
    {
        float min = 1e18;
        for (const auto *shape: m_map)
            if (shape != nullptr)
                min = std::min(min, shape->draw(point));
        return min;
    }

public:
    void setPosition(const lp::Quaternion<float> &position)
    {
        m_pos = position;
    }

    lp::Quaternion<float> getPosition()
    {
        return m_pos;
    }

    float RayMarching(lp::Quaternion<float> rotator)
    {
        float distance = 0;
        lp::Quaternion<float> p(m_pos);
        for (size_t i = 0; i < m_iterations; ++i)
        {
            float newD = minDistance(p);
            if (newD <= 0.6)
                return distance;
            lp::Quaternion<float> buf(0, newD, 0, 0);
            p = (rotator * buf * rotator.inverse()) + p;
            if (distance > m_dephOfRender)
                return 1e18;
        }
        return 1e18;
    }
};

int main(int argc, char **argv)
{
    return 0;
}
