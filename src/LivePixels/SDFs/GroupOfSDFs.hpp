#ifndef GROUP_OF_SDFS
#define GROUP_OF_SDFS

#include "LivePixels/SDFs/ISDF.hpp"
#include <vector>

namespace lp::SDFs
{
    class GroupOfSDFs : public lp::SDFs::ISDF
    {
    public:
        std::vector<lp::SDFs::ISDF *> m_visibleSDFs, m_cutSDFs;

    public:
        GroupOfSDFs( std::vector<lp::SDFs::ISDF *> &&visibleSDFs, std::vector<lp::SDFs::ISDF *> &&cutSDFs);
        virtual ~GroupOfSDFs();

    private:
        float getMin(const lp::Quaternion<float> &quater, const std::vector<lp::SDFs::ISDF *> &vectorOfSDFS) const; 
        
    public:
        [[nodiscard]] virtual float draw(const lp::Quaternion<float> &quater) const;
    };
}

#endif