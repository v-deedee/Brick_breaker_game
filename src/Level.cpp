#include "Level.h"

Level::Level()
{
	level_cleared = true;
	first_load_level = true;
	r_brick = NULL;
	y_brick = NULL;
	g_brick = NULL;
	p_brick = NULL;
}

Level::~Level()
{
	brick.clear();
	brick_matrix.clear();
	SDL_DestroyTexture(r_brick);
	SDL_DestroyTexture(y_brick);
	SDL_DestroyTexture(g_brick);
	SDL_DestroyTexture(p_brick);
}

void Level::load_brick_texture(SDL_Renderer* renderer)
{
	load_texture(renderer, "assets/sprites/GreenBrick.png", g_brick);
	load_texture(renderer, "assets/sprites/YellowBrick.png", y_brick);
	load_texture(renderer, "assets/sprites/RedBrick.png", r_brick);
	load_texture(renderer, "assets/sprites/PlatinumBrick.png", p_brick);
}

void Level::set_brick_wall()
{
	if (brick.size() > 0) brick.clear();
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLS; j++)
		{
			if (brick_matrix.at(i*BRICK_COLS + j) > 0)
			{
				SDL_Rect br;
				br.x = (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2 + j * (BRICK_WIDTH + 5) + 2.5;
				br.y = (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2 + i * (BRICK_HEIGHT + 5) + 2.5;
				br.w = BRICK_WIDTH;
				br.h = BRICK_HEIGHT;
				brick.push_back(br);
			}
			else
			{
				SDL_Rect b;
				b.x = (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2 + j * (BRICK_WIDTH + 5) + 2.5;
				b.y = (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2 + i * (BRICK_HEIGHT + 5) + 2.5;
				b.w = 0;
				b.h = 0;
				brick.push_back(b);
			}
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
			if (brick_matrix.at(i*BRICK_COLS + j) > 0 && brick_matrix.at(i*BRICK_COLS + j) <= 3.0)
			{
				level_cleared = false;
				if (brick_matrix.at(i*BRICK_COLS + j) <= 1.0 && brick_matrix.at(i*BRICK_COLS + j) <= 3.0)
				{
					SDL_RenderCopy(renderer, g_brick, NULL, &brick.at(i*BRICK_COLS + j));
				}
				else if (brick_matrix.at(i*BRICK_COLS + j) > 1.0 && brick_matrix.at(i*BRICK_COLS + j) <= 2.0)
				{
					SDL_RenderCopy(renderer, y_brick, NULL, &brick.at(i*BRICK_COLS + j));
				}
				else if (brick_matrix.at(i*BRICK_COLS + j) > 2.0 && brick_matrix.at(i*BRICK_COLS + j) <= 3.0)
				{
					SDL_RenderCopy(renderer, r_brick, NULL, &brick.at(i*BRICK_COLS + j));
				}
			}
			else if (brick_matrix.at(i*BRICK_COLS + j) > 3.0)
			{
				SDL_RenderCopy(renderer, p_brick, NULL, &brick.at(i*BRICK_COLS + j));
			}
		}
	}
}

void Level::set_up_level_1(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level1.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level1.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				double n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_2(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level2.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level2.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_3(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level3.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level3.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_4(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level4.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level4.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_5(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level5.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level5.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_6(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level6.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level6.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_7(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level7.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level7.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	if (level_cleared) first_load_level = true;
}

void Level::set_up_level_8(SDL_Renderer* renderer)
{
	if (first_load_level)
	{
		if (brick_matrix.size() > 0) brick_matrix.clear();
		std::ifstream file("assets/data/level8.txt");
		if (!file.is_open())
		{
			std::cout << "Failed to load level8.txt" << std::endl;
			exit(1);
		}
		else
		{
			while (!file.eof())
			{
				int n;
				file >> n;
				brick_matrix.push_back(n);
			}
		}
		
		first_load_level = false;
	}

	level_cleared = true;
	set_brick_wall();

	render_brick_wall(renderer);

	//if (level_cleared) first_load_level = true;
}

