#ifndef CA_H
#define CA_H

#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#include <type_traits>
#include <SDL2/SDL.h>

#define ALIVE 0x0U
#define DEAD 0xFFFFFFFFU
#define CELL(i, j) cells[i * W + j]
#define SUM(i, j) sums[i * W + j]

namespace CA {

int mod(int x, int m)
{
    int r = x % m;
    return r < 0 ? r + m : r;
}

bool run = true;

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
    virtual inline std::vector<Cell> N(Cell c) = 0;
    virtual inline State delta(Cell c, std::vector<State>) = 0;
    virtual inline State phi(Cell c, int t) = 0;
    virtual inline State q0(Cell c) = 0;
};

template <class Cell>
class AnimatedCA : virtual public CellularAutomaton<Cell>
{
protected:

    AnimatedCA();
    AnimatedCA(int W, int H, int S, int delay = 0, bool save = false) : W(W), H(H), S(S), delay(delay), save(save), cells(new Uint32[W * H]) { }

    virtual void animate() = 0;

    int W;
    int H;
    int S;
    int delay;
    bool save;
    Uint32* cells;

    static int events_thread(void* ptr)
    {
        SDL_Event event;

        while (true)
        {
            SDL_WaitEvent(&event);
            if (event.type == SDL_QUIT || event.key.type == SDLK_q || event.key.type == SDLK_ESCAPE)
            {
                run = false;
                return 0;
            }
        }
    }

    // http://stackoverflow.com/questions/20233469/how-do-i-take-and-save-a-bmp-screenshot-in-sdl-2
    bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer)
    {
        SDL_Surface* saveSurface = NULL;
        SDL_Surface* infoSurface = NULL;
        infoSurface = SDL_GetWindowSurface(SDLWindow);

        if (infoSurface == NULL)
        {
            std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
        }
        else
        {
            unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels == 0)
            {
                std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";

                return false;
            }
            else
            {
                if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
                {
                    std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                    pixels = NULL;

                    return false;
                }
                else
                {
                    saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

                    if (saveSurface == NULL)
                    {
                        std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";

                        return false;
                    }

                    SDL_SaveBMP(saveSurface, filepath.c_str());
                    SDL_FreeSurface(saveSurface);
                    saveSurface = NULL;
                }

                delete[] pixels;
            }

            SDL_FreeSurface(infoSurface);
            infoSurface = NULL;
        }

        return true;

        /* If using OpenGL:
        unsigned char* pixels = new unsigned char[W * H * 4]; // 4 bytes for RGBA
        glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pixels, W, H, 8 * 4, W * 4, 0, 0, 0, 0);
        SDL_SaveBMP(surf, std::to_string(t / H) + std::string(".bmp"));

        SDL_FreeSurface(surf);
        delete [] pixels;*/
    }
};

class AnimatedCA1D : virtual public AnimatedCA<C1D>
{
protected:

    AnimatedCA1D()
    {
        L = std::vector<C1D>(W);
        for (int i = 0; i < W; i++)
            L[i] = C1D(i);

        Q = std::vector<State>(S);
        Q[0] = DEAD;
        Q[1] = ALIVE; // from ALIVE to DEAD ...
    }

public:

    void animate()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateThread(events_thread, NULL, (void*)NULL);

        SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
        Uint32* cells = new Uint32[W * H];
        memset(cells, DEAD, W * H * sizeof(Uint32));

        int t = 0;
        while (run)
        {
            for (int i = 0; i < W; i++)
                cells[mod(t, H) * W + i] = phi(L[i], t);

            SDL_UpdateTexture(texture, NULL, cells, W * sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);

            t++;
            if (t % H == 0 && save)
            {
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << t / H;
                saveScreenshotBMP(ss.str() + std::string(".bmp"), window, renderer);
            }
        }

        run = true;
        delete[] cells;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

class AnimatedCA2D : virtual public AnimatedCA<C2D>
{
protected:

    AnimatedCA2D()
    {
        L = std::vector<C2D>(W * H);
        for (int i = 0; i < W * H; i++)
            L[i] = (C2D(mod(i, W), (i - mod(i, W)) / W));

        Q = std::vector<State>(S);
        Q[0] = DEAD;
        Q[1] = ALIVE; // for alive to dead ....
    }

public:

    void animate()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateThread(events_thread, NULL, (void*)NULL);

        SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
        Uint32* cells = new Uint32[W * H];

        for (int i = 0; i < W * H; i++)
            cells[i] = phi(L[i], 0);

        int t = 0;
        while (run)
        {
            for (int i = 0; i < W * H; i++)
                cells[i] = phi(L[i], t);

            SDL_UpdateTexture(texture, NULL, cells, W * sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);

            t++;
            if (save)
            {
                std::stringstream ss;
                ss << std::setw(4) << std::setfill('0') << t;
                saveScreenshotBMP(ss.str() + std::string(".bmp"), window, renderer);
            }
        }

        run = true;
        delete[] cells;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

class FirstOrderCA1D : virtual public CellularAutomaton<C1D>
{
protected:

    FirstOrderCA1D(int size, int d) : d(d), current_t(0), old_qs(size), new_qs(size) { }

    inline State phi(C1D c, int t)
    {
        if (t == 0)
        {
            new_qs[c.i] = q0(c);

            return q0(c);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<State>();
            neigh_qs.reserve(d);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old_qs[neighbour.i]);

            new_qs[c.i] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }

private:

    int d;
    int current_t;
    std::vector<State> old_qs;
    std::vector<State> new_qs;
};

class FirstOrderCA2D : virtual public CellularAutomaton<C2D>
{
protected:

    FirstOrderCA2D(int size, int offset, int d) : offset(offset), d(d), current_t(0), old_qs(size), new_qs(size) { }

    inline State phi(C2D c, int t)
    {
        if (t == 0)
        {
            new_qs[c.x + offset * c.y] = q0(c);

            return q0(c);
        }
        else
        {
            if (t != current_t)
            {
                current_t = t;
                old_qs = new_qs;
            }

            auto neighbours = N(c);
            auto neigh_qs = std::vector<CA::State>();
            neigh_qs.reserve(d);

            for (auto neighbour : neighbours)
                neigh_qs.push_back(old_qs[neighbour.x + offset * neighbour.y]);

            new_qs[c.x + offset * c.y] = delta(c, neigh_qs);

            return delta(c, neigh_qs);
        }
    }

private:

    int d;
    int offset;
    int current_t;
    std::vector<State> old_qs;
    std::vector<State> new_qs;
};

}

#endif // CA_H
