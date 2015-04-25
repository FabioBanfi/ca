#include "IFirstOrderCA2D.h"

namespace CA
{
    State IFirstOrderCA2D::phi(const C2D& c, uint32_t t)
    {
        if (t == 0)
        {
            new_qs[c.x + width * c.y] = q0(c);

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
            auto neighbours_states = std::vector<State>();
            neighbours_states.reserve(num_of_neighbours);

            for (auto neighbour : neighbours)
                neighbours_states.push_back(old_qs[neighbour.x + width * neighbour.y]);

            new_qs[c.x + width * c.y] = delta(c, neighbours_states);

            return delta(c, neighbours_states);
        }
    }
}
