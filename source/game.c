// ***************************************************************************
// game
// ***************************************************************************

#include "game.h"
#include "print/print.h"
#include "utils/controller.h"
#include "utils/utils.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------

// definition of global variable that will be accessed from a different file
struct game_t current_game = {
	.current_gamemode = 0,
	.score = { 0, 0, 0, 0 },
	.players = {
		{ .is_human = 0, .health = 0, .player_id = 0 },
		{ .is_human = 0, .health = 0, .player_id = 1 },
		{ .is_human = 0, .health = 0, .player_id = 2 },
		{ .is_human = 0, .health = 0, .player_id = 3 },
	},
	.current_player = 0,
	.no_of_players = 0,
	.pause = { .is_pause = 0, .player_who_requested_pause = 255 },
};

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline)) void game_options(void)
{
	Select_Game(0 /* player count determined by gamemode */, NO_OF_GAMEMODES /* max_options */);
	current_game.current_gamemode = (enum gamemode)Vec_Num_Game;
}

// ---------------------------------------------------------------------------

void game_init(void)
{
	enable_controller_1_x();
	enable_controller_1_y();

	// player 1 (always human)
	current_game.players[0].is_human = 1;
	current_game.players[0].get_input = get_human_input;
	current_game.players[0].position.y = 40;
	current_game.players[0].position.x = -40;
	switch (current_game.current_gamemode)
	{
		case SINGLEPLAYER:
			disable_controller_2_x();
			disable_controller_2_y();
			current_game.no_of_players = 4;
			// Bot 2-4
			current_game.players[1].is_human = 0;
			current_game.players[1].get_input = get_bot_input;
			current_game.players[1].position.y = 40;
			current_game.players[1].position.x = 40;

			current_game.players[2].is_human = 0;
			current_game.players[2].get_input = get_bot_input;
			current_game.players[2].position.y = -40;
			current_game.players[2].position.x = -40;

			current_game.players[3].is_human = 0;
			current_game.players[3].get_input = get_bot_input;
			current_game.players[3].position.y = -40;
			current_game.players[3].position.x = 40;
			break;

		case MULTIPLAYER:
			enable_controller_2_x();
			enable_controller_2_y();
			current_game.no_of_players = 4;
			// human player 2, Bot 3-4
			current_game.players[1].is_human = 1;
			current_game.players[1].get_input = get_human_input;
			current_game.players[1].position.y = 40;
			current_game.players[1].position.x = 40;

			current_game.players[2].is_human = 0;
			current_game.players[2].get_input = get_bot_input;
			current_game.players[2].position.y = -40;
			current_game.players[2].position.x = -40;

			current_game.players[3].is_human = 0;
			current_game.players[3].get_input = get_bot_input;
			current_game.players[3].position.y = -40;
			current_game.players[3].position.x = 40;
			break;

		case DUELL:
			enable_controller_2_x();
			enable_controller_2_y();
			current_game.no_of_players = 2;
			// human player 2
			current_game.players[1].is_human = 1;
			current_game.players[1].get_input = get_human_input;
			current_game.players[1].position.y = 40;
			current_game.players[1].position.x = 40;

			break;

		default:
			// TODO:
			break;
	}
	current_game.current_player = 0;

	assert(current_game.current_gamemode != 0);
}

// ---------------------------------------------------------------------------
// main game loop, this is where the action happens

void game_play(void)
{
	int return_code = 0;
	// while (current_game.lives[0] + current_game.lives[1])
	while (return_code == 0 /* TODO: sth that changed dynamically if game ends */)
	{
		battle_init();
		battle_play();

		if (1 /* TODO: a player has no lives anymore OR time finished*/)
		{
			game_over(); // TODO: Evaluate the ending: Who has won? e.g. most health, most kills, etc.
		}
	}
}

// ---------------------------------------------------------------------------

void game_end(void)
{
	// TODO: Print Winner + Scoreboard + clean up ?
	return;
}

// ---------------------------------------------------------------------------

void game_over(void)
{
	// update system high score
	int score[7];
	Clear_Score(&score);
	Add_Score_a(current_game.score[current_game.current_player], &score);
	New_High_Score(&score, (void*)&Vec_High_Score);

	unsigned int delay = 150;

	do
	{
		sync();
		Intensity_5F();
		print_string(0, -64, "GAME OVER\x80");
		print_string(20, -100, "PLAYER\x80");
		print_unsigned_int(20, 40, current_game.current_player + 1);
		Print_Ships(0x69, current_game.players[current_game.current_player].health, 0xC0E2);
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
		game_end();
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
