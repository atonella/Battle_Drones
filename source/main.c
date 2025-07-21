// ***************************************************************************
// main
// ***************************************************************************

#include "game.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------
// at system startup, a cold reset is performed
// cold reset: the vectrex logo is shown, all ram data is cleared
// if the reset button is pressed, then a warm reset is performed
// warm reset: skip vectrex logo and keep ram data
// after each reset, the game title screen is shown and then main() is called
// ---------------------------------------------------------------------------

int main(void)
{
	// local variables
	int error_code;

	// main loop
	do
	{
		error_code = game();
	} while (error_code == 0);

	// if error_code is <= 0, then a warm reset will be performed,
	// otherwise a cold reset will be performed,
	// after the reset, the game title screen appears,
	// then main() is called
	return error_code;
}

// ***************************************************************************
// end of file
// ***************************************************************************
