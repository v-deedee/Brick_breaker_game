#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class CommonFunc
{
public:
	const SDL_Color CYAN_COLOR = { 0, 255, 255 };
	const SDL_Color BLUE_COLOR = { 0, 0, 255 };
	const SDL_Color ORANGE_COLOR = { 255, 165, 0 };
	const SDL_Color YELLOW_COLOR = { 255, 255, 0 };
	const SDL_Color LIME_COLOR = { 0, 255, 0 };
	const SDL_Color PURPLE_COLOR = { 128, 0, 128 };
	const SDL_Color RED_COLOR = { 255, 0, 0 };
	const SDL_Color WHITE_COLOR = { 255, 255, 255 };
	const SDL_Color BLACK_COLOR = { 0, 0, 0 };
	const SDL_Color GREEN_COLOR = { 0, 128, 0 };

	const int SCREEN_WIDTH = 450;
	const int SCREEN_HEIGHT = 700;

	const int PLAY_GROUND_WIDTH = 400;
	const int PLAY_GROUND_HEIGHT = 600;

	void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
	void logIMGError(std::ostream& os, const std::string& msg, bool fatal = false);
	void logMixError(std::ostream& os, const std::string& msg, bool fatal = false);

	void load_texture(SDL_Renderer* renderer, const std::string& path, SDL_Texture* &texture);

private:

};