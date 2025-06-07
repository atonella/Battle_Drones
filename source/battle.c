// ***************************************************************************
// level
// ***************************************************************************

#include "battle.h"
#include "game.h"
#include "utils/utils.h"
#include "utils/vector.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------
const struct packet_t battle_arena[]
	= {
		  { MOVE, { 127, -78 } },
		  { MOVE, { 53, -127 } },
		  // 180 | -205
		  // upper boarder
		  { DRAW, { 0, 127 } },
		  { DRAW, { 0, 127 } },
		  { DRAW, { 0, 60 } },
		  { DRAW, { 0, 106 } },
		  // 180 | 215
		  // right boarder
		  { DRAW, { -127, 0 } },
		  { DRAW, { -127, 0 } },
		  { DRAW, { -127, 0 } },
		  { DRAW, { -50, 0 } },
		  // -251 | 215
		  // bottom boarder
		  { DRAW, { 0, -127 } },
		  { DRAW, { 0, -127 } },
		  { DRAW, { 0, -60 } },
		  { DRAW, { 0, -106 } },
		  // -251 | -205
		  // left boarder
		  { DRAW, { 127, 0 } },
		  { DRAW, { 127, 0 } },
		  { DRAW, { 127, 0 } },
		  { DRAW, { 50, 0 } },
		  // 180 | -205
		  VL_END
	  };

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
	2. Check & Process Input
	3. Computing
	*/
	unsigned int frames = 0;
	unsigned int seconds = 0;
	unsigned int timer_not_exceeded = 1;
	struct input_t input;

	char time_elapsed[4] = "00\x80";
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

		Intensity_5F(); // set brightness of the electron beam
		Reset0Ref(); // reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f; // set scaling factor for positioning
		Moveto_d(0, 0); // move beam to object coordinates
		dp_VIA_t1_cnt_lo = 64; // set scaling factor for drawing
		Draw_VLp(&battle_arena); // draw vector list

		// ************************************************************************************************************
		// frame start: this is where the action happens...
		while (current_game.pause.is_pause)
		{
			unsigned int player = current_game.pause.player_who_requested_pause;
			input = current_game.players[player].get_input(player);
			if (!input.pause_button)
			{
				current_game.pause.is_pause = 0;
				current_game.pause.player_who_requested_pause = 255;
				continue;
			}
		}
		const char* s
			= "HALLO\x80";
		Print_Str_d(70, -120, (void*)s);
		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			// check_buttons();
			input = current_game.players[i].get_input(i);
			move_player(input); // TODO:: better function name
			// TODO: check input -> computing
			// TODO: compute movement.pause.is_pause)
			if (input.pause_button && !current_game.pause.is_pause)
			{
				// only one player can request the pause
				current_game.pause.is_pause = 1;
				current_game.pause.player_who_requested_pause = i;
			}
		}
		// end of frame
		// ************************************************************************************************************

		// Timer
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
		// Timer end
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
