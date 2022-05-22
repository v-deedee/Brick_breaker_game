#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "CommonFunc.h"

const int BRICK_ROWS = 8;
const int BRICK_COLS = 8;

class Level : public CommonFunc
{
public:
	const int LEVEL_1[BRICK_ROWS][BRICK_COLS] = { 1, 0, 0, 0, 0, 0, 0, 1,
												  0, 1, 0, 0, 0, 0, 1, 0,
												  0, 0, 1, 0, 0, 1, 0, 0,
												  0, 0, 0, 1, 1, 0, 0, 0,
												  0, 0, 0, 1, 1, 0, 0, 0,
												  0, 0, 1, 0, 0, 1, 0, 0,
												  0, 1, 0, 0, 0, 0, 1, 0,
												  1, 0, 0, 0, 0, 0, 0, 1 };

	const int LEVEL_2[BRICK_ROWS][BRICK_COLS] = { 0, 0, 1, 1, 1, 1, 0, 0,
												  0, 1, 2, 1, 1, 2, 1, 0,
												  0, 2, 0, 2, 2, 0, 2, 0,
												  0, 1, 2, 1, 1, 2, 1, 0,
												  0, 1, 1, 1, 1, 1, 1, 0,
												  0, 0, 1, 0, 0, 1, 0, 0,
												  0, 0, 1, 0, 0, 1, 0, 0,
												  0, 0, 1, 1, 1, 1, 0, 0 };

	const int LEVEL_3[BRICK_ROWS][BRICK_COLS] = { 1, 1, 1, 1, 1, 1, 1, 1,
												  1, 3, 0, 0, 0, 0, 3, 1,
												  1, 0, 2, 2, 2, 2, 0, 1,
												  1, 0, 2, 0, 0, 2, 0, 1,
												  1, 0, 2, 0, 0, 2, 0, 1,
												  1, 0, 2, 2, 2, 2, 0, 1,
												  1, 3, 0, 0, 0, 0, 3, 1,
												  1, 1, 1, 1, 1, 1, 1, 1 };

	const int LEVEL_4[BRICK_ROWS][BRICK_COLS] = { 1, 1, 0, 3, 0, 0, 2, 0,
												  1, 0, 3, 3, 3, 2, 2, 2,
												  1, 1, 0, 3, 0, 0, 2, 0,
												  0, 0, 0, 0, 0, 0, 0, 0,
												  1, 1, 0, 3, 0, 0, 2, 0,
												  1, 0, 0, 3, 3, 0, 2, 0,
												  0, 1, 0, 3, 3, 0, 2, 0,
												  1, 1, 0, 3, 0, 0, 2, 2 };

	const int BRICK_WIDTH = 45;
	const int BRICK_HEIGHT = 20;

	Level();
	~Level();

	void set_brick_wall();
	void render_brick_wall(SDL_Renderer* renderer);
	void set_up_level_1(SDL_Renderer* renderer);
	void set_up_level_2(SDL_Renderer* renderer);
	void set_up_level_3(SDL_Renderer* renderer);
	void set_up_level_4(SDL_Renderer* renderer);
	void load_brick_texture(SDL_Renderer* renderer);

	SDL_Rect get_brick(const int& i, const int& j) { return brick[i][j]; };
	int get_brick_matrix(const int& i, const int& j) { return brick_matrix[i][j]; };
	void set_brick_matrix(const int& i, const int& j, const int& val) { brick_matrix[i][j] = val; };
	bool get_level_cleared() { return level_cleared; };
	void set_is_first(const bool& value) { is_first = value; };

private:
	SDL_Rect **brick;
	int **brick_matrix;
	bool level_cleared;
	SDL_Texture* r_brick;
	SDL_Texture* y_brick;
	SDL_Texture* g_brick;
	bool is_first;
};