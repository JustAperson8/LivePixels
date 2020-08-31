#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <LivePixels/SDFs/ISDF.hpp>

namespace lp::SDFs
{
    class Circle : public ISDF
    {
    private:
    lp::Quaternion<float> m_pos;
    float m_radius;

    public:
    Circle(float s, float x, float y, float z, float radius);
    Circle(const lp::Quaternion<float> &pos = {0, 0, 0, 0}, float radius = 10);

    public:
    [[nodiscard]] float draw(const lp::Quaternion<float> &pos) const override;

    };
}

#endif // CIRCLE_HPP
