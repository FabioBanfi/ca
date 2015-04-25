#pragma once

#include "CA.h"

class Rule30 :
        public CA::IAnimatedCA1D,
        public CA::IMooreCA1D,
        public CA::IFirstOrderCA1D,
        public CA::ICentralInitCA1D
{
public:

    Rule30(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 2, delay, save),
            IFirstOrderCA1D(3),
            ICentralInitCA1D(1, 0) { }

private:

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        CA::State ql = qs[0] + 1;
        CA::State qi = qs[1] + 1;
        CA::State qr = qs[2] + 1;

        return Q[CA::mod(qi + ql + qr + qi * qr, 2)];
    }
};
