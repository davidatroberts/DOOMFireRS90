#ifndef STATE_H
#define STATE_H

#include <memory>
#include <utility>
#include <SDL/SDL_keysym.h>
#include <SDL/SDL_video.h>

#include "PixelBuffer.h"
#include "Timer.h"

struct State
{
    virtual ~State() = default;
    virtual void enterState() = 0;
    virtual void leaveState() = 0;
    virtual void update(float delta) = 0;
    virtual void render() = 0;
    virtual void handleKeyDown(const SDLKey &key) = 0;
    virtual void handleKeyUp(const SDLKey &key) = 0;
};

#endif