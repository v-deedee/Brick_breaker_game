#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "CommonFunc.h"
#include "Bullet.h"

class Paddle : public CommonFunc
{
public:
	const std::string PADDLE_IMAGE_FILE = "assets/sprites/NewPaddle.png";

	const int PADDLE_WIDTH = 100;
	const int PADDLE_HEIGHT = 25;

	Paddle();
	~Paddle();
	void load_paddle_texture(SDL_Renderer* renderer);
	void render_paddle(SDL_Renderer* renderer);
	void follow_mouse();
	void set_bullet(SDL_Renderer* renderer);
	void handle_gun_event(SDL_Renderer* renderer);


	int getX() { return x; };
	int getY() { return y; };

private:
	int x, y; // paddle position
	SDL_Texture* paddle_texture;

	std::vector <Bullet> left_bullet_list;
	std::vector <Bullet> right_bullet_list;
};