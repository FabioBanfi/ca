#include <iomanip>
#include <sstream>
#include "IAnimatedCA2D.h"

namespace CA
{
    IAnimatedCA2D::IAnimatedCA2D()
    {
        L = std::vector<C2D>(width * height);
        for (uint32_t i = 0; i < width * height; i++)
            L[i] = (C2D(mod(i, width), (i - mod(i, width)) / width));

        Q = std::vector<State>(num_of_states);
        int d = 255 / (num_of_states - 1);
        for (uint32_t s = 0; s < num_of_states; s++)
            Q[s] = GRAY(255 - s * d);
    }

    void IAnimatedCA2D::animate()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateThread(events_thread, NULL, (void*)NULL);

        SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width,
                                                 height);

        uint32_t t = 0;
        while (run)
        {
            for (uint32_t i = 0; i < width * height; i++)
                cells[i] = phi(L[i], t);

            SDL_UpdateTexture(texture, NULL, cells, width * static_cast<uint32_t>(sizeof(uint32_t)));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);

            t++;
            if (save)
            {
                std::stringstream ss;
                ss << std::setw(4) << std::setfill('0') << t;
                saveScreenshotBMP(ss.str().append(std::string(".bmp")), window, renderer);
            }
        }

        run = true;
        delete[] cells;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
