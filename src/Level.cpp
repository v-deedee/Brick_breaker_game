#include "Level.h"

Level::Level()
{
	brick = new SDL_Rect*[BRICK_ROWS];
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		brick[i] = new SDL_Rect[BRICK_COLS];
	}

	brick_matrix = new int* [BRICK_ROWS];
	for (int i = 0; i < BRICK_ROWS; i++)
		brick_matrix[i] = new int[BRICK_COLS];

	level_cleared = true;
	is_first = true;
	r_brick = NULL;
	y_brick = NULL;
	g_brick = NULL;
}

Level::~Level()
{
	for (int i = 0; i < BRICK_ROWS; i++)
		delete [] brick[i];
	delete [] brick;

	for (int i = 0; i < BRICK_ROWS; i++)
		delete[] brick_matrix[i];
	delete[] brick_matrix;

	SDL_DestroyTexture(r_brick);
	SDL_DestroyTexture(y_brick);
	SDL_DestroyTexture(g_brick);
}

void Level::load_brick_texture(SDL_Renderer* renderer)
{
	load_texture(renderer, "assets/sprites/GreenBrick.png", g_brick);
	load_texture(renderer, "assets/sprites/YellowBrick.png", y_brick);
	load_texture(renderer, "assets/sprites/RedBrick.png", r_brick);
}

void Level::set_brick_wall()
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLS; j++)
		{
			if (brick_matrix[i][j] > 0)
			{
				brick[i][j].x = (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2 + j * (BRICK_WIDTH + 5) + 2.5;
				brick[i][j].y = (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2 + i * (BRICK_HEIGHT + 5) + 2.5;
				brick[i][j].w = BRICK_WIDTH;
				brick[i][j].h = BRICK_HEIGHT;
			}
			else brick[i][j] = { 0, 0, 0, 0 };
		}
	}
}

void Level::render_brick_wall(SDL_Renderer* renderer)
{
	level_cleared = true;
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLS; j++)
		{
			if (brick_matrix[i][j] > 0)
			{
				level_cleared = false;
				if (brick_matrix[i][j] == 1)
				{
					SDL_RenderCopy(renderer, g_brick, NULL, &brick[i][j]);
				}
				else if (brick_matrix[i][j] == 2)
				{
					SDL_RenderCopy(renderer, y_brick, NULL, &brick[i][j]);
				}
				else if (brick_matrix[i][j] == 3)
				{
					SDL_RenderCopy(renderer, r_brick, NULL, &brick[i][j]);
				}
			}
		}
	}
}

void Level::set_up_level_1(SDL_Renderer* renderer)
{
	if (is_first)
	{
		for (int i = 0; i < BRICK_ROWS; i++)
		{
			for (int j = 0; j < BRICK_COLS; j++)
			{
				brick_matrix[i][j] = LEVEL_1[i][j];
			}
		}
		is_first = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) is_first = true;
}

void Level::set_up_level_2(SDL_Renderer* renderer)
{
	if (is_first)
	{
		for (int i = 0; i < BRICK_ROWS; i++)
		{
			for (int j = 0; j < BRICK_COLS; j++)
			{
				brick_matrix[i][j] = LEVEL_2[i][j];
			}
		}
		is_first = false;
	}

	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) is_first = true;
}

void Level::set_up_level_3(SDL_Renderer* renderer)
{
	if (is_first)
	{
		for (int i = 0; i < BRICK_ROWS; i++)
		{
			for (int j = 0; j < BRICK_COLS; j++)
			{
				brick_matrix[i][j] = LEVEL_3[i][j];
			}
		}
		is_first = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) is_first = true;
}

void Level::set_up_level_4(SDL_Renderer* renderer)
{
	if (is_first)
	{
		for (int i = 0; i < BRICK_ROWS; i++)
		{
			for (int j = 0; j < BRICK_COLS; j++)
			{
				brick_matrix[i][j] = LEVEL_4[i][j];
			}
		}
		is_first = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	//if (level_cleared) is_first = true;
}