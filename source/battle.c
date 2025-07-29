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

struct battle_t current_battle = {
	.status = BATTLE_FINISHED,
	.winner_player_id = WINNER_NOT_SET,
};

// ---------------------------------------------------------------------------

void battle_init()
{
	current_battle.status = BATTLE_PLAY;
	current_battle.winner_player_id = WINNER_NOT_SET;

	// player 1 (always human)
	enable_controller_1_x();
	enable_controller_1_y();
	current_game.players[0] = (struct player_t) {
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
			current_game.no_of_players = 4;
			// bot 2
			current_game.players[1] = (struct player_t) {
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
			current_game.players[2] = (struct player_t) {
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
			current_game.players[3] = (struct player_t) {
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
			current_game.no_of_players = 4;
			// human player 2
			// 2nd controller does not work in PARA JVE. Works only in VIDE and on real Vectrex console
			enable_controller_2_x();
			enable_controller_2_y();
			current_game.players[1] = (struct player_t) {
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
			current_game.players[2] = (struct player_t) {
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
			current_game.players[3] = (struct player_t) {
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
			current_game.no_of_players = 2;
			// human player 1
			current_game.players[0].position.y = 0;
			current_game.players[0].position.x = ARENA_LIMIT_LEFT / 2;
			// human player 2
			enable_controller_2_x();
			enable_controller_2_y();
			current_game.players[1] = (struct player_t) {
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
	current_game.current_player = 0;

	assert(current_game.current_gamemode != 0);

	// init of random number generators
	init_rng(&bot_rng, 47, 11, 42, 1);
	init_rng(&respawn_pos_rng, 92, 12, 90, 3);
}

// ---------------------------------------------------------------------------

void battle_play(void)
{
	/*
	1. Rendering
	2. Input
	3. Computing
	*/
	// TODO: Optimize access of players by using pointers.
	// variable declarations
	struct player_t* current_player;
#if DEBUG_ENABLED
	unsigned int frames = 0;
	unsigned int seconds = 0;
	unsigned int timer_not_exceeded = 1;
	char time_elapsed[4] = "00\x80";
	// temporary disabled
	// char debugPos[4] = "00\x80";
#endif
	unsigned int animation_counter = 0;
	while (current_battle.status == BATTLE_PLAY)
	{
		// game loop header start - do not change
		DP_to_C8();
		Explosion_Snd(current_explosion);
		Init_Music_chk(current_music);
		Wait_Recal();
		Do_Sound();
		Intensity_5F();
		// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FRAME START vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

		// print arena
		Intensity_3F(); // set medium-low brightness of the electron beam
		Reset0Ref(); // reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
		Moveto_d(0, 0); // move beam to object coordinates
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for drawing
		Draw_VLp(&battle_arena); // draw vector list

		// print player
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			if (current_game.players[i].respawn_counter > 0)
			{
				current_game.players[i].respawn_counter -= 1;
				if (current_game.players[i].respawn_counter == 0)
				{
					// spawn player on random free position
					// TODO: random number + check for collision
					unsigned int is_collision = 0;
					do
					{
						// limit pos by arena border
						// TODO: long test with final arena borders
						is_collision = 0;
						current_game.players[i].position.x = ((int)(rand(&respawn_pos_rng) & 0b01111111)) - 50; // -50 .. 77
						current_game.players[i].position.y = ((int)(rand(&respawn_pos_rng) & 0b01111111)) - 75; // -75 .. 52
						for (unsigned int j = 0; j < current_game.no_of_players; j++)
						{
							// dont check itself
							if (i == j)
								continue;
							is_collision |= (unsigned)check_for_drone_collision(&current_game.players[i], &current_game.players[j]);
						}
					} while (is_collision);
				}
				continue;
			}
			Intensity_5F(); // set medium brightness of the electron beam
			Reset0Ref(); // reset beam to center
			dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
			Moveto_d(current_game.players[i].position.y, current_game.players[i].position.x); // move beam to object coordinates
			// Moveto_d(current_game.players[i].position.y, current_game.players[i].position.y); // move beam to object coordinates
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
			else if (animation_counter < 8)
			{
				Draw_VLp(&drone_vector_list_3);
			}
			else
			{
				assert(1 == 0); // should never evaluated
			}
#if DEBUG_ENABLED
			// temporary disabled
			// debugPos[0] = (char)('0' + (current_game.players[i].position.y / 10));
			// debugPos[1] = (char)('0' + (current_game.players[i].position.y % 10));
			// Print_Str_d(30, -30, (void*)debugPos);
#endif
		}
		// draw active bullets
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			for (unsigned int j = 0; j < MAX_BULLETS; j++)
			{
				struct bullet_t* bullet = &current_game.players[i].bullets[j];
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
#if DEBUG_ENABLED
		Reset0Ref(); // reset beam to center
		Print_Str_d(70, -120, (void*)"RUNNING\x80");
#endif

		// check if the game is paused
		if (current_game.pause.is_pause)
		{
			Print_Str_d(85, 0, (void*)"PAUSE\x80");
			current_player = &current_game.players[current_game.pause.player_who_requested_pause];
			current_player->get_input(current_player);
			if (current_player->input.pause_button)
			{
				current_game.pause.is_pause = 0;
				current_game.pause.player_who_requested_pause = 255;
			}
			else
			{
				continue;
			}
		}

		// iterate over all player objects: (1) get input (2) process resulting actions (3) check for winner
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			current_player = &current_game.players[i];
			if (current_player->respawn_counter > 0 && current_player->bullets[0].is_active == BULLET_INACTIVE)
			{
				continue;
			}
			current_player->get_input(current_player);

			// move player and objectiles; includes collision detection
			update_player(current_player);

			if (current_player->input.pause_button && !current_game.pause.is_pause)
			{
				// only one player can request the pause
				current_game.pause.is_pause = 1;
				current_game.pause.player_who_requested_pause = current_player->player_id;
			}
			// check for winner
			if (current_player->kill_counter >= BATTLE_WINNING_CONDITION)
			{
				current_battle.status = BATTLE_FINISHED;
				if (current_battle.winner_player_id == WINNER_NOT_SET)
				{
					current_battle.winner_player_id = current_player->player_id;
				}
			}
#if DEBUG_ENABLED
			// Display the kill counter of Player 0 for debugging
			print_unsigned_int(90, -10, current_game.players[0].kill_counter);
#endif
		}
		// animation counter increase
		animation_counter = (animation_counter < 7) ? (animation_counter + 1) : 0;
#if DEBUG_ENABLED

		// timer
		// TODO: Better Timer
		frames++;
		if (frames >= 50)
		{
			frames = 0;
			seconds++;
			time_elapsed[0] = '0' + (seconds / 10);
			time_elapsed[1] = '0' + (seconds % 10);
			// TODO: Update time remaining on screen
		}
		Print_Str_d(120, -120, (void*)time_elapsed);

		if (seconds > 90)
		{
			timer_not_exceeded = 0;
		}
#endif
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FRAME END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	}
}

// ---------------------------------------------------------------------------

int battle_show_winner_screen(void)
{
	int returncode = 0;
	struct player_stats_t stats[current_game.no_of_players];

	// collect & calculate stats for each player
	for (unsigned int i = 0; i < current_game.no_of_players; i++)
	{
		stats[i].player_id = current_game.players[i].player_id;
		// stats[i].has_won = current_battle.winner_player_id == current_game.players[i].player_id ? 1 : 0;
		stats[i].kills = current_game.players[i].kill_counter;
		stats[i].deaths = current_game.players[i].death_counter;
	}

	unsigned int button_delay = 35; // wait few ticks before checking buttons, to prevent accidental inputs
	unsigned int should_exit = 0;

	while (!should_exit)
	{
		Wait_Recal();
		Intensity_5F();
		Reset0Ref(); // reset beam to center
		// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv DRAW WINNING SCREEN vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		print_string(110, -100, "BATTLE FINISHED!\x80"); // TODO:verify
		print_string(65, -112, "WINNER: PLAYER\x80");
		print_unsigned_int(65, 58, current_battle.winner_player_id + 1);
		print_string(20, -85, "PLAYER  K   D\x80");
		print_string(10, -85, "------ --- ---\x80");
		//                      * <- indicates winning player

		// Print stats for each player
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			int line_y = 0 - ((int)i * 15);
			// PLAYER
			print_unsigned_int(line_y, -51, stats[i].player_id + 1);
			// K
			print_unsigned_int(line_y, -6, stats[i].kills);
			// D
			print_unsigned_int(line_y, 39, stats[i].deaths);
		}
		// indicate player who won
		print_string(0 - ((int)current_battle.winner_player_id * 15), -85, "* \x80"); // without trailing whitespace nothing gets printed

		// Check for button press after delay
		if (button_delay > 0)
		{
			button_delay--;
		}
		else
		{
			// play again instruction
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
				// TODO: set inside init
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
