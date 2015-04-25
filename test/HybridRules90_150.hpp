#pragma once

#include "CA.h"

class HybridRules51_153 :
        public CA::IAnimatedCA1D,
        public CA::IMooreCA1D,
        public CA::IFirstOrderCA1D,
        public CA::IRandomInitCA<CA::C1D>
{
public:

    HybridRules51_153(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 2, delay, save),
            IFirstOrderCA1D(2),
            rule(std::vector<bool>(width))
    {
        for (uint32_t i = 0; i < width; i++)
        {
            rule[i] = rand() % 2;
        }
    }

private:

    std::vector<bool> rule;

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        CA::State ql = qs[0] + 1;
        CA::State qi = qs[1] + 1;
        CA::State qr = qs[2] + 1;

        return Q[CA::mod(ql + rule[c.i] * qi + qr, 2)];
    }
};
