#ifndef ISDF_HPP
#define ISDF_HPP

#include "LivePixels/math.hpp"

namespace lp::SDFs
{
    class ISDF
    {
    public:
	virtual ~ISDF() = default;

    public:
    [[nodiscard]] virtual float draw(const lp::Quaternion<float> &quater) const = 0;
    };
}

#endif // ISDF_HPP
