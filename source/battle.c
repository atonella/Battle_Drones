// ***************************************************************************
// level
// ***************************************************************************

#include "battle.h"
#include "game.h"
#include "lib/print/print.h"
#include "utils/utils.h"

#define BATTLE_WINNING_CONDITION 3
#define RETURN_TO_TITLE_SCREEN 0
#define PLAY_AGAIN 1

// ---------------------------------------------------------------------------

struct battle_t current_battle = {
	.status = BATTLE_FINISHED,
	.winner_player_id = WINNER_NOT_SET,
	.players = {
		{ .player_id = 0, .diagonally_counter = 0 },
		{ .player_id = 1, .diagonally_counter = 0 },
		{ .player_id = 2, .diagonally_counter = 0 },
		{ .player_id = 3, .diagonally_counter = 0 },
	},
	.current_player = 0,
	.no_of_players = 0,
	.pause = { .is_pause = PAUSE_OFF, .player_who_requested_pause = INVALID_PLAYER_ID },
};

// ---------------------------------------------------------------------------

void battle_init()
{
	current_battle.status = BATTLE_PLAY;
	current_battle.winner_player_id = WINNER_NOT_SET;

	// player 1 (always human)
	enable_controller_1_x();
	enable_controller_1_y();
	current_battle.players[0] = (struct player_t) {
		.death_counter = 0,
		.diagonally_counter = 0,
		.get_input = get_human_input,
		.health = PLAYER_HEALTH_DEFAULT,
		.is_human = 1,
		.kill_counter = 0,
		.player_id = 0,
		.position = { .y = ARENA_LIMIT_UP / 2, .x = ARENA_LIMIT_LEFT / 2 },
		.respawn_counter = 0,
	};
	switch (current_game.current_gamemode)
	{
		case SINGLEPLAYER:
			disable_controller_2_x();
			disable_controller_2_y();
			current_battle.no_of_players = 4;
			// bot 2
			current_battle.players[1] = (struct player_t) {
				.bot_difficulty = 4,
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_bot_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 0,
				.kill_counter = 0,
				.player_id = 1,
				.position = { .y = ARENA_LIMIT_UP / 2, .x = ARENA_LIMIT_RIGHT / 2 },
				.respawn_counter = 0,
			};
			// bot 3
			current_battle.players[2] = (struct player_t) {
				.bot_difficulty = 5,
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_bot_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 0,
				.kill_counter = 0,
				.player_id = 2,
				.position = { .y = ARENA_LIMIT_LOW / 2, .x = ARENA_LIMIT_LEFT / 2 },
				.respawn_counter = 0,
			};
			// bot 4
			current_battle.players[3] = (struct player_t) {
				.bot_difficulty = 6,
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_bot_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 0,
				.kill_counter = 0,
				.player_id = 3,
				.position = { .y = ARENA_LIMIT_LOW / 2, .x = ARENA_LIMIT_RIGHT / 2 },
				.respawn_counter = 0,
			};
			break;

		case MULTIPLAYER:
			current_battle.no_of_players = 4;
			// human player 2
			// 2nd controller does not work in PARA JVE. Works only in VIDE and on real Vectrex console
			enable_controller_2_x();
			enable_controller_2_y();
			current_battle.players[1] = (struct player_t) {
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_human_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 1,
				.kill_counter = 0,
				.player_id = 1,
				.position = { .y = ARENA_LIMIT_UP / 2, .x = ARENA_LIMIT_RIGHT / 2 },
				.respawn_counter = 0,
			};
			// bot 3
			current_battle.players[2] = (struct player_t) {
				.bot_difficulty = 6,
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_bot_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 0,
				.kill_counter = 0,
				.player_id = 2,
				.position = { .y = ARENA_LIMIT_LOW / 2, .x = ARENA_LIMIT_LEFT / 2 },
				.respawn_counter = 0,
			};
			// bot 4
			current_battle.players[3] = (struct player_t) {
				.bot_difficulty = 6,
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_bot_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 0,
				.kill_counter = 0,
				.player_id = 3,
				.position = { .y = ARENA_LIMIT_LOW / 2, .x = ARENA_LIMIT_RIGHT / 2 },
				.respawn_counter = 0,
			};
			break;

		case DUEL:
			current_battle.no_of_players = 2;
			// human player 1
			current_battle.players[0].position.y = 0;
			current_battle.players[0].position.x = ARENA_LIMIT_LEFT / 2;
			// human player 2
			enable_controller_2_x();
			enable_controller_2_y();
			current_battle.players[1] = (struct player_t) {
				.death_counter = 0,
				.diagonally_counter = 0,
				.get_input = get_human_input,
				.health = PLAYER_HEALTH_DEFAULT,
				.is_human = 1,
				.kill_counter = 0,
				.player_id = 1,
				.position = { .y = 0, .x = ARENA_LIMIT_RIGHT / 2 },
				.respawn_counter = 0,
			};
			break;

		default:
			assert(1 == 0);
			break;
	}
	current_battle.current_player = 0;
	current_battle.pause = (struct pause_t) {
		.is_pause = PAUSE_OFF,
		.player_who_requested_pause = INVALID_PLAYER_ID,
	};

	assert(current_game.current_gamemode != 0);

	// init of random number generators
	init_rng(&bot_rng, 47, 11, 42, 1);
	init_rng(&respawn_pos_rng, 92, 12, 90, 3);
}

// ---------------------------------------------------------------------------

static inline void battle_draw_arena(void)
{
	Intensity_3F(); // set medium-low brightness of the electron beam
	Reset0Ref(); // reset beam to center
	dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
	Moveto_d(0, 0); // move beam to object coordinates
	dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for drawing
	Draw_VLp(&battle_arena); // draw vector list
}

// ---------------------------------------------------------------------------

static inline void battle_draw_players(unsigned int animation_counter)
{
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		if (current_battle.players[i].respawn_counter > 0)
		{
			continue;
		}
		Intensity_5F(); // set medium brightness of the electron beam
		Reset0Ref(); // reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
		Moveto_d(current_battle.players[i].position.y, current_battle.players[i].position.x); // move beam to object coordinates
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for drawing; TODO: in future, use player.scaling_factor (POWER UP)
		// update rotors every 2 frames
		if (animation_counter < 2)
		{
			Draw_VLp(&drone_vector_list_0);
		}
		else if (animation_counter < 4)
		{
			Draw_VLp(&drone_vector_list_1);
		}
		else if (animation_counter < 6)
		{
			Draw_VLp(&drone_vector_list_2);
		}
		else
		{
			Draw_VLp(&drone_vector_list_3);
		}
	}
}

// ---------------------------------------------------------------------------

static inline void battle_draw_bullets(void)
{
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		for (unsigned int j = 0; j < MAX_BULLETS; j++)
		{
			struct bullet_t* bullet = &current_battle.players[i].bullets[j];
			if (bullet->is_active == BULLET_ACTIVE)
			{
				Intensity_7F(); // set max. brightness of the electron beam
				Reset0Ref(); // reset beam to center
				dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
				Moveto_d(bullet->position.y, bullet->position.x); // move beam to bullet coordinates
				Dot_here(); // Simple dot for bullet
			}
		}
	}
}

// ---------------------------------------------------------------------------

static inline void battle_update_players(void)
{
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		struct player_t* current_player = &current_battle.players[i];
		// if increasing the bullets, then this breaks
		if (current_player->respawn_counter > 0 && current_player->bullets[0].is_active == BULLET_INACTIVE)
		{
			continue;
		}
		current_player->get_input(current_player);
		update_player(current_player);

		if (current_player->input.pause_button && current_battle.pause.is_pause == PAUSE_OFF)
		{
			current_battle.pause.is_pause = PAUSE_ON;
			current_battle.pause.player_who_requested_pause = current_player->player_id;
		}
	}
}

// ---------------------------------------------------------------------------

static inline void battle_handle_respawn(void)
{
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		if (current_battle.players[i].respawn_counter > 0)
		{
			current_battle.players[i].respawn_counter -= 1;
			if (current_battle.players[i].respawn_counter == 0)
			{
				unsigned int is_collision;
				do
				{
					is_collision = 0;
					current_battle.players[i].position.x = ((int)(rand(&respawn_pos_rng) & 0b01111111)) - 50;
					current_battle.players[i].position.y = ((int)(rand(&respawn_pos_rng) & 0b01111111)) - 75;
					for (unsigned int j = 0; j < current_battle.no_of_players; j++)
					{
						if (i == j)
							continue;
						is_collision |= (unsigned)check_for_drone_collision(&current_battle.players[i], &current_battle.players[j]);
					}
				} while (is_collision);
			}
		}
	}
}

// ---------------------------------------------------------------------------

static inline void battle_handle_pause(struct player_stats_t* player_stats, unsigned int* stats_collected)
{
	print_string(118, -110, "--- GAME PAUSED ---\x80");
	struct player_t* current_player = &current_battle.players[current_battle.pause.player_who_requested_pause];
	current_player->get_input(current_player);

	if (current_player->input.pause_button)
	{
		// continue the battle
		current_battle.pause.is_pause = PAUSE_OFF;
		current_battle.pause.player_who_requested_pause = INVALID_PLAYER_ID;
		*stats_collected = 0;
		// Bugfix #65: Update the buttons, before getting the input of the same player
		// in the following loop (would lead otherwise to new pause request).
		// Alternative (if this leads to unexpected behavior): cooldown of pause button
		check_buttons();
	}
	else
	{
		// collect stats only once when entering pause mode
		if (*stats_collected == 0)
		{
			collect_player_stats(player_stats);
			*stats_collected = 1;
		}
		display_player_stats(player_stats);
	}
}

// ---------------------------------------------------------------------------

static inline void battle_check_win_condition(void)
{
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		if (current_battle.players[i].kill_counter >= BATTLE_WINNING_CONDITION)
		{
			current_battle.status = BATTLE_FINISHED;
			if (current_battle.winner_player_id == WINNER_NOT_SET)
			{
				current_battle.winner_player_id = current_battle.players[i].player_id;
			}
			// exit early because there is a winner
			return;
		}
	}
}

// ---------------------------------------------------------------------------

void battle_play(void)
{
	// some variable declarations
	unsigned int animation_counter = 0;
	struct player_stats_t player_stats[current_battle.no_of_players];
	unsigned int stats_collected = 0;
#if DEBUG_ENABLED
	unsigned int frames = 0;
	unsigned int seconds = 0;
	char time_elapsed[4] = "00\x80";
#endif

	while (current_battle.status == BATTLE_PLAY)
	{
		// game loop header start - do not change
		DP_to_C8();
		Explosion_Snd(current_explosion);
		Init_Music_chk(current_music);
		Wait_Recal();
		Do_Sound();
		Intensity_5F();
		// Bugfix #67: read controller state once per frame
		check_buttons();
		check_joysticks();
		// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FRAME START vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

		battle_draw_arena();
		battle_draw_players(animation_counter);
		battle_draw_bullets();

#if DEBUG_ENABLED
		Reset0Ref();
		Print_Str_d(70, -120, (void*)"RUNNING\x80");
#endif

		if (current_battle.pause.is_pause == PAUSE_ON)
		{
			battle_handle_pause(player_stats, &stats_collected);
		}
		else
		{
			battle_update_players();
			battle_handle_respawn();
			battle_check_win_condition();

			animation_counter = (animation_counter + 1) & 7; // animation counter increase, range: 0..7
		}

#if DEBUG_ENABLED
		// Display the kill counter of Player 0 for debugging
		print_unsigned_int(90, -10, current_battle.players[0].kill_counter);

		// timer
		frames++;
		if (frames >= 50)
		{
			frames = 0;
			seconds++;
			time_elapsed[0] = '0' + (seconds / 10);
			time_elapsed[1] = '0' + (seconds % 10);
		}
		Print_Str_d(120, -120, (void*)time_elapsed);
#endif
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FRAME END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	}
}

// ---------------------------------------------------------------------------

int battle_show_winner_screen(void)
{
	int returncode = 0;
	struct player_stats_t stats[current_battle.no_of_players];
	collect_player_stats(stats);
	unsigned int button_delay = 35; // wait few ticks before checking buttons, to prevent accidental inputs
	unsigned int should_exit = 0;

	while (!should_exit)
	{
		Wait_Recal();
		Intensity_5F();
		Reset0Ref(); // reset beam to center
		// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv DRAW WINNING SCREEN vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		print_string(110, -100, "BATTLE FINISHED!\x80");
		print_string(65, -112, "WINNER: PLAYER\x80");
		print_unsigned_int(65, 58, current_battle.winner_player_id + 1);

		display_player_stats(stats);

		// indicate player who won
		print_string(0 - ((int)current_battle.winner_player_id * 15), -85, "* \x80"); // without trailing whitespace nothing gets printed

		// Check for button press after delay
		if (button_delay > 0)
		{
			button_delay--;
		}
		else
		{
			// instructions
			print_string(-85, -127, "PRESS:\x80");
			print_string(-105, -110, "1 -> HOMESCREEN\x80");
			print_string(-125, -110, "4 -> PLAY AGAIN\x80");

			check_buttons();
			if (button_1_1_pressed() || button_2_1_pressed())
			{
				should_exit = 1;
				print_string(-70, -80, "RETURNING ...\x80");
				returncode = RETURN_TO_TITLE_SCREEN;
			}
			else if (button_1_4_pressed() || button_2_4_pressed())
			{
				should_exit = 1;
				print_string(-70, -80, "RESTARTING ...\x80");
				returncode = PLAY_AGAIN;
			}
		}
	}
	return returncode;
}

// ***************************************************************************
// end of file
// ***************************************************************************
