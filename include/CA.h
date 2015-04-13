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
class AnimatedCA : public CellularAutomaton<Cell>
{
protected:

    AnimatedCA(int W, int H, int S, int delay = 0, bool save = false) : W(W), H(H), S(S), delay(delay), save(save) { }

    virtual void animate() = 0;

    int W;
    int H;
    int S;
    bool save;
    int delay;
    Uint32* cells = new Uint32[W * H];

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

class AnimatedCA1D : public AnimatedCA<C1D>
{
protected:

    AnimatedCA1D(int W, int H, int S, int delay = 0, bool save = false) : AnimatedCA(W, H, S, delay, save)
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
                CELL(mod(t, H), i) = phi(L[i], t);

            SDL_UpdateTexture(texture, NULL, cells, W * sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);

            t++;
            if(t % H == 0 && save)
                saveScreenshotBMP(std::to_string(t / H) + std::string(".bmp"), window, renderer);
        }

        run = true;
        delete[] cells;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

class AnimatedCA2D : public AnimatedCA<C2D>
{
protected:

    AnimatedCA2D(int W, int H, int S, int delay = 0, bool save = false) : AnimatedCA(W, H, S, delay, save)
    {
        L = std::vector<C2D>(W * H);
        for (int i = 0; i < W * H; i++){
            L[i] = (C2D(mod(i, W), (i - mod(i, W)) / W));}

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
            std::stringstream ss;
            ss << std::setw(4) << std::setfill('0') << t;
            saveScreenshotBMP(ss.str() + std::string(".bmp"), window, renderer);
        }

        run = true;
        delete[] cells;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

};


template <class Cell>
class FirstOrderCA : public AnimatedCA<Cell>
{
protected:

    inline State phi(Cell c, int t)
    {
        if (t == 0)
        {
            if (std::is_same<Cell, C1D>::value)
                new_qs[((C1D)c).i] = q0(c);
            else if (std::is_same<Cell, C2D>::value)
                new_qs[((C2D)c).x + this->W * ((C2D)c).y] = q0(c);

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
            auto nstates = std::vector<State>();
            //nstates.reserve(3);
            for (auto neighbour : neighbours)
                if (std::is_same<Cell, C1D>::value)
                    nstates.push_back(old_qs[((C1D)neighbour).i]);
                else if (std::is_same<Cell, C2D>::value)
                    nstates.push_back(old_qs[((C2D)neighbour).x + this->W * ((C2D)neighbour).y]);


            if (std::is_same<Cell, C1D>::value)
                new_qs[((C1D)c).i] = delta(c, nstates);
            else if (std::is_same<Cell, C2D>::value)
                new_qs[((C2D)c).x + this->W * ((C2D)c).y] = delta(c, nstates);
            return delta(c, nstates);
        }
    }

private:

    int current_t;
    std::vector<State> old_qs;
    std::vector<State> new_qs;
};



}

#endif // CA_H
