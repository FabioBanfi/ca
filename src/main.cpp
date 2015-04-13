#include <iostream>
#include <cmath>
#include "../include/CA.h"

class Life : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    Life(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 2, delay, save), FirstOrderCA2D(W * H, W, 9)
    {
        srand(time(NULL));
    }

    inline std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(9);
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                result.push_back(L[CA::mod(CA::mod(c.x + j, W) + W * CA::mod(c.y + k, H), W * H)]);

        return result;
    }

    inline CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int sum = 0;

        for (int i = 0; i < 9; i++)
            if (i != 4)
                if (qs[i] == Q[1])
                    sum++;

        return Q[(qs[4] == Q[1] && (sum == 2 || sum == 3)) || (qs[4] == Q[0] && sum == 3)];
    }

    inline CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 2) * (rand() % 2)];
    }
};

class Rule30 : public CA::AnimatedCA1D, public CA::FirstOrderCA1D
{
public:

    Rule30(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 2, delay, save), FirstOrderCA1D(W, 3) { }

    inline std::vector<CA::C1D> N(CA::C1D c)
    {
        auto result = std::vector<CA::C1D>(3);

        result[0] = L[CA::mod(c.i - 1, W)];
        result[1] = c;
        result[2] = L[CA::mod(c.i + 1, W)];

        return result;
    }

    inline CA::State delta(CA::C1D c, std::vector<CA::State> qs)
    {
        int ql = qs[0] + 1;
        int qi = qs[1] + 1;
        int qr = qs[2] + 1;

        return Q[CA::mod(qi + ql + qr + qi * qr, 2)];
    }

    inline CA::State q0(CA::C1D c)
    {
        return Q[c.i == W / 2 ? 1 : 0];
    }
};

int main()
{
    //Life(128, 128).animate();
    Rule30(799, 400).animate();
    //Rule30(899, 450, 0, true).animate();

    return 0;
}
