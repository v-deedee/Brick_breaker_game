#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <cmath>
#include "CommonFunc.h"

class Ball : public CommonFunc
{
public:
	const std::string BALL_IMAGE_FILE = "assets/sprites/NewBall.png";

	const int BALL_SPEED = 5;

	const int BALL_WIDTH = 20;
	const int BALL_HEIGHT = 20;

	Ball();
	~Ball();

	void set_start_position(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height);
	void load_ball_texture(SDL_Renderer* renderer);
	void render_ball(SDL_Renderer* renderer);
	void set_ball(SDL_Event& events, bool& is_set_start_pos);
	void move(bool &is_set_start_pos, bool &lose_lives_check, Mix_Chunk* ball_impact_sound);
	void set_paddle_collision(const int& paddle_x, const int& paddle_y, const int& paddle_width, const int& paddle_height,
								const bool& is_set_start_pos, Mix_Chunk* ball_impact_sound);
	void set_brick_collision(SDL_Renderer* renderer, const int& brick_x, const int& brick_y, const int& brick_width, const int& brick_height,
							int &brick_matrix, int &score, Mix_Chunk* ball_impact_sound);

	bool get_button_event() { return button_event; };
	void set_button_event(const bool& value) { button_event = value; };

private:
	SDL_Texture* ball_texture;

	double x, y; // ball position
	double speed_x, speed_y; // speed of the ball

	bool button_event; // to check mouse event
};