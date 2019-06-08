#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL_video.h>
#include <SDL/SDL_ttf.h>
#include <string>

class Text 
{
public:
	Text(SDL_Surface *surface, TTF_Font *font);

	void renderString(
        const std::string &str, int x, int y, const SDL_Color &colour
    );

private:
	SDL_Surface *surface_;
    TTF_Font *font_;
};

#endif