#ifndef LANGTONS_S_ANT_H
#define LANGTONS_S_ANT_H

#include "../include/CA.h"

class LangtonsAnt : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    LangtonsAnt(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 10, delay, save), FirstOrderCA2D(W * H, W, 5)
    {
        srand(time(NULL));
    }

private:

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(5);
        result.push_back(c);
        result.push_back(L[CA::mod(CA::mod(c.x, W) + W * CA::mod(c.y + 1, H), W * H)]);
        result.push_back(L[CA::mod(CA::mod(c.x, W) + W * CA::mod(c.y - 1, H), W * H)]);
        result.push_back(L[CA::mod(CA::mod(c.x - 1, W) + W * CA::mod(c.y, H), W * H)]);
        result.push_back(L[CA::mod(CA::mod(c.x + 1, W) + W * CA::mod(c.y, H), W * H)]);

        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int w = Q[0];
        int Nw = Q[1];
        int Sw = Q[2];
        int Ww = Q[3];
        int Ew = Q[4];
        int Nb = Q[5];
        int Sb = Q[6];
        int Wb = Q[7];
        int Eb = Q[8];
        int b = Q[9];

        int q = qs[0];
        int qN = qs[1];
        int qS = qs[2];
        int qW = qs[3];
        int qE = qs[4];

        if (q == w)
        {
            if (qN == Ew)
                return Sw;
            else if (qS == Ww)
                return Nw;
            else if (qW == Nw)
                return Ew;
            else if (qE == Sw)
                return Ww;
            else if (qN == Wb)
                return Sw;
            else if (qS == Eb)
                return Nw;
            else if (qW == Sb)
                return Ew;
            else if (qE == Nb)
                return Ww;
            else
                return w;
        }
        else if (q == b)
        {
            if (qN == Ew)
                return Sb;
            else if (qS == Ww)
                return Nb;
            else if (qW == Nw)
                return Eb;
            else if (qE == Sw)
                return Wb;
            else if (qN == Wb)
                return Sb;
            else if (qS == Eb)
                return Nb;
            else if (qW == Sb)
                return Eb;
            else if (qE == Nb)
                return Wb;
            else
                return b;
        }
        else
        {
            return q == Nb || q == Sb || q == Wb || q == Eb ? w : b;
        }
    }

    CA::State q0(CA::C2D c)
    {
        return c.x == W / 2 && c.y == H / 2 ? Q[1] : Q[0];
    }
};

#endif // LANGTONS_S_ANT_H
