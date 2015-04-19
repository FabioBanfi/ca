#ifndef LANGTONS_S_ANT_H
#define LANGTONS_S_ANT_H

#define RED(v) ((v) << 16)

#include "../include/CA.h"

class LangtonsAnt : public CA::AnimatedCA2D, public CA::FirstOrderCA2D
{
public:

    LangtonsAnt(int W, int H, int delay = 0, bool save = false) : AnimatedCA(W, H, 10, delay, save), FirstOrderCA2D(W * H, W, 5)
    {
        srand(time(NULL));

        Q[1] = RED(0xFF);
        Q[2] = RED(0xFE);
        Q[3] = RED(0xFD);
        Q[4] = RED(0xFC);
        Q[5] = RED(0xFB);
        Q[6] = RED(0xFA);
        Q[7] = RED(0xF9);
        Q[8] = RED(0xF8);
    }

private:

    std::vector<CA::C2D> N(CA::C2D c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(5);
        result.push_back(c);
        result.push_back(L[CA::mod(c.x, W) + W * CA::mod(c.y - 1, H)]);
        result.push_back(L[CA::mod(c.x + 1, W) + W * CA::mod(c.y, H)]);
        result.push_back(L[CA::mod(c.x, W) + W * CA::mod(c.y + 1, H)]);
        result.push_back(L[CA::mod(c.x - 1, W) + W * CA::mod(c.y, H)]);

        return result;
    }

    CA::State delta(CA::C2D c, std::vector<CA::State> qs)
    {
        int w = Q[0];
        int Nw = Q[1];
        int Ew = Q[2];
        int Sw = Q[3];
        int Ww = Q[4];
        int Nb = Q[5];
        int Eb = Q[6];
        int Sb = Q[7];
        int Wb = Q[8];
        int b = Q[9];

        int q = qs[0];
        int qN = qs[1];
        int qE = qs[2];
        int qS = qs[3];
        int qW = qs[4];

        if (q == w)
        {
            if (qS == Ww || qS == Eb)
                return Nw;
            else if (qW == Nw || qW == Sb)
                return Ew;
            else if (qN == Ew || qN == Wb)
                return Sw;
            else if (qE == Sw || qE == Nb)
                return Ww;
            else
                return w;
        }
        else if (q == b)
        {
            if (qS == Ww || qS == Eb)
                return Nb;
            else if (qW == Nw || qW == Sb)
                return Eb;
            else if (qN == Ew || qN == Wb)
                return Sb;
            else if (qE == Sw || qE == Nb)
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
        return Q[c.x == W / 2 && c.y == H / 2];
    }
};

#endif // LANGTONS_S_ANT_H
