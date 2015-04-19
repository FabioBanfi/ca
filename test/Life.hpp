#ifndef LIFE_H
#define LIFE_H

#include "../include/CA.h"

class Life : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    Life(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 2, delay, save), FirstOrderCA2D(W * H, W, 9)
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
                if (qs[i] == Q[1])
                    sum++;

        return Q[(qs[4] == Q[1] && (sum == 2 || sum == 3)) || (qs[4] == Q[0] && sum == 3)];
    }

    CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 2) * (rand() % 2)];
    }
};

#endif // LIFE_H
