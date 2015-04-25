#ifndef FIRST_ORDER_CA_1D_H
#define FIRST_ORDER_CA_1D_H

#include <cstdint>
#include "ICellularAutomaton.h"

namespace CA
{
    class IFirstOrderCA1D : virtual public ICellularAutomaton<C1D>
    {
    protected:

        IFirstOrderCA1D(uint32_t size, uint32_t d) :
                d(d),
                current_t(0),
                old_qs(size),
                new_qs(size)
        { }
        virtual State phi(const C1D&, uint32_t);

    private:

        uint32_t d;
        uint32_t current_t;
        std::vector<State> old_qs;
        std::vector<State> new_qs;
    };
}

#endif // FIRST_ORDER_CA_1D_H
