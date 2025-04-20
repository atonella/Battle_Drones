// ***************************************************************************
// level
// ***************************************************************************

#include "level.h"
#include "game.h"
#include "utils/utils.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------

struct level_t current_level = {
	.status = LEVEL_LOST,
};

// ---------------------------------------------------------------------------

void level_init()
{
	current_level.status = LEVEL_PLAY;
}

// ---------------------------------------------------------------------------

void level_play(void)
{
	while (current_level.status == LEVEL_PLAY)
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

		// end of frame
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
