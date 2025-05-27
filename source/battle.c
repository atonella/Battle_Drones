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
	current_battle.status = BATTLE_PLAY;
}

// ---------------------------------------------------------------------------

void battle_play(void)
{
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

		// frame start: this is where the action happens...
		/*
		state->inputHandler->update();
		for (int i = 0; i < state->playerCount; i++)
		{
			state->players[i].update(&state->players[i], state->inputHandler); // 1 Frame
		}

		*/
		// end of frame
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
