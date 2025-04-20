// ***************************************************************************
// print
// ***************************************************************************

#include <vectrex.h>
#include "print.h"

// ---------------------------------------------------------------------------
// print long binary unsigned int value at absolute coordinates (y, x)

void print_long_binary(int y, int x, long unsigned int z)
{
	volatile char message[17];
	message[16] = '\x80';
	unsigned int i = 15;
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
