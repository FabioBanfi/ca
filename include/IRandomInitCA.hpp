#ifndef RANDOM_INIT_CA_H
#define RANDOM_INIT_CA_H

#include <cstdint>
#include <random>
#include "ICellularAutomaton.h"

namespace CA
{
    template <class Cell>
    class IRandomInitCA : virtual public ICellularAutomaton<Cell>
    {
    protected:

        IRandomInitCA(uint32_t s) :
                gen(rd()),
                dis(0, s - 1)
        { }
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

#endif // RANDOM_INIT_CA_H
