#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

struct PixelBuffer;
struct State;
class Text;

struct Context
{
    virtual ~Context() = default;
    virtual void quit() = 0;
    virtual bool hasQuit() const = 0;
    virtual std::shared_ptr<PixelBuffer> getPixelBuffer() const = 0;
    virtual void setState(const std::shared_ptr<State> &state) = 0;
    virtual std::shared_ptr<State> getState() const = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual int getScreenWidth() const = 0;
    virtual int getScreenHeight() const = 0;
    virtual void displayFPS(bool display) = 0;
    virtual bool displayingFPS() const = 0;
};

std::shared_ptr<Context> createContext(
    std::shared_ptr<PixelBuffer> pixel_buffer, int screen_width, int screen_height, Text &text
);

#endif