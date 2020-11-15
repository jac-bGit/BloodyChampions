#pragma once
#include "SDL_ttf.h"
#include "Game.h"
#include <string>

class Text 
{
public:
	Text(const char * fontPath, int size, const char * text, const SDL_Color &color);

	void setText(std::string text) { textTexture = loadFont(fontPath, size, text.c_str(), color);}

	void render(int x, int y);

	SDL_Texture * loadFont(const std::string &fontPath, int size, const char * text, const SDL_Color color);

private:
	const char * fontPath;
	int size;
    SDL_Surface * textSurface;
	SDL_Texture * textTexture;
	SDL_Color color;
	SDL_Rect textRect;

};
