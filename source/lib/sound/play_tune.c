// ***************************************************************************
// sound
// ***************************************************************************

#include <vectrex.h>
#include "sound.h"

// ---------------------------------------------------------------------------
// start tune (will keep playing)

void play_tune(unsigned int channel, long unsigned int frequency, unsigned int volume)
{
	unsigned int cha = channel << 1;
	unsigned int x = (unsigned int) (frequency & 255LU);
	Sound_Byte(cha++, x);
	unsigned int y = (unsigned int) (frequency >> 8);
	Sound_Byte(cha, y);
	unsigned int z = channel + 8U;
	Sound_Byte(z, volume);
	Sound_Byte(7, 0b11111000);
}

// ***************************************************************************
// end of file
// ***************************************************************************
