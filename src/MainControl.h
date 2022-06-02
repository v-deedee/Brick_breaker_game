#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "CommonFunc.h"
#include "Ball.h"
#include "Paddle.h"
#include "Level.h"
#include "PlayerLives.h"
#include "Text.h"
#include "Menu.h"
#include "Items.h"

class MainControl : public CommonFunc
{
public:
	MainControl();
	~MainControl();

	void initializeSDL();
	void update_game(bool& is_set_start_pos, bool& lose_lives_check, int& die_number, bool& is_running,
					const std::string& l_text, bool& game_over, bool& items_appearing, int& score, int& destroyed_bricks, int& item_index);
	void check_collision(Ball* ball, int& score, int& destroyed_bricks);
	void load_game(int& high_score);
	void set_main_menu(bool& is_running, SDL_Event* events, bool& is_exit);
	void set_game_over_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score);
	void set_win_game_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score);
	void handle_multi_ball_event(bool &is_set_start_pos, bool& lose_lives_check, const bool& is_activated, int& score, int& destroyed_bricks);
	void set_up_multi_ball_event();
	void stop_multi_ball_event();
	void set_time(const Uint32& current_time, Uint32& base_time, bool& is_set_start_pos);
	void run();
	void close();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ball event_balls[3];
	Ball* main_ball;
	Paddle* paddle;
	Level* level;
	PlayerLives* player_lives;
	Mix_Chunk* ball_impact_sound[2];
	Mix_Chunk* gun_sound;
	Mix_Chunk* multi_ball_sound;
	Mix_Chunk* game_over_sound;
	Mix_Chunk* win_game_sound;
	Text* level_text;
	Text* score_text;
	Text* time_text;
	Menu* menu;
	GunItems* gun_items;
	MultiItems* multi_items;
	LongItems* long_items;
	ShortItems* short_items;
	SpeedUpItems* speed_up_items;

	int high_score;
	bool first_set_up = true;
};