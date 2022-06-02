#include "Paddle.h"

Paddle::Paddle()
{
	x = (PLAY_GROUND_WIDTH + (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2 - PADDLE_WIDTH) / 2;
	y = PLAY_GROUND_HEIGHT + (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2 - PADDLE_HEIGHT - 5;
	paddle_texture = NULL;
}

Paddle::~Paddle()
{
	SDL_DestroyTexture(paddle_texture);
	paddle_texture = NULL;
}

void Paddle::load_paddle_texture(SDL_Renderer* renderer)
{
	load_texture(renderer, PADDLE_IMAGE_FILE, paddle_texture);
}

void Paddle::render_paddle(SDL_Renderer* renderer)
{
	SDL_Rect paddle_rect = { x, y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderCopy(renderer, paddle_texture, NULL, &paddle_rect);
}

void Paddle::follow_mouse()
{
	int dx, dy;
	Uint32 buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.
	buttons = SDL_GetMouseState(&dx, &dy);
	x = dx - PADDLE_WIDTH / 2;
	if (x < (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2) x = (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2;
	if (x + PADDLE_WIDTH > PLAY_GROUND_WIDTH + (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2) x = PLAY_GROUND_WIDTH - PADDLE_WIDTH + (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2;
}

void Paddle::set_bullet(SDL_Renderer* renderer)
{
	left_bullet.set_x(x + 20);
	left_bullet.set_y(y - left_bullet.BULLET_HEIGHT);	

	right_bullet.set_x(x + PADDLE_WIDTH - 20);
	right_bullet.set_y(y - right_bullet.BULLET_HEIGHT);

	left_bullet.load_bullet_texture(renderer);
	right_bullet.load_bullet_texture(renderer);
}

void Paddle::set_gun()
{
	free_bullet_list();

	left_bullet_list.reserve(100);
	right_bullet_list.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		left_bullet_list.push_back(left_bullet);
		right_bullet_list.push_back(right_bullet);
	}
}

void Paddle::handle_gun_event(SDL_Renderer* renderer, const bool& is_activated, Mix_Chunk* gun_sound)
{
	if (is_activated)
	{
		if (left_bullet_list.at(0).get_is_move())
		{
			left_bullet_list.at(0).set_left_start_pos(x, y);
			left_bullet_list.at(0).render(renderer, gun_sound);
			left_bullet_list.at(0).move();
		}
		if (right_bullet_list.at(0).get_is_move())
		{
			right_bullet_list.at(0).set_right_start_pos(x, y, PADDLE_WIDTH);
			right_bullet_list.at(0).render(renderer, gun_sound);
			right_bullet_list.at(0).move();
		}

		for (int i = 1; i < 100; i++)
		{
			if (left_bullet_list.at(i-1).get_y() < y - left_bullet.BULLET_HEIGHT - 50)
			{
				if (left_bullet_list.at(i).get_is_move())
				{
					left_bullet_list.at(i).set_left_start_pos(x, y);
					left_bullet_list.at(i).render(renderer, gun_sound);
					left_bullet_list.at(i).move();
				}
				if (right_bullet_list.at(i).get_is_move())
				{
					right_bullet_list.at(i).set_right_start_pos(x, y, PADDLE_WIDTH);
					right_bullet_list.at(i).render(renderer, gun_sound);
					right_bullet_list.at(i).move();
				}
			}
		}
	}
}

void Paddle::set_brick_collision(const int& brick_x, const int& brick_y, const int& brick_width, const int& brick_height,
								double &brick_matrix, int &score, Mix_Chunk* ball_impact_sound, int& destroyed_bricks)
{
	for (int i = 0; i < 100; i++)
	{
		int l_x = left_bullet_list.at(i).get_x();
		int l_y = left_bullet_list.at(i).get_y();
		int r_x = right_bullet_list.at(i).get_x();
		int r_y = right_bullet_list.at(i).get_y();
		int bullet_width = left_bullet.BULLET_WIDTH;
		int bullet_height = left_bullet.BULLET_HEIGHT;
		SDL_Rect left_bullet_rect = {l_x, l_y, bullet_width, bullet_height};
		SDL_Rect right_bullet_rect = {r_x, r_y, bullet_width, bullet_height};
		SDL_Rect brick_rect = { brick_x, brick_y, brick_width, brick_height };

		if (SDL_HasIntersection(&left_bullet_rect, &brick_rect))
		{
			if (brick_matrix < 4.0) brick_matrix -= 0.25;
			else if (brick_matrix == 4.0) left_bullet_list.at(i).set_is_move(false);
			if (ceil(brick_matrix) == floor(brick_matrix))
			{
				score += 50;
			}
			if (brick_matrix == 0)
			{
				destroyed_bricks++;
				Mix_PlayChannel(-1, ball_impact_sound, 0);
			}
			left_bullet_list.at(i).set_is_move(false);
			left_bullet_list.at(i).set_x(x + 20);
			left_bullet_list.at(i).set_y(y - left_bullet.BULLET_HEIGHT);
			break;
		}
		if (SDL_HasIntersection(&right_bullet_rect, &brick_rect))
		{
			if (brick_matrix < 4.0) brick_matrix -= 0.25;
			else if (brick_matrix == 4.0) right_bullet_list.at(i).set_is_move(false);
			if (ceil(brick_matrix) == floor(brick_matrix))
			{
				score += 50;
			}
			if (brick_matrix == 0)
			{
				destroyed_bricks++;
				Mix_PlayChannel(-1, ball_impact_sound, 0);
			}
			right_bullet_list.at(i).set_is_move(false);
			right_bullet_list.at(i).set_x(x + PADDLE_WIDTH - 20);
			right_bullet_list.at(i).set_y(y - right_bullet.BULLET_HEIGHT);
			break;
		}
	}
}

void Paddle::free_bullet_list()
{
	left_bullet_list.clear();
	right_bullet_list.clear();
}

void Paddle::handle_long_paddle_event(const bool& long_activated, const bool& short_activated)
{
	if (long_activated && !short_activated)
	{
		PADDLE_WIDTH = 150;
	}
	if (long_activated && short_activated)
	{
		PADDLE_WIDTH = 100;
	}
	if (!long_activated && !short_activated)
	{
		PADDLE_WIDTH = 100;
	}
}

void Paddle::handle_short_paddle_event(const bool& long_activated, const bool& short_activated)
{
	if (short_activated && !long_activated)
	{
		PADDLE_WIDTH = 60;
	}
	if (long_activated && short_activated)
	{
		PADDLE_WIDTH = 100;
	}
	if (!long_activated && !short_activated)
	{
		PADDLE_WIDTH = 100;
	}
}