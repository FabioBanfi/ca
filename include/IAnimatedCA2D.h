#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IAnimatedCA2D : virtual public IAnimatedCA<C2D>
    {
    public:

        IAnimatedCA2D();
        void animate();
    };
}
