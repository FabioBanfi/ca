#ifndef RANDOM_CA_1D_H
#define RANDOM_CA_1D_H

#include <cstdint>
#include <random>
#include "CA.h"

class RandomCA1D :
        public CA::IAnimatedCA1D,
        public CA::IFirstOrderCA1D,
        public CA::IRandomInitCA<CA::C1D>
{
public:

    RandomCA1D(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(W, H, 2, delay, save),
            IFirstOrderCA1D(W, 3),
            IRandomInitCA(2),
            gen(rd()),
            dis(0, 1)
    { }

private:

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    std::vector<CA::C1D> N(const CA::C1D& c)
    {
        return std::vector<CA::C1D>();
    }

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        return Q[dis(gen)];
    }
};

#endif // RANDOM_CA_1D_H
