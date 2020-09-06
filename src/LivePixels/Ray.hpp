#ifndef RAY_HPP
#define RAY_HPP

#include <LivePixels/SDFs.hpp>
#include <LivePixels/math.hpp>
#include <vector>

namespace lp
{
    class Ray
    {
    private:
        std::vector<lp::SDFs::ISDF *> m_map;
        lp::Quaternion<float> m_pos;
        float m_depthOfRender;
        size_t m_iterations;

    public:
        Ray(std::vector<lp::SDFs::ISDF *> map,
            const lp::Quaternion<float> &position = {0, 0, 0, 0},
            float depthOfRender = 2000,
            size_t iterations = 10);

        virtual ~Ray() = default;

    private:
        float minDistance(const lp::Quaternion<float> &point);

    public:
        void setPosition(const lp::Quaternion<float> &pos);
        lp::Quaternion<float> getPosition();

        float rayMarching(lp::Quaternion<float> rotator);
    };
}

#endif // RAY_HPP
