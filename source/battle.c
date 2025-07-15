// ***************************************************************************
// level
// ***************************************************************************

#include "battle.h"
#include "game.h"
#include "utils/utils.h"

struct battle_t current_battle = {
	.status = BATTLE_FINISHED,
};

// ---------------------------------------------------------------------------

void battle_init()
{
	// Generate Arena, set stats, spawn player, countdown, ...
	current_battle.status = BATTLE_PLAY;
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

	while (current_battle.status == BATTLE_PLAY)
	{
		// game loop header start - do not change
		DP_to_C8();
		Explosion_Snd(current_explosion);
		Init_Music_chk(current_music);
		Wait_Recal();
		Do_Sound();
		Intensity_5F();
		// game loop header end
		// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FRAME START vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

		// print arena
		Intensity_3F(); // set medium-low brightness of the electron beam
		Reset0Ref(); // reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
		Moveto_d(0, 0); // move beam to object coordinates
		dp_VIA_t1_cnt_lo = 138; // set scaling factor for drawing
		Draw_VLp(&battle_arena); // draw vector list
		// print arena end

		// print player
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			Intensity_5F(); // set medium brightness of the electron beam
			Reset0Ref(); // reset beam to center
			dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
			Moveto_d(current_game.players[i].position.y, current_game.players[i].position.x); // move beam to object coordinates
			// Moveto_d(current_game.players[i].position.y, current_game.players[i].position.y); // move beam to object coordinates
			dp_VIA_t1_cnt_lo = 24; // set scaling factor for drawing; TODO: in future, use player.scaling_factor (POWER UP)
			Draw_VLp(&vectors_battle_car); // draw vector list
#if DEBUG_ENABLED
			// temporary disabled
			// debugPos[0] = (char)('0' + (current_game.players[i].position.y / 10));
			// debugPos[1] = (char)('0' + (current_game.players[i].position.y % 10));
			// Print_Str_d(30, -30, (void*)debugPos);
#endif
		}
		// print player end

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
		// draw active bullets end
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

		// iterate over all player objects: (1) get input (2) process resulting actions
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			current_player = &current_game.players[i];
			current_player->get_input(current_player);

			// move player and objectiles; collision detection
			update_player(current_player);

			if (current_player->input.pause_button && !current_game.pause.is_pause)
			{
				// only one player can request the pause
				current_game.pause.is_pause = 1;
				current_game.pause.player_who_requested_pause = current_player->player_id;
			}
		}

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
		// timer end
#endif
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ FRAME END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
