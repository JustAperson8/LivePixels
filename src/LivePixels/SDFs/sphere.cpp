#include "sphere.hpp"

using namespace lp::SDFs;

Sphere::Sphere(float s, float x, float y, float z, float radius)
    : m_pos(s, x, y, z), m_radius(radius)
{}

Sphere::Sphere(const lp::Quaternion<float> &pos, float radius)
    : m_pos(pos), m_radius(radius)
{}

[[nodiscard]] float Sphere::draw(const lp::Quaternion<float> &pos) const
{
    auto minus = pos - m_pos;
    return std::sqrt(std::abs(minus.getX() * minus.getX() + minus.getY() * minus.getY() + minus.getZ() * minus.getZ())) - m_radius;
}
