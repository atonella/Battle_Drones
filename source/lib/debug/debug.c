// ***************************************************************************
// debug
// ***************************************************************************

#include "../../input.h"
#include "print/print.h"
#include "utils/controller.h"
#include "utils/utils.h"
#include <vectrex.h>

#include "debug.h"

// ---------------------------------------------------------------------------

void _f_debug(char* text, enum debug_type_t type, void* p_value, char* file, unsigned long int length, unsigned long int line)
{
	Clear_Sound();

	long unsigned int text_hw = Vec_Text_HW;
	Vec_Text_HW = 0xF850;

	char* p = file + length;
	length = 0;
	while ((*(--p) != '\\') && (p != file))
	{
		++length;
	}

	volatile char vfile[length--];
	unsigned long int i;
	for (i = 0; i < length; ++i)
	{
		char c = *(++p);
		if ((c >= 'a') && (c <= 'z'))
			c -= ('a' - 'A');
		vfile[i] = c;
	}
	vfile[length] = '\x80';

	do
	{
		DP_to_C8();
		Wait_Recal();
		Intensity_5F();
		print_string(90, -120, text);
		print_string(50, -120, "FILE:\x80");
		print_string(30, -120, (char*)&vfile[0]);
		print_string(0, -120, "LINE:\x80");
		print_long_unsigned_int(-20, -120, line);
		print_string(-50, -120, "VALUE:\x80");
		switch (type)
		{
			case DEBUG_TYPE_UNSIGNED_INT:
				print_unsigned_int(-70, -120, *((unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_SIGNED_INT:
				print_signed_int(-70, -120, *((signed int*)(p_value)));
				break;
			case DEBUG_TYPE_LONG_UNSIGNED_INT:
				print_long_unsigned_int(-70, -120, *((long unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_LONG_SIGNED_INT:
				print_long_signed_int(-70, -120, *((long signed int*)(p_value)));
				break;
			case DEBUG_TYPE_CHAR:
				print_char(-70, -120, *((char*)(p_value)));
				break;
			case DEBUG_TYPE_POINTER:
				print_long_hex(-70, -120, *((long unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_HEX:
				print_hex(-70, -120, *((unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_LONG_HEX:
				print_long_hex(-70, -120, *((long unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_BINARY:
				print_binary(-70, -120, *((unsigned int*)(p_value)));
				break;
			case DEBUG_TYPE_LONG_BINARY:
				print_long_binary(-70, -120, *((long unsigned int*)(p_value)));
				break;
			default:
				break;
		}
		check_buttons();
	} while (!button_1_1_pressed());

	Vec_Text_HW = text_hw;
}

void debug_print_input(struct input_t input)
{
	/*
	Prints the inputs of a player. It DOES NOT distinguish between Controller 1 and Controller 2.
	*/
	Print_Str_d(0, 0, (void*)"DEBUG ON\x80");
	// Buttons
	if (input.fire_button)
	{
		Print_Str_d(-81, -127, (void*)"FIRE\x80");
	}
	if (input.throttle_button)
	{
		Print_Str_d(-94, -127, (void*)"THROTTLE\x80");
	}
	if (input.reverse_button)
	{
		Print_Str_d(-107, -127, (void*)"REVERSE\x80");
	}
	if (input.pause_button)
	{
		Print_Str_d(-120, -127, (void*)"PAUSE\x80");
	}
	// Joystick
	switch (input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			Print_Str_d(-68, 45, (void*)"CENTER\x80");
			break;
		case JOY_8_WAY_UP:
			Print_Str_d(-81, 45, (void*)"UP\x80");
			break;
		case JOY_8_WAY_LEFT_UP:
			Print_Str_d(-120, 45, (void*)"LEFT\x80");
			Print_Str_d(-81, 45, (void*)"UP\x80");
			break;
		case JOY_8_WAY_LEFT:
			Print_Str_d(-120, 45, (void*)"LEFT\x80");
			break;
		case JOY_8_WAY_LEFT_DOWN:
			Print_Str_d(-120, 45, (void*)"LEFT\x80");
			Print_Str_d(-107, 45, (void*)"DOWN\x80");
			break;
		case JOY_8_WAY_DOWN:
			Print_Str_d(-107, 45, (void*)"DOWN\x80");
			break;
		case JOY_8_WAY_RIGHT_DOWN:
			Print_Str_d(-94, 45, (void*)"RIGHT\x80");
			Print_Str_d(-107, 45, (void*)"DOWN\x80");
			break;
		case JOY_8_WAY_RIGHT:
			Print_Str_d(-94, 45, (void*)"RIGHT\x80");
			break;
		case JOY_8_WAY_RIGHT_UP:
			Print_Str_d(-94, 45, (void*)"RIGHT\x80");
			Print_Str_d(-81, 45, (void*)"UP\x80");
			break;
		default:
			Print_Str_d(-55, 45, (void*)"DEFAULT CASE\x80");
			break;
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
