#ifndef FIRST_ORDER_CA_1D_H
#define FIRST_ORDER_CA_1D_H

#include "CellularAutomaton.h"

namespace CA
{
    class FirstOrderCA1D : virtual public CellularAutomaton<C1D>
    {
    protected:

        FirstOrderCA1D(uint32_t size, uint32_t d) : d(d), current_t(0), old_qs(size), new_qs(size) { }
        virtual State phi(C1D c, uint32_t t);

    private:

        uint32_t d;
        uint32_t current_t;
        std::vector<State> old_qs;
        std::vector<State> new_qs;
    };
}

#endif // FIRST_ORDER_CA_1D_H
