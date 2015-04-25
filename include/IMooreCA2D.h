#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IMooreCA2D : virtual public IAnimatedCA<C2D>
    {
    protected:

        virtual std::vector<CA::C2D> N(const CA::C2D&);
    };
}
