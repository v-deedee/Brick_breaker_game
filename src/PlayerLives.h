#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "CommonFunc.h"

class PlayerLives : public CommonFunc
{
public:
	const std::string LIVES_IMAGE_FILE = "assets/sprites/NewBall.png";
	const int lIVES_WIDTH = 20;
	const int LIVES_HEIGHT = 20;
	const int Y_POS = SCREEN_HEIGHT - LIVES_HEIGHT * 2;

	PlayerLives();
	~PlayerLives();
	void set_number(const int& num) { number = num; };
	void add_pos(const int& xpos);
	void render(SDL_Renderer* renderer);
	void init(SDL_Renderer* renderer);
	void decrease();

private:
	int number;
	std::vector<int> pos_list;
	SDL_Texture* lives_texture;

};