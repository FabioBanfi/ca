#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class ICentralInitCA1D : virtual public IAnimatedCA<C1D>
    {
    protected:

        ICentralInitCA1D(uint32_t central, uint32_t outer) :
                central(central),
                outer(outer) { }
        State q0(const C1D&);

    private:

        uint32_t central;
        uint32_t outer;
    };
}
