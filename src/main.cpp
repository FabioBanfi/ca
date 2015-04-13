#include <iostream>
#include <cmath>
#include "../include/CA.h"

class Life : public CA::AnimatedCA2D
{
public:

    Life(int W, int H, int delay, bool save) : AnimatedCA2D(W, H, 2, delay, save), old_qs(W * H), new_qs(W * H), current_t(0)
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

    inline CA::State phi(CA::C2D c, int t)
    {
        if (t == 0)
        {
            new_qs[c.x + W * c.y] = q0(c);
            return q0(c);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<CA::State>();
            neigh_qs.reserve(9);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old_qs[neighbour.x + W * neighbour.y]);

            new_qs[c.x + W * c.y] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }

    inline CA::State q0(CA::C2D c)
    {
        return Q[(rand() % 2) * (rand() % 2)];
    }

private:

    int current_t;
    std::vector<CA::State> old_qs;
    std::vector<CA::State> new_qs;
};

class Rule30 : public CA::AnimatedCA1D
{
public:

    Rule30(int W, int H, int delay, bool save) : AnimatedCA1D(W, H, 2, delay, save), old_qs(W), new_qs(W), current_t(0) { }

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

    inline CA::State phi(CA::C1D c, int t)
    {
        if (t == 0)
        {
            new_qs[c.i] = q0(c);
            return q0(c);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<CA::State>();
            neigh_qs.reserve(3);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old_qs[neighbour.i]);

            new_qs[c.i] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }

    inline CA::State q0(CA::C1D c)
    {
        return Q[c.i == W / 2 ? 1 : 0];
    }

private:

    int current_t;
    std::vector<CA::State> old_qs;
    std::vector<CA::State> new_qs;
};






int main()
{
    //Life(32, 32, 0, true).animate();
    Rule30(799, 400, 0, true).animate();
    //Rule30(899, 450, 0, true).animate();

    return 0;
}
