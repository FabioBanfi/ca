#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IAnimatedCA1D : virtual public IAnimatedCA<C1D>
    {
    public:

        IAnimatedCA1D();
        void animate();
    };
}