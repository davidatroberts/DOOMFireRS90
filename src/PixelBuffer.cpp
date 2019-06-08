#include "PixelBuffer.h"

struct PixelBufferImpl: public PixelBuffer
{
    PixelBufferImpl(SDL_Surface *screen):
        screen_(screen),
        pitch_(screen_->pitch),
        bytes_per_pixel_(screen_->format->BytesPerPixel)
    {

    }

    void drawPixel(int x, int y, const Colour &colour) override
    {
        Uint32 mapped_colour = SDL_MapRGB(
            screen_->format, 
            colour.r, colour.g, colour.b
        );

        Uint8 *p = (Uint8*)screen_->pixels + y * pitch_ + x * bytes_per_pixel_;
        *(Uint16*)p = mapped_colour;
    }

    void clear() override
    {
        SDL_FillRect(screen_, NULL, SDL_MapRGB(screen_->format, 0, 0, 0));
    }

    SDL_Surface* getScreenSurface() const override
    {
        return screen_;
    }

private:
    SDL_Surface *screen_;
    const Uint16 pitch_;
    const Uint8 bytes_per_pixel_;
};

std::shared_ptr<PixelBuffer> createPixelBuffer(SDL_Surface *surface)
{
    return std::make_shared<PixelBufferImpl>(surface);
}