#pragma once
#include "CommonFunc.h"

enum class mouse_states
{
	PLAY_BUTTON_IN, PLAY_BUTTON_OUT, PLAY_BUTTON_DOWN,
	EXIT_BUTTON_IN, EXIT_BUTTON_OUT, EXIT_BUTTON_DOWN,
	MAIN_MENU_IN, MAIN_MENU_OUT, MAIN_MENU_DOWN
};

class Menu : public CommonFunc
{
public:
	const int BUTTON_WIDTH = 150;
	const int BUTTON_HEIGHT = 75;

	const int BUTTON_X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;

	const int PLAY_BUTTON_Y = 450;
	const int EXIT_BUTTON_Y = 450 + BUTTON_HEIGHT + 20;
	const int MAIN_MENU_Y = 450;

	Menu();
	~Menu();

	void load_menu_texture(SDL_Renderer* renderer);
	void get_mouse_state(SDL_Event* event, mouse_states& state, int x, int y, mouse_states in, mouse_states out, mouse_states down);
	void handle_start_event(SDL_Event* events);
	void handle_over_event(SDL_Event* events);
	void render_main_menu(SDL_Renderer* renderer);
	void render_game_over_menu(SDL_Renderer* renderer);
	void render_win_game_menu(SDL_Renderer* renderer);

	bool get_is_exit() { return is_exit; };
	bool get_is_play() { return is_play; };
	bool get_is_restart() { return is_restart; };
	void set_is_play(const bool& value) { is_play = value; };
	void set_is_exit(const bool& value) { is_exit = value; };
	void set_is_start(const bool& value) { is_restart = value; };
	void set_play_state(const mouse_states& value) { play_state = value; };
	void set_main_menu_state(const mouse_states& value) { main_menu_state = value; };

private:
	SDL_Texture* background_texture;
	SDL_Texture* play_up;
	SDL_Texture* play_down;
	SDL_Texture* exit_up;
	SDL_Texture* exit_down;
	SDL_Texture* game_over_texture;
	SDL_Texture* main_menu_up;
	SDL_Texture* main_menu_down;
	SDL_Texture* win_game_texture;

	mouse_states play_state;
	mouse_states exit_state;
	mouse_states main_menu_state;

	bool is_exit;
	bool is_play;
	bool is_restart;
};