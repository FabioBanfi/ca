#pragma once

#include "CA.h"

class SecondOrderRule150 :
        public CA::IAnimatedCA1D,
        public CA::IMooreCA1D,
        public CA::ISecondOrderCA1D,
        public CA::IRandomInitCA<CA::C1D>
{
public:

    SecondOrderRule150(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 2, delay, save),
            ISecondOrderCA1D(3) { }

private:

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        CA::State ql = qs[0] + 1;
        CA::State qi = qs[1] + 1;
        CA::State qr = qs[2] + 1;

        //return Q[CA::mod((qi + 1) * (ql + qr), 2)]; // Rule 18 (test)
        return Q[CA::mod(ql + qi + qr, 2)];
    }
};
