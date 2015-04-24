#include "CentralInitCA1D.h"

namespace CA
{

    State CentralInitCA1D::q0(const C1D& c)
    {
        return Q[c.i == _W / 2 ? centre : outer];
    }
}
