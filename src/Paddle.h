#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "CommonFunc.h"
#include "Bullet.h"

class Paddle : public CommonFunc
{
public:
	const std::string PADDLE_IMAGE_FILE = "assets/sprites/NewPaddle.png";

	int PADDLE_WIDTH = 100;
	const int PADDLE_HEIGHT = 25;

	Paddle();
	~Paddle();
	void load_paddle_texture(SDL_Renderer* renderer);
	void render_paddle(SDL_Renderer* renderer);
	void follow_mouse();
	void set_bullet(SDL_Renderer* renderer);
	void set_gun();
	void handle_gun_event(SDL_Renderer* renderer, const bool& is_activated, Mix_Chunk* gun_sound);
	void handle_long_paddle_event(const bool& long_activated, const bool& short_activated);
	void handle_short_paddle_event(const bool& long_activated, const bool& short_activated);
	void set_brick_collision(const int& brick_x, const int& brick_y, const int& brick_width, const int& brick_height,
							double &brick_matrix, int &score, Mix_Chunk* ball_impact_sound, int& destroyed_bricks);
	void free_bullet_list();


	int getX() { return x; };
	int getY() { return y; };

private:
	int x, y; // paddle position
	SDL_Texture* paddle_texture;

	std::vector <Bullet> left_bullet_list;
	std::vector <Bullet> right_bullet_list;

	Bullet left_bullet;
	Bullet right_bullet;
};