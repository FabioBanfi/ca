#ifndef CENTRAL_INIT_CA_1D_H
#define CENTRAL_INIT_CA_1D_H

#include <cstdint>
#include "CellularAutomaton.h"

namespace CA
{
    class CentralInitCA1D : virtual public CellularAutomaton<C1D>
    {
    protected:

        CentralInitCA1D(uint32_t W, uint32_t centre, uint32_t outer) :
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
