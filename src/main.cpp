#include <iostream>
#include <vector>
#include <cmath>
#include <SDL/SDL.h>

#include "Context.h"
#include "FireState.h"
#include "PixelBuffer.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 320
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 240
#endif

#ifndef SCREEN_BPP
#define SCREEN_BPP 16
#endif

namespace
{
    SDL_Event event;
}

SDL_Surface* initSDL(int width, int height, int bpp)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1)
        return nullptr;

    auto screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == nullptr)
        return nullptr;

    SDL_ShowCursor(SDL_DISABLE);

    if (SDL_Flip(screen) == -1)
        return nullptr;

    if (TTF_Init() == -1)
        return nullptr;

    return screen;
}

void processEvents(const std::shared_ptr<State> &state)
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
            state->handleKeyDown(event.key.keysym.sym);
        else if (event.type == SDL_KEYUP)
            state->handleKeyUp(event.key.keysym.sym);
    }
}

int main(int argc, char *argv[])
{
    auto screen = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    if (!screen)
    {
        std::cout << "Failed to init SDL\n";
        return 1;
    }

    auto font = TTF_OpenFont("assets/font.ttf", 14);
    if (!font)
    {
        std::cout << "Failed to load the font\n";
        return 1;
    }
    Text text(screen, font);

    auto context = createContext(createPixelBuffer(screen), SCREEN_WIDTH, SCREEN_HEIGHT, text);
    context->setState(createFireState(context));

    float delta = 0.0f;
    uint32_t old_time, current_time;
    current_time = SDL_GetTicks();

    while (!context->hasQuit())
    {
        old_time = current_time;
        current_time = SDL_GetTicks();
        delta = static_cast<float>(current_time - old_time) / 1000.0f;

        processEvents(context->getState());

        context->update(delta);

        context->render();

        SDL_Flip(screen);
    }

    SDL_Quit();
    return 0;
}