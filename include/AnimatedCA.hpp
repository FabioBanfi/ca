#ifndef ANIMATED_CA_H
#define ANIMATED_CA_H

#include "CellularAutomaton.h"

namespace CA {

static bool run = true;

template <class Cell>
class AnimatedCA : virtual public CellularAutomaton<Cell>
{
protected:

    AnimatedCA() { }
    AnimatedCA(int W, int H, int S, int delay = 0, bool save = false) : W(W), H(H), S(S), delay(delay), save(save), cells(new int[W * H]) { }

    virtual void animate() = 0;

    int W;
    int H;
    int S;
    int delay;
    bool save;
    int* cells;

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

} // CA

#endif // ANIMATED_CA_H
