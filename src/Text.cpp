#include "Text.h"

Text::Text()
{
	font = NULL;
	font_size = 0;
	text_color = CommonFunc::BLACK_COLOR;
	text_texture = NULL;
}

Text::~Text()
{
	free();
}

void Text::free()
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
	if (text_texture != NULL)
	{
		SDL_DestroyTexture(text_texture);
		text_texture = NULL;
	}
}

void Text::set_up_text(const std::string& text_, const int& f_s, SDL_Color color)
{
	text_str = text_;
	font_size = f_s;
	text_color = color;
}

void Text::load_font(SDL_Renderer* renderer)
{
	font = TTF_OpenFont(FONT_FILE.c_str(), font_size);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text_str.c_str(), text_color);

	text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);
}

void Text::render(int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect renderQuad;
	TTF_SizeText(font, text_str.c_str(), &renderQuad.w, &renderQuad.h);
	renderQuad.x = x;
	renderQuad.y = y;

	SDL_RenderCopy(renderer, text_texture, NULL, &renderQuad);
}