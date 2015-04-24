#include <cstdint>
#include "FirstOrderCA2D.h"

namespace CA
{
    State FirstOrderCA2D::phi(const C2D& c, uint32_t t)
    {
        if (t == 0)
        {
            new_qs[c.x + offset * c.y] = q0(c);

            return q0(c);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<State>();
            neigh_qs.reserve(d);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old_qs[neighbour.x + offset * neighbour.y]);

            new_qs[c.x + offset * c.y] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }
}
