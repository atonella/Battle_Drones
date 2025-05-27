// ***************************************************************************
// level
// ***************************************************************************

#include "battle.h"
#include "game.h"
#include "utils/utils.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------

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
	1. Check & Process Input
	2. Computinh
	3. Rendering
	*/
	unsigned int frames = 0;
	unsigned int seconds = 0;
	unsigned int timer_not_exceeded = 1;
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

		// ************************************************************************************************************
		// frame start: this is where the action happens...
		/*
		state->inputHandler->update();
		for (int i = 0; i < state->playerCount; i++)
		{
			state->players[i].update(&state->players[i], state->inputHandler); // 1 Frame
		}

		*/

		for (unsigned int i = 0; i < current_game.no_of_players; i++)
		{
			// TODO: check input -> computing
			// sth like current_game.players[i]->getInput()
			// sth like current_game.players[i]->action()
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
			// TODO: Update time remaining on screen
		}
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
