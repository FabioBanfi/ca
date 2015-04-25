#include "ICentralInitCA2D.h"

namespace CA
{

    State ICentralInitCA2D::q0(const C2D& c)
    {
        return Q[c.x == _W / 2 && c.y == _H / 2 ? centre : outer];
    }
}
