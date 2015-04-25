#pragma once

#include <random>
#include "IAnimatedCA.hpp"

namespace CA
{
    template <class Cell>
    class IRandomInitCA : virtual public IAnimatedCA<Cell>
    {
    protected:

        IRandomInitCA() :
                gen(rd()),
                dis(0, this->num_of_states - 1) { }
        State q0(const Cell& c)
        {
            return this->Q[dis(gen)];
        }

    private:

        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> dis;
    };
}
