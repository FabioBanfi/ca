#ifndef ANIMATED_CA_H
#define ANIMATED_CA_H

#include <iostream>
#include <SDL2/SDL.h>
#include "CellularAutomaton.h"

#define BLACK 0x0U
#define WHITE 0xFFU
#define GRAY(v) ((v) | ((v) << 8) | ((v) << 16))

namespace CA
{
    static bool run = true;

    template <class Cell>
    class AnimatedCA : virtual public CellularAutomaton<Cell>
    {
    public:

        AnimatedCA() { }
        AnimatedCA(uint32_t W, uint32_t H, uint32_t S, uint32_t delay = 0, bool save = false) :
                W(W),
                H(H),
                S(S),
                delay(delay),
                save(save),
                cells(new uint32_t[W * H]) { }

        virtual void animate() = 0;

        uint32_t W;
        uint32_t H;
        uint32_t S;
        uint32_t delay;
        bool save;

    protected:

        uint32_t* cells;

        static int32_t events_thread(void* ptr)
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
                std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << std::endl;
            }
            else
            {
                u_char* pixels = new (std::nothrow) u_char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
                if (pixels == nullptr)
                {
                    std::cerr << "Unable to allocate memory for screenshot pixel data buffer!" << std::endl;

                    return false;
                }
                else
                {
                    if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
                    {
                        std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << std::endl;
                        pixels = NULL;

                        return false;
                    }
                    else
                    {
                        saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

                        if (saveSurface == NULL)
                        {
                            std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << std::endl;

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
        }
    };
}

#endif // ANIMATED_CA_H
