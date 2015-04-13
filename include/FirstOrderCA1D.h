#ifndef FIRST_ORDER_CA_1D_H
#define FIRST_ORDER_CA_1D_H

#include "CellularAutomaton.h"

namespace CA {

class FirstOrderCA1D : virtual public CellularAutomaton<C1D>
{
protected:

    FirstOrderCA1D(int size, int d) : d(d), current_t(0), old_qs(size), new_qs(size) { }
    virtual State phi(C1D c, int t);

private:

    int d;
    int current_t;
    std::vector<State> old_qs;
    std::vector<State> new_qs;
};

} // CA

#endif // FIRST_ORDER_CA_1D_H
