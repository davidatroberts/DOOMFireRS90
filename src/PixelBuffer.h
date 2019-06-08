#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <memory>
#include <SDL/SDL_video.h>

struct Colour
{
    Uint8 r, g, b;
};

struct PixelBuffer
{
    virtual ~PixelBuffer() = default;
    virtual void drawPixel(int x, int y, const Colour &colour) = 0;
    virtual void clear() = 0;
    virtual SDL_Surface* getScreenSurface() const = 0;
};

std::shared_ptr<PixelBuffer> createPixelBuffer(SDL_Surface *surface);

#endif