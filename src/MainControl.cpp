#include "MainControl.h"

MainControl::MainControl()
{
	window = NULL;
	renderer = NULL;
	ball = new Ball();
	paddle = new Paddle();
	level = new Level();
	player_lives = new PlayerLives();
	ball_impact_sound[0] = NULL;
	ball_impact_sound[1] = NULL;
	level_text = new Text();
	score_text = new Text();
	menu = new Menu();
}

MainControl::~MainControl()
{
	
}

void MainControl::initializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		logSDLError(std::cout, "SDL_Init", true);
	}

	window = SDL_CreateWindow("Brick game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		logSDLError(std::cout, "SDL_CreateWindow", true);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		logSDLError(std::cout, "SDL_CreateRenderer", true);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		logIMGError(std::cout, "IMG_Init", true);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		logMixError(std::cout, "Mix_OpenAudio", true);
	}

	if (TTF_Init() < 0)
	{
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		TTF_Quit();
		exit(1);
	}
}

void MainControl::update_game(bool &is_set_start_pos, bool &lose_lives_check, int &die_number, bool &is_running, const std::string& l_text, const int& score, bool& game_over)
{
	level_text->free();
	score_text->free();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// render play ground
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect play_ground = { (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2, (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2, PLAY_GROUND_WIDTH, PLAY_GROUND_HEIGHT };
	SDL_RenderDrawRect(renderer, &play_ground);

	paddle->follow_mouse();
	paddle->render_paddle(renderer);

	player_lives->render(renderer);

	ball->render_ball(renderer);

	level_text->set_up_text(l_text, 30, WHITE_COLOR);
	level_text->load_font(renderer);
	level_text->render(10, 10, renderer);

	std::string sc_text = "SCORE:";
	std::string sc_value = std::to_string(score);
	sc_text += sc_value;
	score_text->set_up_text(sc_text, 25, WHITE_COLOR);
	score_text->load_font(renderer);
	score_text->render(10, 655, renderer);

	if (is_set_start_pos)
	{
		ball->set_start_position(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	}

	ball->move(is_set_start_pos, lose_lives_check, ball_impact_sound[0]);

	if (lose_lives_check)
	{
		die_number++;
		if (die_number <= 2)
		{
			player_lives->decrease();
			lose_lives_check = false;
		}
		else
		{
			game_over = true;
		}
	}

	ball->set_paddle_collision(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT, is_set_start_pos, ball_impact_sound[0]);

	
}

void MainControl::check_collision(int& score)
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLS; j++)
		{
			if (level->get_brick_matrix(i, j) > 0)
			{
				int val = level->get_brick_matrix(i, j);
				ball->set_brick_collision(renderer, level->get_brick(i, j).x, level->get_brick(i, j).y, level->BRICK_WIDTH, level->BRICK_HEIGHT,
											val, score, ball_impact_sound[1]);
				level->set_brick_matrix(i, j, val);
			}
		}
	}
}

void MainControl::load_game()
{
	ball->load_ball_texture(renderer);
	paddle->load_paddle_texture(renderer);
	player_lives->load(renderer);
	ball_impact_sound[0] = Mix_LoadWAV("assets/audio/Ball_hit_paddle.wav");
	ball_impact_sound[1] = Mix_LoadWAV("assets/audio/Ball_hit_brick.wav");
	if (ball_impact_sound[0] == NULL || ball_impact_sound[1] == NULL)
	{
		logMixError(std::cout, "Mix_LoadWAV", true);
	}
	level->load_brick_texture(renderer);
	menu->load_menu_texture(renderer);
	//paddle->set_bullet(renderer);
}

void MainControl::set_main_menu(bool& is_running, SDL_Event* events, bool& is_exit)
{
	
	while (is_running)
	{
		while (SDL_PollEvent(events) != 0)
		{
			if (events->type == SDL_QUIT)
			{
				is_running = false;
			}
			menu->handle_start_event(events);
		}
		
		menu->render_main_menu(renderer);
		SDL_RenderPresent(renderer);

		if (menu->get_is_exit())
		{
			is_exit = true;
			break;
		}
		if (menu->get_is_play())
		{
			break;
		}
	}
}

void MainControl::set_game_over_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score)
{
	
	while (is_running)
	{
		while (SDL_PollEvent(events) != 0)
		{
			if (events->type == SDL_QUIT)
			{
				is_running = false;
			}
			menu->handle_over_event(events);
		}
		menu->render_game_over_menu(renderer);

		if (menu->get_is_exit())
		{
			is_exit = true;
			return;
		}
		if (menu->get_is_restart())
		{
			is_restart = true;
			break;
		}

		std::string sc_text = "YOUR SCORE:";
		std::string sc_value = std::to_string(score);
		sc_text += sc_value;
		score_text->set_up_text(sc_text, 30, LIME_COLOR);
		score_text->load_font(renderer);
		score_text->render(100, 350, renderer);
		
		SDL_RenderPresent(renderer);
		score_text->free();
	}
}

void MainControl::set_win_game_menu(bool& is_running, SDL_Event* events, bool& is_restart, bool& is_exit, const int& score)
{
	
	while (is_running)
	{
		
		while (SDL_PollEvent(events) != 0)
		{
			if (events->type == SDL_QUIT)
			{
				is_running = false;
			}
			menu->handle_over_event(events);
		}
		menu->render_win_game_menu(renderer);

		if (menu->get_is_exit())
		{
			is_exit = true;
			return;
		}
		if (menu->get_is_restart())
		{
			is_restart = true;
			break;
		}
		

		std::string sc_text = "YOUR SCORE:";
		std::string sc_value = std::to_string(score);
		sc_text += sc_value;
		score_text->set_up_text(sc_text, 30, LIME_COLOR);
		score_text->load_font(renderer);
		score_text->render(100, 350, renderer);

		SDL_RenderPresent(renderer);
		score_text->free();
	}
}

bool first_load_game = true;

void MainControl::run()
{
	bool is_running = true;
	SDL_Event events;

	bool is_set_start_pos = true;
	bool level_over[4] = { 0, 0, 0, 0 };

	int score = 0;

	int die_number = 0;
	bool lose_lives_check = false;

	bool first_load_level = true;
	
	bool is_restart = true;
	bool game_over = false;
	bool is_exit = false;
	bool win_game = false;

	player_lives->init();

	if (first_load_game)
	{
		load_game();
		first_load_game = false;
	}

	if (is_restart)
	{
		menu->set_is_play(false);
		menu->set_is_exit(false);
		menu->set_is_start(false);
		menu->set_play_state(mouse_states::PLAY_BUTTON_OUT);

		level->set_first_load_level(true);

		set_main_menu(is_running, &events, is_exit);
		is_restart = false;
	}

	if (is_exit) return;

	while (is_running)
	{
		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				is_running = false;
			}
			ball->set_ball(events, is_set_start_pos);
		}
		paddle->handle_gun_event(renderer);
		// lEVEL 1
		if (!level_over[0])
		{
			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 1", score, game_over);

			level->set_up_level_1(renderer);
			check_collision(score);
			if (level->get_level_cleared()) level_over[0] = true;
		}

		// LEVEL2
		if (level_over[0] && !level_over[1])
		{
			level_over[0] = true;

			if (first_load_level)
			{
				is_set_start_pos = true;
				ball->set_button_event(true);
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 2", score, game_over);

			level->set_up_level_2(renderer);
			check_collision(score);

			if (level->get_level_cleared())
			{
				level_over[1] = true;
				first_load_level = true;
			}
		}

		// LEVEL 3
		if (level_over[1] && !level_over[2])
		{
			level_over[1] = true;

			if (first_load_level)
			{
				is_set_start_pos = true;
				ball->set_button_event(true);
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 3", score, game_over);

			level->set_up_level_3(renderer);
			check_collision(score);

			if (level->get_level_cleared())
			{
				level_over[2] = true;
				first_load_level = true;
			}
		}

		// LEVEL 4
		if (level_over[2] && !level_over[3])
		{
			level_over[2] = true;

			if (first_load_level)
			{
				is_set_start_pos = true;
				ball->set_button_event(true);
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 4", score, game_over);

			level->set_up_level_4(renderer);
			check_collision(score);

			if (level->get_level_cleared())
			{
				level_over[3] = true;
				win_game = true;
			}
		}

		SDL_RenderPresent(renderer);
		if (game_over) break;
		if (win_game) break;
	}

	if (game_over)
	{
		game_over = false;
		menu->set_main_menu_state(mouse_states::MAIN_MENU_OUT);
		set_game_over_menu(is_running, &events, is_restart, is_exit, score);
		
		if (is_restart) run();
		return;
	}

	if (win_game)
	{
		win_game = false;
		menu->set_main_menu_state(mouse_states::MAIN_MENU_OUT);
		set_win_game_menu(is_running, &events, is_restart, is_exit, score);
		ball->set_button_event(true);

		if (is_restart) run();
		return;
	}
}

void MainControl::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL; renderer = NULL;
	delete ball;
	delete paddle;
	delete level;
	delete player_lives;

	Mix_FreeChunk(ball_impact_sound[0]);
	Mix_FreeChunk(ball_impact_sound[1]);

	delete level_text;
	delete score_text;
	delete menu;

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}