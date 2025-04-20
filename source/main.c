// ***************************************************************************
// main
// ***************************************************************************

#include "car.h"
#include "game.h"
#include <vectrex.h>

// ---------------------------------------------------------------------------
// at system startup, a cold reset is performed
// cold reset: the vectrex logo is shown, all ram data is cleared
// if the reset button is pressed, then a warm reset is performed
// warm reset: skip vectrex logo and keep ram data
// after each reset, the game title screen is shown and then main() is called
// ---------------------------------------------------------------------------

// Original main, commented out for displaying vectors_car[]

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

/*
int main(void)
{
	do
	{
		Wait_Recal();					// synchronize frame rate to 50 Hz

		// draw car

		Intensity_5F();					// set brightness of the electron beam
		Reset0Ref();					// reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f;		// set scaling factor for positioning
		Moveto_d(64, -64);				// move beam to object coordinates
		dp_VIA_t1_cnt_lo = 32;			// set scaling factor for drawing
		Draw_VLp(&vectors_car);			// draw vector list

		// draw same car with larger scale

		Intensity_5F();					// set brightness of the electron beam
		Reset0Ref();					// reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f;		// set scaling factor for positioning
		Moveto_d(64, 64);				// move beam to object coordinates
		dp_VIA_t1_cnt_lo = 48;			// set scaling factor for drawing
		Draw_VLp(&vectors_car);			// draw vector list

		// draw same car with very large scale

		Intensity_5F();					// set brightness of the electron beam
		Reset0Ref();					// reset beam to center
		dp_VIA_t1_cnt_lo = 0x7f;		// set scaling factor for positioning
		Moveto_d(-64, -64);				// move beam to object coordinates
		dp_VIA_t1_cnt_lo = 80;			// set scaling factor for drawing
		Draw_VLp(&vectors_car);			// draw vector list

	}
	while(1);
}
*/
// ***************************************************************************
// end of file
// ***************************************************************************
