#include "IVonNeumannCA2D.h"

namespace CA
{
    std::vector<CA::C2D> IVonNeumannCA2D::N(const CA::C2D& c)
    {
        auto result = std::vector<CA::C2D>();

        result.reserve(5);
        result.push_back(c);
        result.push_back(L[CA::mod(c.x, width) + width * CA::mod(c.y - 1, height)]);
        result.push_back(L[CA::mod(c.x + 1, width) + width * CA::mod(c.y, height)]);
        result.push_back(L[CA::mod(c.x, width) + width * CA::mod(c.y + 1, height)]);
        result.push_back(L[CA::mod(c.x - 1, width) + width * CA::mod(c.y, height)]);

        return result;
    }
}