#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CommonFunc.h"

const int BRICK_ROWS = 10;
const int BRICK_COLS = 8;

class Level : public CommonFunc
{
public:

	const int BRICK_WIDTH = 45;
	const int BRICK_HEIGHT = 20;

	Level();
	~Level();

	void load_brick_texture(SDL_Renderer* renderer);
	void set_brick_wall();
	void render_brick_wall(SDL_Renderer* renderer);
	void set_up_level_1(SDL_Renderer* renderer);
	void set_up_level_2(SDL_Renderer* renderer);
	void set_up_level_3(SDL_Renderer* renderer);
	void set_up_level_4(SDL_Renderer* renderer);
	void set_up_level_5(SDL_Renderer* renderer);
	void set_up_level_6(SDL_Renderer* renderer);
	void set_up_level_7(SDL_Renderer* renderer);
	void set_up_level_8(SDL_Renderer* renderer);

	SDL_Rect get_brick(const int& i, const int& j) { return brick.at(i*BRICK_COLS + j); };
	double get_brick_matrix(const int& i, const int& j) { return brick_matrix.at(i*BRICK_COLS + j); };
	void set_brick_matrix(const int& i, const int& j, const double& val) { brick_matrix.at(i*BRICK_COLS + j) = val; };
	bool get_level_cleared() { return level_cleared; };
	void set_first_load_level(const bool& value) { first_load_level = value; };

private:
	std::vector <SDL_Rect> brick;
	std::vector <double> brick_matrix;
	SDL_Texture* r_brick;
	SDL_Texture* y_brick;
	SDL_Texture* g_brick;
	SDL_Texture* p_brick;
	bool level_cleared;
	bool first_load_level;
};