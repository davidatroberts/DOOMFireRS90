#include "Text.h"

Text::Text(SDL_Surface *surface, TTF_Font *font): 
    surface_(surface), font_(font)
{
}

void Text::renderString(
    const std::string &str, int x, int y, const SDL_Color &colour
) 
{
	SDL_Surface *msg = TTF_RenderText_Solid(font_, str.c_str(), colour);

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(msg, NULL, surface_, &offset);
}