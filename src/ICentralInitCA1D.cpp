#include "ICentralInitCA1D.h"

namespace CA
{
    State ICentralInitCA1D::q0(const C1D& c)
    {
        return Q[c.i == width / 2 ? central : outer];
    }
}
