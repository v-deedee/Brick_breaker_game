#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "CommonFunc.h"
#include "Ball.h"
#include "Paddle.h"
#include "Level.h"
#include "PlayerLives.h"
#include "Text.h"
#include "Menu.h"

class MainControl : public CommonFunc
{
public:
	MainControl();
	~MainControl();

	void initializeSDL();
	void update_game(bool& is_set_start_pos, bool& lose_lives_check, int& die_number, bool& is_running, const std::string& l_text, const int& score, bool& game_over);
	void check_collision(int& score);
	void load_game();
	void set_main_menu(bool& is_running, SDL_Event* events, bool& is_exit);
	void set_game_over_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score);
	void set_win_game_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score);
	void run();
	void close();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ball* ball;
	Paddle* paddle;
	Level* level;
	PlayerLives* player_lives;
	Mix_Chunk* ball_impact_sound[2];
	Text* level_text;
	Text* score_text;
	Menu* menu;
};