#pragma once

#define RED(v) ((v) << 16)

#include "CA.h"

class LangtonsAnt :
        public CA::IAnimatedCA2D,
        public CA::IVonNeumannCA2D,
        public CA::IFirstOrderCA2D,
        public CA::ICentralInitCA2D
{
public:

    LangtonsAnt(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 10, delay, save),
            IFirstOrderCA2D(5),
            ICentralInitCA2D(1, 0)
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

    CA::State delta(const CA::C2D& c, const std::vector<CA::State>& qs)
    {
        CA::State w = Q[0];
        CA::State Nw = Q[1];
        CA::State Ew = Q[2];
        CA::State Sw = Q[3];
        CA::State Ww = Q[4];
        CA::State Nb = Q[5];
        CA::State Eb = Q[6];
        CA::State Sb = Q[7];
        CA::State Wb = Q[8];
        CA::State b = Q[9];

        CA::State q = qs[0];
        CA::State qN = qs[1];
        CA::State qE = qs[2];
        CA::State qS = qs[3];
        CA::State qW = qs[4];

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
};
