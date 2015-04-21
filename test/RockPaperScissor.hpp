#ifndef ROCK_PAPER_SCISSOR_H
#define ROCK_PAPER_SCISSOR_H

#include <cstdint>
#include <random>
#include "../include/CA.h"

class RockPaperScissor : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    RockPaperScissor(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) : AnimatedCA(W, H, 3, delay, save), FirstOrderCA2D(W * H, W, 2), gen(rd()), dis(0, 7)
    {
        srand(time(NULL));
    }

private:

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();
        auto moore = std::vector<CA::C2D>();

        result.reserve(2);
        result.push_back(c);

        moore.reserve(8);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                if (CA::C2D(j, k) != c)
                    moore.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        result.push_back(moore[dis(gen)]);
        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        CA::State q0 = qs[0] == Q[0] ? 0 : (qs[0] == Q[1] ? 1 : 2);
        CA::State q1 = qs[1] == Q[0] ? 0 : (qs[1] == Q[1] ? 1 : 2);

        return qs[q0 == CA::mod(q1 - 1, 3)];
    }

    CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 3)];
    }
};

#endif // ROCK_PAPER_SCISSOR_H
