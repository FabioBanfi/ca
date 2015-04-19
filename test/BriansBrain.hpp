#ifndef BRIAN_S_BRAIN_H
#define BRIAN_S_BRAIN_H

#include "../include/CA.h"

class BriansBrain : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    BriansBrain(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 3, delay, save), FirstOrderCA2D(W * H, W, 9)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(9);
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                result.push_back(L[CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H)]);

        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int sum = 0;

        for (int i = 0; i < 9; i++)
            if (i != 4)
                if (qs[i] == Q[2])
                    sum++;

        return qs[4] == Q[0] && sum == 2 ? Q[2] : Q[qs[4] == Q[2]];
    }

    CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 3)];
    }
};

#endif // BRIAN_S_BRAIN_H
