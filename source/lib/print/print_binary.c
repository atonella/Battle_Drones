// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print binary unsigned int value at absolute coordinates (y, x)

void print_binary(int y, int x, unsigned int z)
{
	volatile char message[9];
	message[8] = '\x80';
	unsigned int i = 7;
	do
	{
		message[i--] = (char) ('0' + (z & 1));
		z >>= 1; 
	}
	while (i != 255);	
	reset_print_position();
	Print_Str_d(y, x, (void*) &message[0]);
}

// ***************************************************************************
// end of file
// ***************************************************************************
