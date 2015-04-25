#include "ICentralInitCA1D.h"

namespace CA
{

    State ICentralInitCA1D::q0(const C1D& c)
    {
        return Q[c.i == _W / 2 ? centre : outer];
    }
}
