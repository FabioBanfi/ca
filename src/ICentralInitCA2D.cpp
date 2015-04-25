#include "ICentralInitCA2D.h"

namespace CA
{
    State ICentralInitCA2D::q0(const C2D& c)
    {
        return Q[c.x == width / 2 && c.y == height / 2 ? central : outer];
    }
}
