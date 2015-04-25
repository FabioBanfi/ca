#pragma once

#include <random>
#include "CA.h"

class RockPaperScissor :
        public CA::IAnimatedCA2D,
        public CA::IFirstOrderCA2D,
        public CA::IRandomInitCA<CA::C2D>
{
public:

    RockPaperScissor(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 3, delay, save),
            IFirstOrderCA2D(2),
            gen(rd()),
            dis(0, 7)
    {
        srand(time(NULL));
    }

private:

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    std::vector<CA::C2D> N(const CA::C2D& c)
    {
        auto result = std::vector<CA::C2D>();
        auto moore = std::vector<CA::C2D>();

        result.reserve(2);
        result.push_back(c);

        moore.reserve(8);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                if (CA::C2D(j, k) != c)
                    moore.push_back(L[CA::mod(c.x + j, width) + width * CA::mod(c.y + k, height)]);

        result.push_back(moore[dis(gen)]);
        return result;
    }

    CA::State delta(const CA::C2D& c, const std::vector<CA::State>& qs)
    {
        CA::State q0 = qs[0] == Q[0] ? 0 : (qs[0] == Q[1] ? 1 : 2);
        CA::State q1 = qs[1] == Q[0] ? 0 : (qs[1] == Q[1] ? 1 : 2);

        return qs[q0 == CA::mod(q1 - 1, 3)];
    }
};
