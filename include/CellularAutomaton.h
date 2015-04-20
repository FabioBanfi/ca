#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <iostream>
#include <vector>

namespace CA {

static int mod(int x, int m)
{
    int r = x % m;
    return r < 0 ? r + m : r;
}

typedef int State;

struct C1D
{
    int i;
    C1D() { i = 0; }
    C1D(int i) : i(i) { }
    bool operator==(const C1D& c) const { return this->i == c.i; }
    bool operator!=(const C1D& c) const { return this->i != c.i; }
    friend std::ostream& operator<<(std::ostream& os, const C1D& c);
};
inline std::ostream& operator<<(std::ostream& os, const C1D& c) { return os << "<" << c.i << ">"; }

struct C2D
{
    int x, y;
    C2D() { x = 0, y = 0; }
    C2D(int x, int y) : x(x), y(y) { }
    bool operator==(const C2D& c) const { return this->x == c.x && this->y == c.y; }
    bool operator!=(const C2D& c) const { return this->x != c.x || this->y != c.y; }
    friend std::ostream& operator<<(std::ostream& os, const C2D& c);
};
inline std::ostream& operator<<(std::ostream& os, const C2D& c) { return os << "<" << c.x << ", " << c.y << ">"; }

template <class Cell>
class CellularAutomaton
{
protected:

    std::vector<Cell> L;
    std::vector<State> Q;
    virtual std::vector<Cell> N(Cell c) = 0;
    virtual State delta(Cell c, std::vector<State>) = 0;
    virtual State phi(Cell c, int t) = 0;
    virtual State q0(Cell c) = 0;
};

} // CA

#endif // CELLULAR_AUTOMATON_H
