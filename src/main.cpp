#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>

#define ALIVE 0U
#define DEAD -1U
#define CELL(i, j) cells[i * w + j]
#define SUM(i, j) sums[i * w + j]

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

inline int mod(int a, int b)
{
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

int main()
{
    int w = 1023;
    int h = 1023;
    int dx = 511;
    int dy = 511;
    int delay = 0;
    bool random = false;

                       //  Stay alive:                    Birth:
                       //  0  1  2  3  4  5  6  7  8      0  1  2  3  4  5  6  7  8
    const int life[18] = { 0, 0, 1, 1, 0, 0, 0, 0, 0,     0, 0, 0, 1, 0, 0, 0, 0, 0 };
    const int rand1[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 0, 0, 0, 0, 0, 0, 0 };
    const int rand2[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 0, 0, 0, 0, 0, 0 };
    const int rand3[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 0, 0, 0, 0, 0 }; // Circles
    const int rand4[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 1, 0, 0, 0, 0 }; // Templars cross
    const int rand5[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 1, 1, 0, 0, 0 }; // Arrows
    const int rand6[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 1, 1, 1, 0, 0 }; // Squares
    const int rand7[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 1, 1, 1, 1, 0 }; // Squares (same as 6!)
    const int rand8[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,     0, 1, 1, 1, 1, 1, 1, 1, 1 }; // Squares (same as 6!)
    const int rand9[18] = { 1, 0, 1, 1, 1, 1, 1, 0, 0,     0, 1, 1, 0, 0, 0, 1, 0, 1 };
    const int* rule = rand9;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateThread(events_thread, NULL, (void*)NULL);

    SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
    Uint32* cells = new Uint32[w * h];
    Uint32 sums[w * h];

    srand(time(NULL));
    memset(cells, DEAD, w * h * sizeof(Uint32));
    for (int r = dy; r < h - dy; r++)
        for (int c = dx; c < w - dx; c++)
            CELL(r, c) = random ? (rand() % 2) * DEAD : ALIVE;

    //for (int i = 0; i < w * h; i++)
    //    cells[i] = (rand() % 2) * DEAD;

    while (run)
    {
        SDL_UpdateTexture(texture, NULL, cells, w * sizeof(Uint32));

        memset(sums, 0, w * h * sizeof(Uint32));
        //for (int r = 0; r < h; r++)
        //    for (int c = 0; c < w; c++)
        for (int r = 1; r < h - 1; r++)
            for (int c = 1; c < w - 1; c++)
                for (int i = r - 1; i <= r + 1; i++)
                    for (int j = c - 1; j <= c + 1; j++)
                        if (mod(i, h) != r || mod(j, w) != c)
                            if (CELL(mod(i, h), mod(j, w)) == ALIVE)
                                SUM(r, c)++;


        //for (int i = 0; i < w * h; i++)
            //cells[i] = (cells[i] == ALIVE && (sums[i] == 2 || sums[i] == 3)) || (cells[i] == DEAD && sums[i] == 3) ? ALIVE : DEAD;
        for (int r = 0; r < h; r++)
            for (int c = 0; c < w; c++)
                if (CELL(r, c) == ALIVE)
                    CELL(r, c) =
                    (rule[0] && SUM(r, c) == 0) ||
                    (rule[1] && SUM(r, c) == 1) ||
                    (rule[2] && SUM(r, c) == 2) ||
                    (rule[3] && SUM(r, c) == 3) ||
                    (rule[4] && SUM(r, c) == 4) ||
                    (rule[5] && SUM(r, c) == 5) ||//
                    (rule[6] && SUM(r, c) == 6) ||
                    (rule[7] && SUM(r, c) == 7) ||
                    (rule[8] && SUM(r, c) == 8)
                    ? ALIVE : DEAD;
                else
                    CELL(r, c) =
                    (rule[9] && SUM(r, c) == 0) ||
                    (rule[10] && SUM(r, c) == 1) ||
                    (rule[11] && SUM(r, c) == 2) ||
                    (rule[12] && SUM(r, c) == 3) ||
                    (rule[13] && SUM(r, c) == 4) ||
                    (rule[14] && SUM(r, c) == 5) ||
                    (rule[15] && SUM(r, c) == 6) ||
                    (rule[16] && SUM(r, c) == 7) ||
                    (rule[17] && SUM(r, c) == 8)
                    ? ALIVE : DEAD;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }

    delete[] cells;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
