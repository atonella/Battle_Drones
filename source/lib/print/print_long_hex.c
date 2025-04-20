// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print long hex value at absolute coordinates (y, x)

void print_long_hex(int y, int x, long unsigned int z)
{
	char message[5];
	message[4] = '\x80';
	unsigned int lo = (unsigned int) z;
	unsigned int hi = (unsigned int) (z >> 8);
	
	if ((message[3] = (lo & 0b00001111) + '0') > '9')
	{
		message[3] += 7;
	}
	lo >>= 4;
	if ((message[2] = (lo & 0b00001111) + '0') > '9')
	{
		message[2] += 7;
	}
	if ((message[1] = (hi & 0b00001111) + '0') > '9')
	{
		message[1] += 7;
	}
	hi >>= 4;
	if ((message[0] = (hi & 0b00001111) + '0') > '9')
	{
		message[0] += 7;
	}
	reset_print_position();
	Print_Str_d(y, x, (void*) &message[0]);
}

// ***************************************************************************
// end of file
// ***************************************************************************
