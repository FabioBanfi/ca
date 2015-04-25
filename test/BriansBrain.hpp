#pragma once

#include "CA.h"

class BriansBrain :
        public CA::IAnimatedCA2D,
        public CA::IMooreCA2D,
        public CA::IFirstOrderCA2D,
        public CA::IRandomInitCA<CA::C2D>
{
public:

    BriansBrain(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 3, delay, save),
            IFirstOrderCA2D(9)
    {
        srand(time(NULL));
    }

private:

    CA::State delta(const CA::C2D& c, const std::vector<CA::State>& qs)
    {
        uint32_t sum = 0;

        for (uint32_t i = 0; i < 9; i++)
            if (i != 4)
                if (qs[i] == Q[2])
                    sum++;

        return Q[qs[4] == Q[0] && sum == 2 ? 2 : qs[4] == Q[2]];
    }
};
