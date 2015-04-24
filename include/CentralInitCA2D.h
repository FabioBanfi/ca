#ifndef CENTRAL_INIT_CA_2D_H
#define CENTRAL_INIT_CA_2D_H

#include <cstdint>
#include <random>
#include "CellularAutomaton.h"

namespace CA
{
    class CentralInitCA2D : virtual public CellularAutomaton<C2D>
    {
    protected:

        CentralInitCA2D(uint32_t W, uint32_t H, uint32_t centre, uint32_t outer) :
                _W(W),
                _H(H),
                centre(centre),
                outer(outer)
        { }
        State q0(const C2D&);

    private:

        uint32_t _W;
        uint32_t _H;
        uint32_t centre;
        uint32_t outer;
    };
}

#endif // CENTRAL_INIT_CA_2D_H
