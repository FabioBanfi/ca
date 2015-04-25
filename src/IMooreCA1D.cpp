#include "IMooreCA1D.h"

namespace CA
{
    std::vector<CA::C1D> IMooreCA1D::N(const CA::C1D& c)
    {
        auto result = std::vector<CA::C1D>(3);

        result[0] = L[CA::mod(c.i - 1, width)];
        result[1] = c;
        result[2] = L[CA::mod(c.i + 1, width)];

        return result;
    }
}