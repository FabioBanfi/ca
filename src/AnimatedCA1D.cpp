#include <iomanip>
#include <sstream>
#include "AnimatedCA1D.h"

namespace CA
{
    AnimatedCA1D::AnimatedCA1D()
    {
        L = std::vector<C1D>(W);
        for (uint32_t i = 0; i < W; i++)
            L[i] = C1D(i);

        Q = std::vector<State>(S);
        int d = 255 / (S - 1);
        for (uint32_t s = 0; s < S; s++)
            Q[s] = GRAY(255 - s * d);
    }

    void AnimatedCA1D::animate()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateThread(events_thread, NULL, (void*)NULL);

        SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
        memset(cells, WHITE, W * H * sizeof(uint32_t));

        uint32_t t = 0;
        while (run)
        {
            for (uint32_t i = 0; i < W; i++)
                cells[mod(t, H) * W + i] = phi(L[i], t);

            SDL_UpdateTexture(texture, NULL, cells, W * static_cast<uint32_t>(sizeof(uint32_t)));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay);

            t++;
            if (t % H == 0 && save)
            {
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << t / H;
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
