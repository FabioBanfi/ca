#ifndef SECOND_ORDER_RULE_150_H
#define SECOND_ORDER_RULE_150_H

#include <cstdint>
#include "CA.h"

class SecondOrderRule150 :
        public CA::AnimatedCA1D,
        public CA::SecondOrderCA1D,
        public CA::RandomInitCA<CA::C1D>
{
public:

    SecondOrderRule150(uint32_t W, uint32_t H, uint32_t delay = 0, bool save = false) :
            AnimatedCA(W, H, 2, delay, save),
            SecondOrderCA1D(W, 3),
            RandomInitCA(2)
    { }

private:

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

        //return Q[CA::mod((qi + 1) * (ql + qr), 2)]; // Rule 18 (test)
        return Q[CA::mod(ql + qi + qr, 2)];
    }
};

#endif // SECOND_ORDER_RULE_150_H
