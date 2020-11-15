#include "Text.h"

Text::Text(const char * fontPath, int size, const char * text, const SDL_Color &color) {
	textTexture = loadFont(fontPath, size, text, color);
	this->size = size;
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

	this->fontPath = fontPath;
	this->color = color;
}

void Text::render(int x, int y){
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(Game::renderer, textTexture, nullptr, &textRect);
}

SDL_Texture * Text::loadFont(const std::string &fontPath, int size, const char * text, const SDL_Color color) {
    TTF_Font * font = TTF_OpenFont(fontPath.c_str(), size);

	if (!font)
		std::cout << "no font" << std::endl;

	auto text_surface = TTF_RenderText_Solid(font, text, color);

	auto text_texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);


	SDL_FreeSurface(text_surface);
	return text_texture;
}