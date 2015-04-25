#ifndef CENTRAL_INIT_CA_1D_H
#define CENTRAL_INIT_CA_1D_H

#include <cstdint>
#include "ICellularAutomaton.h"

namespace CA
{
    class ICentralInitCA1D : virtual public ICellularAutomaton<C1D>
    {
    protected:

        ICentralInitCA1D(uint32_t W, uint32_t centre, uint32_t outer) :
                _W(W),
                centre(centre),
                outer(outer)
        { }
        State q0(const C1D&);

    private:

        uint32_t _W;
        uint32_t centre;
        uint32_t outer;
    };
}

#endif // CENTRAL_INIT_CA_1D_H
