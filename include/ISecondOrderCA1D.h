#ifndef SECOND_ORDER_CA_1D_H
#define SECOND_ORDER_CA_1D_H

#include <cstdint>
#include "ICellularAutomaton.h"

namespace CA
{
    class ISecondOrderCA1D : virtual public ICellularAutomaton<C1D>
    {
    protected:

        ISecondOrderCA1D(uint32_t size, uint32_t d) :
                d(d),
                current_t(0),
                old1_qs(size),
                old2_qs(size),
                new_qs(size)
        { }
        virtual State phi(const C1D&, uint32_t);

    private:

        uint32_t d;
        uint32_t current_t;
        std::vector<State> old1_qs;
        std::vector<State> old2_qs;
        std::vector<State> new_qs;
    };
}

#endif // SECOND_ORDER_CA_1D_H
