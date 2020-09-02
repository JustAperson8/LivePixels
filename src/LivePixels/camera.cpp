#include "camera.hpp"

lp::Camera::Camera(std::vector<lp::SDFs::ISDF *> map,
           const lp::Quaternion<float> &position,
           float depthOfRender,
           size_t iterations)
        : m_map(map),  m_pos(position), m_depthOfRender(depthOfRender), m_iterations(iterations)
{}

float lp::Camera::minDistance(const lp::Quaternion<float> &point)
{
    float min = 1e18;
    for (const auto *shape: m_map)
	if (shape != nullptr)
	    min = std::min(min, shape->draw(point));
    return min;
}

void lp::Camera::setPosition(const lp::Quaternion<float> &pos)
{
    m_pos = pos;
}

lp::Quaternion<float> lp::Camera::getPosition()
{
    return m_pos;
}

float lp::Camera::rayMarching(lp::Quaternion<float> rotator)
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
	distance += newD;
	if (distance > m_depthOfRender)
	    return 1e18;
    }
    return 1e18;
}
