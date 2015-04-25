#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "ICellularAutomaton.h"

#define GRAY(v) ((v) | ((v) << 8) | ((v) << 16))

namespace CA
{
    static bool run = true;

    template <class Cell>
    class IAnimatedCA : virtual public ICellularAutomaton<Cell>
    {
    public:

        IAnimatedCA() { }
        IAnimatedCA(uint32_t width, uint32_t height, uint32_t num_of_states, uint32_t delay = 0, bool save = false) :
                width(width),
                height(height),
                num_of_states(num_of_states),
                delay(delay),
                save(save),
                cells(new uint32_t[width * height]) { }
        virtual void animate() = 0;

    protected:

        uint32_t width;
        uint32_t height;
        uint32_t num_of_states;
        uint32_t delay;
        bool save;
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
        bool saveScreenshotBMP(std::string file_path, SDL_Window*window, SDL_Renderer*renderer)
        {
            SDL_Surface* saveSurface = NULL;
            SDL_Surface* infoSurface = NULL;
            infoSurface = SDL_GetWindowSurface(window);

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
                    if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
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

                        SDL_SaveBMP(saveSurface, file_path.c_str());
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
