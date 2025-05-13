// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print decimal unsigned long int value at absolute coordinates (y, x)

void print_long_signed_int(int y, int x, long signed int z)
{
	volatile char message[7];
	message[6] = '\x80';
	message[4] = '0';
	message[3] = '0';
	message[2] = '0';
	message[1] = '0';
	if (z >= 0)
	{
		message[0] = (char) 0x2b;
	}
	else
	{
		message[0] = (char) 0x2d;
		z = -z;
	}
	while ((long unsigned int) z >= 10000)
	{
		++message[1];
		z -= 10000;
	}
	while (z >= 1000)
	{
		++message[2];
		z -= 1000;
	}
	while (z >= 100)
	{
		++message[3];
		z -= 100;
	}

	while (z >= 10)
	{
		++message[4];
		z -= 10;
	}
	message[5] = '0' + (unsigned char) z;
	reset_print_position();
	Print_Str_d(y, x, (void*) &message[0]);
}

// ***************************************************************************
// end of file
// ***************************************************************************
