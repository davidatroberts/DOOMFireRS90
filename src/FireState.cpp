#include "FireState.h"

#include <cmath>
#include <vector>

#include "Context.h"

namespace
{
    const std::vector<Colour> palette = 
    {
        {7, 7, 7}, 
        {31, 7, 7}, 
        {47, 15, 7}, 
        {71, 15, 7}, 
        {87, 23, 7}, 
        {103, 31, 7}, 
        {119, 31, 7}, 
        {143, 39, 7}, 
        {159, 47, 7}, 
        {175, 63, 7}, 
        {191, 71, 7}, 
        {199, 71, 7}, 
        {223, 79, 7}, 
        {223, 87, 7}, 
        {223, 87, 7},
        {215, 95, 7}, 
        {215, 95, 7}, 
        {215, 103, 15}, 
        {207, 111, 15}, 
        {207, 119, 15}, 
        {207, 127, 15}, 
        {207, 135, 23}, 
        {199, 135, 23}, 
        {199, 143, 23}, 
        {199, 151, 31}, 
        {191, 159, 31}, 
        {191, 159, 31}, 
        {191, 167, 39}, 
        {191, 167, 39}, 
        {191, 175, 47}, 
        {183, 175, 47}, 
        {183, 183, 47}, 
        {183, 183, 55}, 
        {207, 207, 111}, 
        {223, 223, 159}, 
        {239, 239, 199}, 
        {255, 255, 255}
    };

    inline float random01()
    {
        return static_cast<float>(rand() / static_cast<float>(RAND_MAX));
    }
}

class FireState: public State
{
public:
    FireState(std::shared_ptr<Context> context): 
        context_(std::move(context)),
        width_(context_->getScreenWidth()),
        height_(context_->getScreenHeight())
    {
        buffer_.resize(width_);
        for (auto x=0; x<width_; ++x)
            buffer_[x].resize(height_);
    }

    void enterState() override
    {
        initFire();
    }

    void leaveState() override
    {
    }

    void update(float delta) override
    {
        doFire();
    }

    void render() override
    {
        context_->getPixelBuffer()->clear();

        for (auto x=0; x<width_; ++x)
        {
            for (auto y=height_-1; y>(height_/2); --y)
            {
                const auto &colour = palette[buffer_[x][y]];
                context_->getPixelBuffer()->drawPixel(x, y, colour);
            }
        }
    }

    void handleKeyDown(const SDLKey &key) override
    {
        switch (key)
        {
            case SDLK_ESCAPE:
                context_->quit();
                break;
            case SDLK_RETURN:
                context_->displayFPS(!context_->displayingFPS());
                break;
            default:
                break;
        }
    }

    void handleKeyUp(const SDLKey &key) override
    {

    }

private:
    std::shared_ptr<Context> context_;
    const int width_;
    const int height_;

    void initFire()
    {
        for (int x=0; x<width_; ++x)
            for (int y=0; y<height_; ++y)
                buffer_[x][y] = 0;

        for (int x=0; x<width_; ++x)
            buffer_[x][height_ - 1] = 36;
    }

    inline void spreadFire(int x, int y)
    {
        const auto spread = random01();
        const auto spread_width = static_cast<int>(floor(random01()*3)+0.5);
        const auto new_x = spread > 0.6 ? x + spread_width : x - spread_width;

        if (new_x > (width_-1) || new_x < 0)
            return;

        const auto decay = floor(random01() * 2.3);

        auto new_value = buffer_[x][y+1] - decay;
        if (new_value < 0)
            new_value = 0;

        buffer_[new_x][y] = new_value;
    }

    void doFire()
    {
        for (int x=0; x<width_; ++x)
        {
            for (int y=(height_ - 2); y>=(height_/2); --y)
            {
                spreadFire(x, y);
            }
        }
    }

    std::vector<std::vector<int>> buffer_;
};

std::shared_ptr<State> createFireState(std::shared_ptr<Context> context)
{
    return std::make_shared<FireState>(context);
}