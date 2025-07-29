// ***************************************************************************
// game
// ***************************************************************************

#include "game.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------

// definition of global variable that will be accessed from a different file
struct game_t current_game = {
	.current_gamemode = 0,
};

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline)) void game_options(void)
{
	Select_Game(0 /* player count determined by gamemode */, NO_OF_GAMEMODES /* max_options */);
	current_game.current_gamemode = (enum gamemode)Vec_Num_Game;
}

// ---------------------------------------------------------------------------

// main game loop, this is where the action happens
void game_play(void)
{
	int returncode = 1;
	while (returncode == 1)
	{
		battle_init();
		battle_play();
		returncode = battle_show_winner_screen();
	}
}

// ---------------------------------------------------------------------------

int game(void)
{
	game_options();

	if (button_1_4_held())
	{
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
