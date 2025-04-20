// ***************************************************************************
// game
// ***************************************************************************

#include "game.h"
#include "level.h"
#include "print/print.h"
#include "utils/controller.h"
#include "utils/utils.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------

struct game_t current_game = {
	.option_players = 0,
	.option_mode = 0,
	.lives = { 0, 0 },
	.level = { 0, 0 },
	.score = { 0, 0 },
	.player = 0,
};

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline)) void game_options(void)
{
	Select_Game(2 /* max_players */, 5 /* max_options */);
	current_game.option_players = Vec_Num_Players;
	current_game.option_mode = Vec_Num_Game;
}

// ---------------------------------------------------------------------------

void game_init(void)
{
	// activate first joystick, switch off second joystick
	enable_controller_1_x();
	enable_controller_1_y();
	disable_controller_2_x();
	disable_controller_2_y();

	// set player data
	current_game.lives[0] = 3;
	current_game.level[0] = 1;
	current_game.score[0] = 0;
	current_game.score[1] = 0;

	if (current_game.option_players == 2)
	{
		current_game.lives[1] = 3;
		current_game.level[1] = 1;
	}
	else
	{
		current_game.lives[1] = 0;
		current_game.level[1] = 0;
	}

	current_game.player = 0;
}

// ---------------------------------------------------------------------------
// main game loop, this is where the action happens

void game_play(void)
{
	while (current_game.lives[0] + current_game.lives[1])
	{
		level_init();
		level_play();

		if (current_level.status == LEVEL_WON)
		{
			++current_game.level[current_game.player];
		}
		else
		{
			if (--current_game.lives[current_game.player] == 0)
			{
				game_over();
			}

			current_game.player = (current_game.option_players - 1) - current_game.player;
		}
	}
}

// ---------------------------------------------------------------------------

void game_over(void)
{
	// update system high score
	int score[7];
	Clear_Score(&score);
	Add_Score_a(current_game.score[current_game.player], &score);
	New_High_Score(&score, (void*)&Vec_High_Score);

	unsigned int delay = 150;

	do
	{
		sync();
		Intensity_5F();
		print_string(0, -64, "GAME OVER\x80");
		print_string(20, -100, "PLAYER\x80");
		print_unsigned_int(20, 40, current_game.player + 1);
		Print_Ships(0x69, current_game.lives[current_game.player], 0xC0E2);
		check_buttons();
	} while ((--delay) && !button_1_4_pressed());
}

// ---------------------------------------------------------------------------

int game(void)
{
	game_options();

	if (button_1_4_held())
	{
		game_init();
		game_play();
		return 0; // go to option screen, repeat cycle
	}
	else
	{
		return -1; // jump to title screen
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
