#ifndef RULE_30_H
#define RULE_30_H

#include <cstdint>
#include "../include/CA.h"

class Rule30 : public CA::AnimatedCA1D, public CA::FirstOrderCA1D
{
public:

    Rule30(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) : AnimatedCA(W, H, 2, delay, save), FirstOrderCA1D(W, 3) { }

private:

    std::vector<CA::C1D> N(CA::C1D c)
    {
        auto result = std::vector<CA::C1D>(3);

        result[0] = L[CA::mod(c.i - 1, W)];
        result[1] = c;
        result[2] = L[CA::mod(c.i + 1, W)];

        return result;
    }

    CA::State delta(CA::C1D c, std::vector<CA::State> qs)
    {
        CA::State ql = qs[0] + 1;
        CA::State qi = qs[1] + 1;
        CA::State qr = qs[2] + 1;

        return Q[CA::mod(qi + ql + qr + qi * qr, 2)];
    }

    CA::State q0(CA::C1D c)
    {
        return Q[c.i == W / 2 ? 1 : 0];
    }
};

#endif // RULE_30_H
