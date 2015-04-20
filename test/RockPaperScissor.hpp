#ifndef ROCK_PAPER_SCISSOR_H
#define ROCK_PAPER_SCISSOR_H

#include <random>
#include "../include/CA.h"

class RockPaperScissor : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    RockPaperScissor(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 3, delay, save), FirstOrderCA2D(W * H, W, 2), gen(rd()), dis(0, 7)
    {
        //std::cout << Q[0] << " " << Q[1] << " " << Q[2] << std::endl;//Q[2]=GRAY(254);
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
        for (int k = -1; k <= 1; k++)
            for (int j = -1; j <= 1; j++)
                if (CA::C2D(j, k) != c)
                    moore.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        result.push_back(moore[dis(gen)]);
        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int q0 = qs[0] == Q[0] ? 0 : (qs[0] == Q[1] ? 1 : 2);
        int q1 = qs[1] == Q[0] ? 0 : (qs[1] == Q[1] ? 1 : 2);

        return q0 == CA::mod(q1 - 1, 3) ? qs[1] : qs[0];
        //return abs(CA::mod(qs[0] - , 3))
    }

    CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 3)];
    }
};

#endif // ROCK_PAPER_SCISSOR_H
