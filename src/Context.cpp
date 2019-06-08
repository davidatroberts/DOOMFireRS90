#include "Context.h"

#include <string>

#include "PixelBuffer.h"
#include "State.h"
#include "Timer.h"
#include "Text.h"

namespace
{
    std::string fps_str;
}

class ContextImpl: public Context
{
public:
    ContextImpl(
        std::shared_ptr<PixelBuffer> pixel_buffer, 
        int screen_width, int screen_height, 
        Text text): 
        quit_(false), 
        pixel_buffer_(std::move(pixel_buffer)),
        screen_width_(screen_width),
        screen_height_(screen_height),
        text_(std::move(text)),
        display_fps_(true),
        frame_count_(0),
        fps_(0),
        font_colour_{255, 255, 255}
    {
        fps_timer_.start();
        update_timer_.start();
    }

    void quit() override
    {
        quit_ = true;
    }

    bool hasQuit() const override
    {
        return quit_;
    }

    std::shared_ptr<PixelBuffer> getPixelBuffer() const override
    {
        return pixel_buffer_;
    }

    void setState(const std::shared_ptr<State> &state) override
    {
        if (state_)
            state_->leaveState();

        state_ = std::move(state);

        if (state_)
            state_->enterState();
    }

    std::shared_ptr<State> getState() const override
    {
        return state_;
    }

    void update(float dt) override
    {
        state_->update(dt);
        
        frame_count_++;
    }

    void render() override
    {
        if (SDL_MUSTLOCK(pixel_buffer_->getScreenSurface()))
            SDL_LockSurface(pixel_buffer_->getScreenSurface());

        state_->render();

        if (SDL_MUSTLOCK(pixel_buffer_->getScreenSurface()))
            SDL_UnlockSurface(pixel_buffer_->getScreenSurface());

        if (update_timer_.ticks() > 1000)
        {
            fps_ = frame_count_ / (fps_timer_.ticks() / 1000);
            update_timer_.start();
            fps_str = std::to_string(fps_);
        }
        if (display_fps_)
        {
            text_.renderString("FPS: ", 0, 0, font_colour_);
            text_.renderString(fps_str, 30, 0, font_colour_);
        }
    }

    int getScreenWidth() const override
    {
        return screen_width_;
    }

    int getScreenHeight() const override
    {
        return screen_height_;
    }

    void displayFPS(bool display) override
    {
        display_fps_ = display;
    }

    bool displayingFPS() const override
    {
        return display_fps_;
    }

private:
    bool quit_;
    std::shared_ptr<PixelBuffer> pixel_buffer_;
    std::shared_ptr<State> state_;
    const int screen_width_;
    const int screen_height_;
    Text text_;
    bool display_fps_;
    Timer fps_timer_;
    Timer update_timer_;
    int frame_count_;
    int fps_;
    SDL_Colour font_colour_;
};

std::shared_ptr<Context> createContext(
    std::shared_ptr<PixelBuffer> pixel_buffer, int screen_width, int screen_height, Text &text
)
{
    return std::make_shared<ContextImpl>(pixel_buffer, screen_width, screen_height, text);
}