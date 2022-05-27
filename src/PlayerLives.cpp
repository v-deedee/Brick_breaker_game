#include "PlayerLives.h"

PlayerLives::PlayerLives()
{
	number = 0;
	lives_texture = NULL;
}

PlayerLives::~PlayerLives()
{

}

void PlayerLives::add_pos(const int& xpos)
{
	pos_list.push_back(xpos);
}

void PlayerLives::render(SDL_Renderer* renderer)
{
	if (number == pos_list.size())
	{
		for (int i = 0; i < pos_list.size(); i++)
		{
			SDL_Rect renderQuad = { pos_list[i], Y_POS, lIVES_WIDTH, LIVES_HEIGHT };
			SDL_RenderCopy(renderer, lives_texture, NULL, &renderQuad);
		}
	}
}

void PlayerLives::load(SDL_Renderer* renderer)
{
	load_texture(renderer, LIVES_IMAGE_FILE, lives_texture);
}

void PlayerLives::init()
{
	
	number = 3;
	if (pos_list.size() > 0)
	{
		pos_list.clear();
	}

	add_pos(400);
	add_pos(370);
	add_pos(340);
}


void PlayerLives::decrease()
{
	number--;
	pos_list.pop_back();
}