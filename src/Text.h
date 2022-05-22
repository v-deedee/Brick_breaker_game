#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "CommonFunc.h"

class Text : public CommonFunc
{
public:
	const std::string FONT_FILE = "assets/font/VeraMoBd.ttf";

	Text();
	~Text();
	void free();
	void set_up_text(const std::string& text_, const int& f_s, SDL_Color color);
	void load_font(SDL_Renderer* renderer);
	void render(int x, int y, SDL_Renderer* renderer);

private:
	TTF_Font* font;
	SDL_Texture* text_texture;
	std::string text_str;
	int font_size;
	SDL_Color text_color;
};