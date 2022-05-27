#include "Menu.h"

Menu::Menu()
{
	background_texture = NULL;
	play_up = NULL;
	play_down = NULL;
	exit_up = NULL;
	exit_down = NULL;
	game_over_texture = NULL;
	main_menu_up = NULL;
	main_menu_down = NULL;
	win_game_texture = NULL;

	play_state = mouse_states::PLAY_BUTTON_OUT;
	exit_state = mouse_states::EXIT_BUTTON_OUT;
	main_menu_state = mouse_states::MAIN_MENU_OUT;

	is_exit = false;
	is_play = false;
	is_restart = false;
}

void Menu::free()
{
	if (background_texture != NULL) SDL_DestroyTexture(background_texture);
	if (play_up != NULL) SDL_DestroyTexture(play_up);
	if (play_down != NULL) SDL_DestroyTexture(play_down);
	if (exit_up != NULL) SDL_DestroyTexture(exit_up);
	if (exit_down != NULL) SDL_DestroyTexture(exit_down);
	if (game_over_texture != NULL) SDL_DestroyTexture(game_over_texture);
	if (main_menu_up != NULL) SDL_DestroyTexture(main_menu_up);
	if (main_menu_down != NULL) SDL_DestroyTexture(main_menu_down);
	if (win_game_texture != NULL) SDL_DestroyTexture(win_game_texture);
}

Menu::~Menu()
{
	std::cout << "Menu destructor call" << std::endl;
	free();
}

void Menu::load_menu_texture(SDL_Renderer* renderer)
{
	load_texture(renderer, "assets/sprites/Menu_game.png", background_texture);
	load_texture(renderer, "assets/sprites/Play_button_up.png", play_up);
	load_texture(renderer, "assets/sprites/Play_button_down.png", play_down);
	load_texture(renderer, "assets/sprites/Exit_button_up.png", exit_up);
	load_texture(renderer, "assets/sprites/Exit_button_down.png", exit_down);
	load_texture(renderer, "assets/sprites/Game_over.png", game_over_texture);
	load_texture(renderer, "assets/sprites/Main_menu_up.png", main_menu_up);
	load_texture(renderer, "assets/sprites/Main_menu_down.png", main_menu_down);
	load_texture(renderer, "assets/sprites/Victory_background.png", win_game_texture);
}

void Menu::get_mouse_state(SDL_Event* event, mouse_states &state, int button_x, int button_y, mouse_states in, mouse_states out, mouse_states down)
{
	state = out;
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_PumpEvents();
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < button_x)
		{
			inside = false;
		}
		else if (x >  button_x + BUTTON_WIDTH)
		{
			inside = false;
		}
		else if (y < button_y)
		{
			inside = false;
		}
		else if (y > button_y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		if (inside)
		{
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				state = in;
				break;

			case SDL_MOUSEBUTTONDOWN:
				state = down;
				break;
			}
		}
		else
		{
			state = out;
		}
	}
}

void Menu::handle_start_event(SDL_Event* events)
{
	get_mouse_state(events, play_state, BUTTON_X, PLAY_BUTTON_Y, mouse_states::PLAY_BUTTON_IN, mouse_states::PLAY_BUTTON_OUT, mouse_states::PLAY_BUTTON_DOWN);
	get_mouse_state(events, exit_state, BUTTON_X, EXIT_BUTTON_Y, mouse_states::EXIT_BUTTON_IN, mouse_states::EXIT_BUTTON_OUT, mouse_states::EXIT_BUTTON_DOWN);
}

void Menu::handle_over_event(SDL_Event* events)
{
	get_mouse_state(events, main_menu_state, BUTTON_X, MAIN_MENU_Y, mouse_states::MAIN_MENU_IN, mouse_states::MAIN_MENU_OUT, mouse_states::MAIN_MENU_DOWN);
	get_mouse_state(events, exit_state, BUTTON_X, EXIT_BUTTON_Y, mouse_states::EXIT_BUTTON_IN, mouse_states::EXIT_BUTTON_OUT, mouse_states::EXIT_BUTTON_DOWN);
}

void Menu::render_main_menu(SDL_Renderer* renderer)
{
	SDL_Rect main_menu_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect play_button_rect = { BUTTON_X, PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_Rect exit_button_rect = { BUTTON_X, EXIT_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

	SDL_RenderCopy(renderer, background_texture, NULL, &main_menu_rect);
	SDL_RenderCopy(renderer, play_up, NULL, &play_button_rect);
	SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);
	
	switch (play_state)
	{
	case mouse_states::PLAY_BUTTON_IN:
		SDL_RenderCopy(renderer, play_down, NULL, &play_button_rect);
		break;
	case mouse_states::PLAY_BUTTON_OUT:
		SDL_RenderCopy(renderer, play_up, NULL, &play_button_rect);
		break;
	case mouse_states::PLAY_BUTTON_DOWN:
		is_play = true;
		break;
	}

	switch (exit_state)
	{
	case mouse_states::EXIT_BUTTON_IN:
		SDL_RenderCopy(renderer, exit_down, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_OUT:
		SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_DOWN:
		is_exit = true;
		break;
	}
}

void Menu::render_game_over_menu(SDL_Renderer* renderer)
{
	SDL_Rect game_over_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect main_menu_rect = { BUTTON_X, MAIN_MENU_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_Rect exit_button_rect = { BUTTON_X, EXIT_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

	SDL_RenderCopy(renderer, game_over_texture, NULL, &game_over_rect);
	SDL_RenderCopy(renderer, main_menu_up, NULL, &main_menu_rect);
	SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);

	switch (main_menu_state)
	{
	case mouse_states::MAIN_MENU_IN:
		SDL_RenderCopy(renderer, main_menu_down, NULL, &main_menu_rect);
		break;
	case mouse_states::MAIN_MENU_OUT:
		SDL_RenderCopy(renderer, main_menu_up, NULL, &main_menu_rect);
		break;
	case mouse_states::MAIN_MENU_DOWN:
		is_restart = true;
		break;
	}

	switch (exit_state)
	{
	case mouse_states::EXIT_BUTTON_IN:
		SDL_RenderCopy(renderer, exit_down, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_OUT:
		SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_DOWN:
		is_exit = true;
		break;
	}
}

void Menu::render_win_game_menu(SDL_Renderer* renderer)
{
	SDL_Rect win_game_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect main_menu_rect = { BUTTON_X, MAIN_MENU_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_Rect exit_button_rect = { BUTTON_X, EXIT_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

	SDL_RenderCopy(renderer, win_game_texture, NULL, &win_game_rect);
	SDL_RenderCopy(renderer, main_menu_up, NULL, &main_menu_rect);
	SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);

	switch (main_menu_state)
	{
	case mouse_states::MAIN_MENU_IN:
		SDL_RenderCopy(renderer, main_menu_down, NULL, &main_menu_rect);
		break;
	case mouse_states::MAIN_MENU_OUT:
		SDL_RenderCopy(renderer, main_menu_up, NULL, &main_menu_rect);
		break;
	case mouse_states::MAIN_MENU_DOWN:
		is_restart = true;
		break;
	}

	switch (exit_state)
	{
	case mouse_states::EXIT_BUTTON_IN:
		SDL_RenderCopy(renderer, exit_down, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_OUT:
		SDL_RenderCopy(renderer, exit_up, NULL, &exit_button_rect);
		break;
	case mouse_states::EXIT_BUTTON_DOWN:
		is_exit = true;
		break;
	}
}