#ifndef SECOND_ORDER_CA_1D_H
#define SECOND_ORDER_CA_1D_H

#include "CellularAutomaton.h"

namespace CA
{
    class SecondOrderCA1D : virtual public CellularAutomaton<C1D>
    {
    protected:

        SecondOrderCA1D(uint32_t size, uint32_t d) :
                d(d),
                current_t(0),
                old1_qs(size),
                old2_qs(size),
                new_qs(size) { }
        virtual State phi(C1D c, uint32_t t);

    private:

        uint32_t d;
        uint32_t current_t;
        std::vector<State> old1_qs;
        std::vector<State> old2_qs;
        std::vector<State> new_qs;
    };
}

#endif // SECOND_ORDER_CA_1D_H
