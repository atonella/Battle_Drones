// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print decimal int value at absolute coordinates (y, x)

void print_signed_int(int y, int x, int z)
{
	volatile char message[5];
	message[4] = '\x80';
	message[2] = '0';
	if (z >= 0)
	{
		message[0] = (char) 0x2b;
	}
	else
	{
		message[0] = (char) 0x2d;
		z = -z;
	}
	if (z < 100)
	{
		message[1] = '0';
	}
	else
	{
		message[1] = '1';
		z -= 100;
	}
	while (z >= 10)
	{
		++message[2];
		z -= 10;
	}
	message[3] = '0' + (unsigned char) z;
	reset_print_position();
	Print_Str_d(y, x, (void*) &message[0]);
}

// ***************************************************************************
// end of file
// ***************************************************************************
