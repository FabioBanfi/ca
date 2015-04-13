#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <ctime>

#define ALIVE 0U
#define DEAD -1U
#define CELL(i, j) cells[i * w + j]
#define SUM(i, j) sums[i * w + j]

namespace CA {

bool run = true;

static int events_thread(void* ptr)
{
    SDL_Event event;

    while (true)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            run = false;
            return 0;
        }
    }
}




template<int d>
struct Cell;

template<>
struct Cell<1>
{
    Cell<1>() { }
    Cell<1>(int i) : i(i) { }
    int i;
};

template<>
struct Cell<2>
{
    Cell<2>() { }
    Cell<2>(int x, int y) : x(x), y(y) { }
    int x;
    int y;
};


template<int d>
class CellularAutomaton
{
public:





    int w;
    int h;

    Uint32* cells = new Uint32[w * h];

    CellularAutomaton(int w, int h) : w(w), h(h) { }

    typedef int State;

   // struct Cell { virtual ~Cell() { } };
    struct Cell1D //: Cell
    {
        Cell1D(int i) : i(i) { }
        int i;
    };
    struct Cell2D //: Cell
    {
        Cell2D(int x, int y) : x(x), y(y) { }
        int x;
        int y;
    };

    virtual inline std::vector<Cell<d>> N(Cell<d> c) = 0;
    virtual inline State delta(Cell<d> c, std::vector<State>) = 0;
    virtual inline State phi(Cell<d> c, int t) = 0;
    virtual inline State q0(Cell<d> c) = 0;

    void show()
    {
        switch (d)
        {
        case 1:
            break;

        case 2:

            int dx = 450;
            int dy = 450;

            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateThread(events_thread, NULL, (void*)NULL);

            SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
            Uint32* cells = new Uint32[w * h];
            Uint32 sums[w * h];

            srand(time(NULL));
            memset(cells, DEAD, w * h * sizeof(Uint32));
            for (int r = dy + 1; r < h - dy - 1; r++)
                for (int c = dx + 1; c < w - dx - 1; c++)
                    CELL(r, c) = (rand() % 2) * DEAD;

            //for (int i = 0; i < w * h; i++)
            //    cells[i] = (rand() % 2) * DEAD;

            while (run)
            {
                SDL_UpdateTexture(texture, NULL, cells, w * sizeof(Uint32));

                memset(sums, 0, w * h * sizeof(Uint32));
                for (int r = 1; r < h - 1; r++)
                    for (int c = 1; c < w - 1; c++)
                        for (int i = r - 1; i <= r + 1; i++)
                            for (int j = c - 1; j <= c + 1; j++)
                                if (i != r || j != c)
                                    if (CELL(i, j) == ALIVE)
                                        SUM(r, c)++;

                for (int r = 1; r < h - 1; r++)
                {
                    for (int c = 1; c < w - 1; c++)
                    {
                        auto neighbours = N(Cell<2>(c, r));
                        for (auto neighbour : neighbours)
                            std::cout << neighbour.x << std::endl;
                    }
                }

                //for (int i = 0; i < w * h; i++)
                    //cells[i] = (cells[i] == ALIVE && (sums[i] == 2 || sums[i] == 3)) || (cells[i] == DEAD && sums[i] == 3) ? ALIVE : DEAD;
                /*for (int r = 1; r < h - 1; r++)
                    for (int c = 1; c < w - 1; c++)
                        if (CELL(r, c) == ALIVE)
                            CELL(r, c) =
                            (0 && SUM(r, c) == 0) ||
                            (0 && SUM(r, c) == 1) ||
                            (0 && SUM(r, c) == 2) ||
                            (0 && SUM(r, c) == 3) ||
                            (0 && SUM(r, c) == 4) ||
                            (1 && SUM(r, c) == 5) ||
                            (1 && SUM(r, c) == 6) ||
                            (1 && SUM(r, c) == 7) ||
                            (1 && SUM(r, c) == 8)
                            ? ALIVE : DEAD;
                        else
                            CELL(r, c) =
                            (0 && SUM(r, c) == 0) ||
                            (0 && SUM(r, c) == 1) ||
                            (0 && SUM(r, c) == 2) ||
                            (1 && SUM(r, c) == 3) ||
                            (0 && SUM(r, c) == 4) ||
                            (1 && SUM(r, c) == 5) ||
                            (1 && SUM(r, c) == 6) ||
                            (1 && SUM(r, c) == 7) ||
                            (1 && SUM(r, c) == 8)
                            ? ALIVE : DEAD;*/

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(0);
            }

            delete[] cells;
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();

            break;
        }
    }
};

class Life : public CellularAutomaton<2>
{
public:
    Life(int w, int h) : CellularAutomaton(w, h) { }

    inline std::vector<Cell<2>> N(Cell<2> c)
    {
        auto result = std::vector<Cell<2>>(9);
        for (int r = 1; r < h - 1; r++)
            for (int c = 1; c < w - 1; c++)
                for (int i = r; i <= r; i++)
                    for (int j = c; j <= c; j++)
                        result.push_back(Cell<2>(i % h, j % w));

        return result;
    }

    inline State delta(Cell<2> c, std::vector<State> qs)
    {
        int sum = qs[0] + qs[1] + qs[2] + qs[3] + qs[5] + qs[6] + qs[7] + qs[8];
        return (qs[4] == 1 && (sum == 2 || sum == 3)) || (qs[4] == 0 && sum == 3);
    }

    inline State phi(Cell<2> c, int t)
    {
        return 0;//return delta(c, );
    }

    inline State q0(Cell<2> c)
    {
        return 0;
    }
};

/*inline std::vector<Cell> N(Cell)
{
    auto result = std::vector<Cell>(9);
    for (int r = 1; r < h - 1; r++)
        for (int c = 1; c < w - 1; c++)
            for (int i = r - 1; i <= r + 1; i++)
                for (int j = c - 1; j <= c + 1; j++)
                    if (i != r || j != c)
                        if (CELL(i, j) == ALIVE)
}*/


}

int main()
{
    CA::Life(1024, 1024).show();

    return 0;
}
