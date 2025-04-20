// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print decimal unsigned long int value at absolute coordinates (y, x)

void print_long_unsigned_int(int y, int x, unsigned long int z)
{
	volatile char message[6];
	message[5] = '\x80';
	message[3] = '0';
	message[2] = '0';
	message[1] = '0';
	message[0] = '0';
	while (z >= 10000)
	{
		++message[0];
		z -= 10000;
	}
	while (z >= 1000)
	{
		++message[1];
		z -= 1000;
	}
	while (z >= 100)
	{
		++message[2];
		z -= 100;
	}
	while (z >= 10)
	{
		++message[3];
		z -= 10;
	}
	message[4] = '0' + (unsigned char) z;
	reset_print_position();
	Print_Str_d(y, x, (void*) &message[0]);
}

// ***************************************************************************
// end of file
// ***************************************************************************
