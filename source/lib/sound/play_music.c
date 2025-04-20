// ***************************************************************************
// sound
// ***************************************************************************

#include <vectrex.h>
#include "sound.h"

// ---------------------------------------------------------------------------
// start new music

void play_music(const struct sound_music_t* music)
{
	// Vec_Music_Flag == 0 indicates that no current sound is playing
	stop_explosion();
	current_music = music;
	Vec_Music_Flag = 1; // start new music
}

// ***************************************************************************
// end of file
// ***************************************************************************
