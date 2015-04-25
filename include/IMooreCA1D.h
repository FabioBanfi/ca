#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IMooreCA1D : virtual public IAnimatedCA<C1D>
    {
    protected:

        virtual std::vector<CA::C1D> N(const CA::C1D&);
    };
}
