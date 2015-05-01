#pragma once

#include <algorithm>
#include "CA.h"

class AsynchronousRule30 :
        public CA::IAnimatedCA1D,
        public CA::IMooreCA1D,
        public CA::IRandomInitCA<CA::C1D>
{
public:

    AsynchronousRule30(uint32_t width, uint32_t height, uint32_t delay = 0, bool save = false) :
            IAnimatedCA(width, height, 2, delay, save),
            width(width),
            qs(width)
    {
        pi.reserve(width);
        for (uint32_t i = 0; i < width; i++)
            pi.push_back(i);
        std::random_shuffle(pi.begin(), pi.end());
    }

private:

    uint32_t width;
    std::vector<uint32_t> pi;

    CA::State delta(const CA::C1D& c, const std::vector<CA::State>& qs)
    {
        CA::State ql = qs[0] != Q[0];
        CA::State qi = qs[1] != Q[0];
        CA::State qr = qs[2] != Q[0];

        //return Q[((!ql && qi && !qr) || (!qi && qr))]; // 38
        return Q[CA::mod(qi + ql + qr + qi * qr, 2)];
    }

    uint32_t num_of_neighbours = 3;
    std::vector<CA::State> qs;

    CA::State phi(const CA::C1D& c, uint32_t t)
    {
        if (t == 0)
        {
            qs[c.i] = q0(c);

            return q0(c);
        }
        else
        {
            //if (CA::mod(t, width) == pi[c.i])
            //{
                auto c_ = CA::C1D(pi[c.i]);
                auto neighbours = N(c_);
                auto neighbours_states = std::vector<CA::State>();
                neighbours_states.reserve(num_of_neighbours);

                for (auto neighbour : neighbours)
                    neighbours_states.push_back(qs[neighbour.i]);

                return qs[c_.i] = delta(c_, neighbours_states);
            //}
            //else
            //{
            //    return qs[c.i];
            //}
        }
    }
};
