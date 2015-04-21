#include "../include/AnimatedCA2D.h"

namespace CA {

AnimatedCA2D::AnimatedCA2D()
{
    L = std::vector<C2D>(W * H);
    for (uint32_t i = 0; i < W * H; i++)
        L[i] = (C2D(mod(i, W), (i - mod(i, W)) / W));

    Q = std::vector<State>(S);
    int d = 255 / (S - 1);
    for (uint32_t s = 0; s < S; s++)
        Q[s] = GRAY(255 - s * d);
}

void AnimatedCA2D::animate()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateThread(events_thread, NULL, (void*)NULL);

    SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);

    uint32_t t = 0;
    while (run)
    {
        for (uint32_t i = 0; i < W * H; i++)
            cells[i] = phi(L[i], t);

        SDL_UpdateTexture(texture, NULL, cells, W * static_cast<uint32_t>(sizeof(uint32_t)));
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

} // CA
