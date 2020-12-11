#include "GroupOfSDFs.hpp"

using namespace lp::SDFs;

GroupOfSDFs::GroupOfSDFs( std::vector<lp::SDFs::ISDF *> &&visibleSDFs, std::vector<lp::SDFs::ISDF *> &&cutSDFs)
            : m_visibleSDFs(visibleSDFs), m_cutSDFs(cutSDFs)
        {}

float GroupOfSDFs::getMin(const lp::Quaternion<float> &quater, const std::vector<lp::SDFs::ISDF *> &vectorOfSDFS) const 
{
    float min = 1e18;
    for (const auto *shape: vectorOfSDFS)
        if (shape != nullptr)
            min = std::min(min, shape->draw(quater));
    return min;
}

float GroupOfSDFs::draw(const lp::Quaternion<float> &quater) const
{
    return std::max(getMin(quater, m_visibleSDFs), -(getMin(quater, m_cutSDFs)));
}

GroupOfSDFs::~GroupOfSDFs()
{
    for (auto SDF: m_visibleSDFs)
        delete SDF;
    for (auto SDF: m_cutSDFs)
        delete SDF;
}