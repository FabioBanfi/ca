#include <cstdint>
#include "ISecondOrderCA1D.h"

namespace CA
{
    State ISecondOrderCA1D::phi(const C1D& c, uint32_t t)
    {
        if (t == 0)
        {
            new_qs[c.i] = q0(c);

            return q0(c);
        }
        else if (t == 1)
        {
            if (t != current_t)
            {
                current_t = t;
                old1_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<State>();
            neigh_qs.reserve(d);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old1_qs[neighbour.i]);

            new_qs[c.i] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old2_qs = old1_qs;
                old1_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<State>();
            neigh_qs.reserve(d);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old1_qs[neighbour.i]);

            new_qs[c.i] = mod(delta(c, neigh_qs) + old2_qs[c.i] + 1, 2);

            return delta(c, neigh_qs);
        }
    }
}
