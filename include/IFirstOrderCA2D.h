#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IFirstOrderCA2D : virtual public IAnimatedCA<C2D>
    {
    protected:

        IFirstOrderCA2D(uint32_t num_of_neighbours) :
                num_of_neighbours(num_of_neighbours),
                current_t(0),
                old_qs(width * height),
                new_qs(width * height) { }
        virtual State phi(const C2D&, uint32_t);

    private:

        uint32_t num_of_neighbours;
        uint32_t current_t;
        std::vector<State> old_qs;
        std::vector<State> new_qs;
    };
}
