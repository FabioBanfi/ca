#include "FirstOrderCA1D.h"

namespace CA
{
    State FirstOrderCA1D::phi(C1D c, uint32_t t)
    {
        if (t == 0)
        {
            new_qs[c.i] = q0(c);

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
                neigh_qs.push_back(old_qs[neighbour.i]);

            new_qs[c.i] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }
}
