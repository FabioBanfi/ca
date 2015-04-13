#ifndef FIRST_ORDER_CA_2D_H
#define FIRST_ORDER_CA_2D_H

#include "CellularAutomaton.h"

namespace CA {

class FirstOrderCA2D : virtual public CellularAutomaton<C2D>
{
protected:

    FirstOrderCA2D(int size, int offset, int d) : offset(offset), d(d), current_t(0), old_qs(size), new_qs(size) { }
    virtual State phi(C2D c, int t);

private:

    int offset;
    int d;
    int current_t;
    std::vector<State> old_qs;
    std::vector<State> new_qs;
};

} // CA

#endif // FIRST_ORDER_CA_2D_H
