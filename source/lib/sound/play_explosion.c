// ***************************************************************************
// sound
// ***************************************************************************

#include <vectrex.h>
#include "sound.h"

// ---------------------------------------------------------------------------
// start new explosion

void play_explosion(const struct sound_explosion_t* explosion)
{
	// Vec_Expl_Timer == 0 indicates that no current explosion is playing
	Stop_Sound();
	stop_music();
	current_explosion = explosion;
	Vec_Expl_Flag = 128; // start new explosion
}

// ***************************************************************************
// end of file
// ***************************************************************************
