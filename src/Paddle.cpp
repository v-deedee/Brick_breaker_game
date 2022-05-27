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
	Bullet left_bullet;
	Bullet right_bullet;
	left_bullet.set_x(x + 20);
	left_bullet.set_y(y - left_bullet.BULLET_HEIGHT);

	right_bullet.set_x(x + PADDLE_WIDTH - 20);
	right_bullet.set_y(y - right_bullet.BULLET_HEIGHT);

	left_bullet.load_bullet_texture(renderer);
	right_bullet.load_bullet_texture(renderer);

	for (int i = 0; i < 10; i++)
	{
		left_bullet_list.push_back(left_bullet);
		right_bullet_list.push_back(right_bullet);
	}
}

void Paddle::handle_gun_event(SDL_Renderer* renderer)
{
	// if event happened
	{
		Bullet left_bullet;
		Bullet right_bullet;
		left_bullet.set_x(x + 20);
		left_bullet.set_y(y - left_bullet.BULLET_HEIGHT);

		right_bullet.set_x(x + PADDLE_WIDTH - 20);
		right_bullet.set_y(y - right_bullet.BULLET_HEIGHT);

		left_bullet.load_bullet_texture(renderer);
		right_bullet.load_bullet_texture(renderer);

		left_bullet.render(renderer);
		//left_bullet.move();

		right_bullet.render(renderer);
		//right_bullet.move();
	}
}