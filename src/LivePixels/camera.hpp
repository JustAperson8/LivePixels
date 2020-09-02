#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <LivePixels/SDFs.hpp>
#include <LivePixels/math.hpp>
#include <vector>

namespace lp
{
    class Camera
    {
    private:
        std::vector<lp::SDFs::ISDF *> m_map;
        lp::Quaternion<float> m_pos;
        float m_depthOfRender;
        size_t m_iterations;

    public:
    Camera(std::vector<lp::SDFs::ISDF *> map,
           const lp::Quaternion<float> &position = {0, 0, 0, 0},
           float depthOfRender = 2000,
           size_t iterations = 10);

        virtual ~Camera() = default;

    private:
        float minDistance(const lp::Quaternion<float> &point);

    public:
        void setPosition(const lp::Quaternion<float> &pos);
        lp::Quaternion<float> getPosition();

        float rayMarching(lp::Quaternion<float> rotator);
    };
}

#endif // CAMERA_HPP
