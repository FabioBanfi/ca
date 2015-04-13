#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#include <SDL2/SDL.h>

#define ALIVE 0x0U
#define DEAD 0xFFFFFFFFU

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
};

struct C2D
{
    int x, y;
    C2D() { x = 0, y = 0; }
    C2D(int x, int y) : x(x), y(y) { }
};

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
