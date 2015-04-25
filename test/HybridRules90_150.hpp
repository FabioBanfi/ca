#ifndef HYBRID_RULES_51_153_H
#define HYBRID_RULES_51_153_H

#include <cstdint>
#include "CA.h"

class HybridRules51_153 :
        public CA::IAnimatedCA1D,
        public CA::IFirstOrderCA1D,
        public CA::IRandomInitCA<CA::C1D>
{
public:

    HybridRules51_153(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(W, H, 2, delay, save),
            IFirstOrderCA1D(W, 2),
            IRandomInitCA(2),
            rule(std::vector<bool>(W))
    {
        for (uint32_t i = 0; i < W; i++)
        {
            rule[i] = rand() % 2;
        }
    }

private:

    std::vector<bool> rule;

    std::vector<CA::C1D> N(const CA::C1D& c)
    {
        auto result = std::vector<CA::C1D>(3);

        result[0] = L[CA::mod(c.i - 1, W)];
        result[1] = c;
        result[2] = L[CA::mod(c.i + 1, W)];

        return result;
    }

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        CA::State ql = qs[0] + 1;
        CA::State qi = qs[1] + 1;
        CA::State qr = qs[2] + 1;

        return Q[CA::mod(ql + rule[c.i] * qi + qr, 2)];
    }
};

#endif // HYBRID_RULES_51_153_H
