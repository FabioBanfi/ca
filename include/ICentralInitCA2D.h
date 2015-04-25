#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class ICentralInitCA2D : virtual public IAnimatedCA<C2D>
    {
    protected:

        ICentralInitCA2D(uint32_t central, uint32_t outer) :
                central(central),
                outer(outer) { }
        State q0(const C2D&);

    private:

        uint32_t central;
        uint32_t outer;
    };
}
