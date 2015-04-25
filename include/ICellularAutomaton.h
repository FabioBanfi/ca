#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

namespace CA
{
    #ifdef __GNUG__
    static uint32_t mod (int32_t, uint32_t) __attribute__ ((unused));
    #endif
    static uint32_t mod(int32_t value, uint32_t modulo)
    {
        int32_t remainder = value % static_cast<int32_t>(modulo);
        return static_cast<uint32_t>(remainder < 0 ? remainder + modulo : remainder);
    }

    typedef uint32_t State;

    struct C1D
    {
        uint32_t i;
        C1D() : i(0) { }
        C1D(uint32_t i) : i(i) { }
        bool operator==(const C1D& c) const { return this->i == c.i; }
        bool operator!=(const C1D& c) const { return this->i != c.i; }
        friend std::ostream& operator<<(std::ostream&, const C1D&);
    };
    inline std::ostream& operator<<(std::ostream& os, const C1D& c) { return os << "<" << c.i << ">"; }

    struct C2D
    {
        uint32_t x, y;
        C2D() : x(0), y(0) { }
        C2D(uint32_t x, uint32_t y) : x(x), y(y) { }
        bool operator==(const C2D& c) const { return this->x == c.x && this->y == c.y; }
        bool operator!=(const C2D& c) const { return this->x != c.x || this->y != c.y; }
        friend std::ostream& operator<<(std::ostream&, const C2D&);
    };
    inline std::ostream& operator<<(std::ostream& os, const C2D& c) { return os << "<" << c.x << ", " << c.y << ">"; }

    template <class Cell>
    class ICellularAutomaton
    {
    protected:

        std::vector<Cell> L;
        std::vector<State> Q;
        virtual std::vector<Cell> N(const Cell&) = 0;
        virtual State delta(const Cell&, const std::vector<State>&) = 0;
        virtual State phi(const Cell&, uint32_t) = 0;
        virtual State q0(const Cell&) = 0;
    };
}
