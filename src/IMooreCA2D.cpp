#include "IMooreCA2D.h"

namespace CA
{
    std::vector<CA::C2D> IMooreCA2D::N(const CA::C2D& c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(9);
        for (int32_t k = -1; k <= 1; k++)
            for (int32_t j = -1; j <= 1; j++)
                result.push_back(L[CA::mod(c.x + j, width) + width * CA::mod(c.y + k, height)]);

        return result;
    }
}