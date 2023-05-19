#include "MainControl.h"

MainControl::MainControl()
{
	window = NULL;
	renderer = NULL;
	ball_impact_sound[0] = NULL;
	ball_impact_sound[1] = NULL;
	gun_sound = NULL;
	multi_ball_sound = NULL;
	game_over_sound = NULL;
	win_game_sound = NULL;

	main_ball = new Ball();
	paddle = new Paddle();
	level = new Level();
	player_lives = new PlayerLives();
	level_text = new Text();
	score_text = new Text();
	time_text = new Text();
	menu = new Menu();

	gun_items = new GunItems();
	multi_items = new MultiItems();
	long_items = new LongItems();
	short_items = new ShortItems();
	speed_up_items = new SpeedUpItems();
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

int i_, j_;
void MainControl::update_game(bool &is_set_start_pos, bool &lose_lives_check, int &die_number, bool &is_running, const std::string& l_text,
								bool& game_over, bool& items_appearing, int& score, int& destroyed_bricks, const int& item_index)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// render play ground
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect play_ground = { (SCREEN_WIDTH - PLAY_GROUND_WIDTH) / 2, (SCREEN_HEIGHT - PLAY_GROUND_HEIGHT) / 2, PLAY_GROUND_WIDTH, PLAY_GROUND_HEIGHT };
	SDL_RenderDrawRect(renderer, &play_ground);

	level_text->free();
	level_text->set_up_text(l_text, 30, WHITE_COLOR);
	level_text->load_font(renderer);
	level_text->render(10, 10, renderer);

	score_text->free();
	std::string sc_text = "SCORE:";
	std::string sc_value = std::to_string(score);
	sc_text += sc_value;
	score_text->set_up_text(sc_text, 25, WHITE_COLOR);
	score_text->load_font(renderer);
	score_text->render(10, 655, renderer);

	paddle->follow_mouse();
	paddle->render_paddle(renderer);

	if (is_set_start_pos)
	{
		main_ball->set_start_position(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	}
	if (!multi_items->get_is_activated())
	{
		bool val = speed_up_items->get_is_activated();
		main_ball->render_ball(renderer);
		main_ball->move(is_set_start_pos, lose_lives_check, ball_impact_sound[0], val);
		main_ball->handle_paddle_collision(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT,
											is_set_start_pos, ball_impact_sound[0]);
		speed_up_items->set_is_activated(val);
	}

	player_lives->render(renderer);
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

	paddle->handle_gun_event(renderer, gun_items->get_is_activated(), gun_sound);
	handle_multi_ball_event(is_set_start_pos, lose_lives_check, multi_items->get_is_activated(), score, destroyed_bricks);
	paddle->handle_long_paddle_event(long_items->get_is_activated(), short_items->get_is_activated());
	paddle->handle_short_paddle_event(long_items->get_is_activated(), short_items->get_is_activated());

	handle_items(items_appearing, item_index);
}

void MainControl::handle_items(bool& items_appearing, const int& item_index)
{
	if (items_appearing)
	{
		switch(item_index)
		{
			case 1:
			if (!gun_items->get_is_appeared() && !gun_items->get_is_activated())
			{
				gun_items->set_gun_start_pos(level->get_brick(i_, j_).x, level->get_brick(i_, j_).y);
				gun_items->set_is_appeared(true);
			}
			break;
			case 2:
			if (!multi_items->get_is_activated() && !multi_items->get_is_appeared())
			{
				multi_items->set_multi_start_pos(level->get_brick(i_, j_).x, level->get_brick(i_, j_).y);
				multi_items->set_is_appeared(true);
			}
			break;
			case 3:
			if (!long_items->get_is_activated() && !long_items->get_is_appeared())
			{
				long_items->set_long_start_pos(level->get_brick(i_, j_).x, level->get_brick(i_, j_).y);
				long_items->set_is_appeared(true);
			}
			break;
			case 4:
			if (!short_items->get_is_activated() && !short_items->get_is_appeared())
			{
				short_items->set_short_start_pos(level->get_brick(i_, j_).x, level->get_brick(i_, j_).y);
				short_items->set_is_appeared(true);
			}
			break;
			case 5:
			if (!speed_up_items->get_is_activated() && !speed_up_items->get_is_appeared())
			{
				speed_up_items->set_speed_up_start_pos(level->get_brick(i_, j_).x, level->get_brick(i_, j_).y);
				speed_up_items->set_is_appeared(true);
			}
			break;
		}
		items_appearing = false;
	}

	gun_items->render_gun_items(renderer);
	gun_items->gun_start_falling(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	multi_items->render_multi_items(renderer);
	multi_items->multi_item_start_falling(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	long_items->render_long_items(renderer);
	long_items->long_item_start_falling(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	short_items->render_short_items(renderer);
	short_items->short_item_start_falling(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
	speed_up_items->render_speed_up_items(renderer);
	speed_up_items->speed_up_item_start_falling(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT);
}

void MainControl::check_collision(Ball* ball, int& score, int& destroyed_bricks)
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLS; j++)
		{
			if (level->get_brick_matrix(i, j) > 0)
			{
				double val = level->get_brick_matrix(i, j);
				ball->handle_brick_collision(level->get_brick(i, j).x, level->get_brick(i, j).y, level->BRICK_WIDTH, level->BRICK_HEIGHT,
											val, score, ball_impact_sound[1], destroyed_bricks);
				paddle->set_brick_collision(level->get_brick(i, j).x, level->get_brick(i, j).y, level->BRICK_WIDTH, level->BRICK_HEIGHT,
											val, score, ball_impact_sound[1], destroyed_bricks);
				level->set_brick_matrix(i, j, val);
				if (ball->get_brick_collision())
				{
					i_ = i;
					j_ = j;
				}
			}
		}
	}
}

void MainControl::load_game(int& high_score)
{
	std::ifstream infile("assets/data/high_score.txt");
	if( infile.is_open() )
    {
        infile >> high_score;
    }
    else
    {
        high_score = 0;
    }
	infile.close();
	paddle->load_paddle_texture(renderer);
	player_lives->load(renderer);
	ball_impact_sound[0] = Mix_LoadWAV("assets/audio/Ball_hit_paddle.wav");
	ball_impact_sound[1] = Mix_LoadWAV("assets/audio/Ball_hit_brick.wav");
	gun_sound = Mix_LoadWAV("assets/audio/Gun.wav");
	multi_ball_sound = Mix_LoadWAV("assets/audio/Multi_ball.wav");
	game_over_sound = Mix_LoadWAV("assets/audio/Game_over.wav");
	win_game_sound = Mix_LoadWAV("assets/audio/Win_game.wav");
	if (ball_impact_sound[0] == NULL || ball_impact_sound[1] == NULL || gun_sound == NULL || multi_ball_sound == NULL 
		|| game_over_sound == NULL || win_game_sound == NULL)
	{
		logMixError(std::cout, "Mix_LoadWAV", true);
	}
	level->load_brick_texture(renderer);
	menu->load_menu_texture(renderer);
	
	gun_items->load_gun_items_texture(renderer);
	multi_items->load_multi_items_texture(renderer);
	long_items->load_long_items_texture(renderer);
	short_items->load_short_items_texture(renderer);
	speed_up_items->load_speed_up_items_texture(renderer);
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
		std::string sc_text = "HIGH SCORE:";
		std::string sc_value = std::to_string(high_score);
		sc_text += sc_value;
		score_text->set_up_text(sc_text, 25, WHITE_COLOR);
		score_text->load_font(renderer);
		if (high_score == 0) score_text->render(130, 415, renderer);
		if (high_score == 50) score_text->render(126, 415, renderer);
		if (high_score >= 100 && high_score < 1000) score_text->render(122, 415, renderer);
		if (high_score >= 1000 && high_score < 10000) score_text->render(112, 415, renderer);
		if (high_score >= 10000) score_text->render(106, 415, renderer);
		
		SDL_RenderPresent(renderer);
		score_text->free();

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
	srand(time(NULL));

	bool is_running = true;
	SDL_Event events;

	bool is_set_start_pos = true;
	bool level_over[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	int score = 0;

	int die_number = 0;
	bool lose_lives_check = false;

	bool first_load_level = true;
	bool first_set_gun = true;
	
	bool is_restart = true;
	bool game_over = false;
	bool is_exit = false;
	bool win_game = false;

	bool items_appearing = false;

	int destroyed_bricks = 0;

	int item_index;

	Uint32 base_time = 0;
	Uint32 time1 = 0;
	Uint32 time2 = 0;
	Uint32 time3 = 0;
	Uint32 time4 = 0;
	Uint32 time5 = 0;
	Uint32 time6 = 0;
	Uint32 time7 = 0;
	Uint32 time8 = 0;

	player_lives->init();

	if (first_load_game)
	{
		load_game(high_score);
		first_load_game = false;
	}

	if (is_restart)
	{
		base_time = SDL_GetTicks()/1000;
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
			main_ball->set_ball(events, is_set_start_pos);
		}
		
		// LEVEL 1
		if (!level_over[0])
		{
			time1 = SDL_GetTicks()/1000;
			

			if (first_set_gun)
			{
				main_ball->load_ball_texture(renderer);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;

				first_set_gun = false;
			}
			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 1", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time1, base_time, is_set_start_pos);

			level->set_up_level_1(renderer);
			check_collision(main_ball ,score, destroyed_bricks);

			if (destroyed_bricks >= 5)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}
			
			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}
			
			if (level->get_level_cleared())
			{
				level_over[0] = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL2
		if (level_over[0] && !level_over[1])
		{
			time2 = SDL_GetTicks()/1000;

			level_over[0] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;

				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 2", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time2, time1, is_set_start_pos);

			level->set_up_level_2(renderer);
			check_collision(main_ball ,score, destroyed_bricks);

			if (destroyed_bricks >= 5)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}
			
			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[1] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 3
		if (level_over[1] && !level_over[2])
		{
			time3 = SDL_GetTicks()/1000;
			level_over[1] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;

				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 3", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time3, time2, is_set_start_pos);

			level->set_up_level_3(renderer);
			check_collision(main_ball ,score, destroyed_bricks);

			if (destroyed_bricks >= 5)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[2] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 4
		if (level_over[2] && !level_over[3])
		{
			time4 = SDL_GetTicks()/1000;
			level_over[2] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;
				
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 4", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time4, time3, is_set_start_pos);

			level->set_up_level_4(renderer);
			check_collision(main_ball, score, destroyed_bricks);

			if (destroyed_bricks >= 4)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[3] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 5
		if (level_over[3] && !level_over[4])
		{
			time5 = SDL_GetTicks()/1000;
			
			level_over[3] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;
				
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 5", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time5, time4, is_set_start_pos);

			level->set_up_level_5(renderer);
			check_collision(main_ball, score, destroyed_bricks);

			if (destroyed_bricks >= 2)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[4] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 6
		if (level_over[4] && !level_over[5])
		{
			time6 = SDL_GetTicks()/1000;

			level_over[4] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;
				
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 6", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time6, time5, is_set_start_pos);

			level->set_up_level_6(renderer);
			check_collision(main_ball, score, destroyed_bricks);

			if (destroyed_bricks >= 4)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[5] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 7
		if (level_over[5] && !level_over[6])
		{
			time7 = SDL_GetTicks()/1000;

			level_over[5] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;
				
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 7", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time7, time6, is_set_start_pos);

			level->set_up_level_7(renderer);
			check_collision(main_ball, score, destroyed_bricks);

			if (destroyed_bricks >= 4)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[6] = true;
				first_load_level = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		// LEVEL 8
		if (level_over[6] && !level_over[7])
		{
			time8 = SDL_GetTicks()/1000;

			level_over[6] = true;

			if (first_load_level)
			{
				main_ball->load_ball_texture(renderer);
				is_set_start_pos = true;
				main_ball->set_button_event(true);
				paddle->set_bullet(renderer);
				paddle->set_gun();
				first_set_up = true;
				gun_items->set_as_default();
				multi_items->set_as_default();
				long_items->set_as_default();
				short_items->set_as_default();
				speed_up_items->set_as_default();
				items_appearing = false;
				destroyed_bricks = 0;
				item_index = 0;
				
				first_load_level = false;
			}

			update_game(is_set_start_pos, lose_lives_check, die_number, is_running, "LEVEL 8", game_over,
						items_appearing, score, destroyed_bricks, item_index);
			set_time(time8, time7, is_set_start_pos);

			level->set_up_level_8(renderer);
			check_collision(main_ball, score, destroyed_bricks);

			if (destroyed_bricks >= 3)
			{
				items_appearing = true;
				item_index = rand() % 5 + 1;
				destroyed_bricks = 0;
			}

			if (main_ball->get_paddle_collision())
			{
				destroyed_bricks = 0;
			}

			if (level->get_level_cleared())
			{
				level_over[7] = true;
				win_game = true;
				paddle->free_bullet_list();
				stop_multi_ball_event();
				SDL_Delay(100);
			}
		}

		SDL_RenderPresent(renderer);
		if (game_over) break;
		if (win_game) break;
	}

	if (game_over)
	{
		Mix_PlayChannel(-1, game_over_sound, 0);
		game_over = false;
		menu->set_main_menu_state(mouse_states::MAIN_MENU_OUT);
		set_game_over_menu(is_running, &events, is_restart, is_exit, score);
		paddle->free_bullet_list();
		if (score > high_score)
		{
			high_score = score;
			std::ofstream outfile("assets/data/high_score.txt");
			if(outfile.is_open())
			{
				outfile << high_score;
			}
			outfile.close();
		}
		
		if (is_restart) run();
		return;
	}

	if (win_game)
	{
		Mix_PlayChannel(-1, win_game_sound, 0);
		win_game = false;
		menu->set_main_menu_state(mouse_states::MAIN_MENU_OUT);
		set_win_game_menu(is_running, &events, is_restart, is_exit, score);
		main_ball->set_button_event(true);
		paddle->free_bullet_list();
		if (score > high_score)
		{
			high_score = score;
			std::ofstream outfile("assets/data/high_score.txt");
			if(outfile.is_open())
			{
				outfile << high_score;
			}
			outfile.close();
		}

		if (is_restart) run();
		return;
	}
}

void MainControl::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeChunk(ball_impact_sound[0]);
	Mix_FreeChunk(ball_impact_sound[1]);
	Mix_FreeChunk(gun_sound);
	Mix_FreeChunk(multi_ball_sound);
	Mix_FreeChunk(game_over_sound);
	Mix_FreeChunk(win_game_sound);

	delete main_ball;
	delete paddle;
	delete level;
	delete player_lives;
	delete level_text;
	delete score_text;
	delete time_text;
	delete menu;

	delete gun_items;
	delete multi_items;
	delete long_items;
	delete short_items;
	delete speed_up_items;

	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}

bool is_deleted[3] = {0, 0, 0};
void MainControl::handle_multi_ball_event(bool &is_set_start_pos, bool& lose_lives_check, const bool& is_activated, int& score, int& destroyed_bricks)
{
	// if event happened
	if (is_activated)
	{
		if (first_set_up)
		{
			set_up_multi_ball_event();
			Mix_PlayChannel(-1, multi_ball_sound, 0);
			first_set_up = false;
		}

		for (int i = 0; i < 3; i++)
		{
			if (!is_deleted[i])
			{
				event_balls[i].render_ball(renderer);
				event_balls[i].event_move(ball_impact_sound[0], is_deleted[i], speed_up_items->get_is_activated());
				event_balls[i].handle_paddle_collision(paddle->getX(), paddle->getY(), paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT,
														is_set_start_pos, ball_impact_sound[0]);
				check_collision(&event_balls[i], score, destroyed_bricks);
			}
		}
		if (is_deleted[0] && is_deleted[1] && is_deleted[2])
		{
			multi_items->set_is_activated(false);
			lose_lives_check = true;
			is_set_start_pos = true;
			main_ball->set_button_event(true);
		}
	}
}

void MainControl::set_up_multi_ball_event()
{
	for (int i = 0; i < 3; i++)
	{
		event_balls[i] = *main_ball;
		is_deleted[i] = 0;
	}

	event_balls[1].set_speed_y(-main_ball->get_speed_y());
	event_balls[2].set_speed_x(-main_ball->get_speed_x());
}

void MainControl::stop_multi_ball_event()
{
	for (int i = 0; i < 3; i++)
	{
		event_balls[i].free();
	}
}

void MainControl::set_time(const Uint32& current_time, Uint32& base_time, bool& is_set_start_pos)
{
	time_text->free();
	std::string t_text = "TIME:";
	std::string t_value = std::to_string(180 - (current_time - base_time));
	t_text += t_value;
	time_text->set_up_text(t_text, 25, BLUE_COLOR);
	time_text->load_font(renderer);
	time_text->render(300, 10, renderer);
	if (current_time - base_time > 180)
	{
		is_set_start_pos = true;
		main_ball->set_button_event(true);
		base_time = current_time;
	}
}