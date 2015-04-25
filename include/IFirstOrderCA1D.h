#pragma once

#include "IAnimatedCA.hpp"

namespace CA
{
    class IFirstOrderCA1D : virtual public IAnimatedCA<C1D>
    {
    protected:

        IFirstOrderCA1D(uint32_t num_of_neighbours) :
                num_of_neighbours(num_of_neighbours),
                current_t(0),
                old_qs(width),
                new_qs(width) { }
        virtual State phi(const C1D&, uint32_t);

    private:

        uint32_t num_of_neighbours;
        uint32_t current_t;
        std::vector<State> old_qs;
        std::vector<State> new_qs;
    };
}
