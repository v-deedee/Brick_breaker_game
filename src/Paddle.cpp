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
	SDL_Surface* loadedSurface = IMG_Load(PADDLE_IMAGE_FILE.c_str());
	if (loadedSurface == NULL)
	{
		logIMGError(std::cout, "Class Paddle - IMG_Load", true);
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
		paddle_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (paddle_texture == NULL)
		{
			logSDLError(std::cout, "Class Paddle - SDL_CreateTextureFromSurface", true);
		}
	}
}

void Paddle::render_paddle(SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { x, y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_RenderCopy(renderer, paddle_texture, NULL, &renderQuad);
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