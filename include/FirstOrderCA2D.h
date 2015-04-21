#ifndef FIRST_ORDER_CA_2D_H
#define FIRST_ORDER_CA_2D_H

#include "CellularAutomaton.h"

namespace CA
{
    class FirstOrderCA2D : virtual public CellularAutomaton<C2D>
    {
    protected:

        FirstOrderCA2D(uint32_t size, uint32_t offset, uint32_t d) : offset(offset), d(d), current_t(0), old_qs(size), new_qs(size) { }
        virtual State phi(C2D c, uint32_t t);

    private:

        uint32_t offset;
        uint32_t d;
        uint32_t current_t;
        std::vector<State> old_qs;
        std::vector<State> new_qs;
    };
}

#endif // FIRST_ORDER_CA_2D_H
