#ifndef LIFE_H
#define LIFE_H

#include <cstdint>
#include "CA.h"

class Life :
        public CA::AnimatedCA2D,
        public CA::FirstOrderCA2D
{
public:

    Life(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) :
            AnimatedCA(W, H, 2, delay, save),
            FirstOrderCA2D(W * H, W, 9)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(9);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                result.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        uint32_t sum = 0;

        for (uint32_t i = 0; i < 9; i++)
            if (i != 4)
                if (qs[i] == Q[1])
                    sum++;

        return Q[(qs[4] == Q[1] && (sum == 2 || sum == 3)) || (qs[4] == Q[0] && sum == 3)];
    }

    CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 2)];
    }
};

#endif // LIFE_H
