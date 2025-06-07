#include "input.h"

struct input_t get_human_input(unsigned int player)
{
	check_buttons();
	struct input_t input = {
		.fire_button = 0,
		.throttle_button = 0,
		.reverse_button = 0,
		.pause_button = 0,
	};
	if (player == 0)
	{
		input.fire_button = button_1_4_held();
		input.throttle_button = button_1_3_held();
		input.reverse_button = button_1_2_held();
		input.pause_button = button_1_1_pressed();
	}
	else if (player == 1)
	{
		input.fire_button = button_2_4_held();
		input.throttle_button = button_2_3_held();
		input.reverse_button = button_2_2_held();
		input.pause_button = button_2_1_pressed();
	}
	else
	{
		assert(1 == 0);
	}
#ifdef DEBUG_ENABLED
	debug_print_input(input);
#endif
	return input;
}

struct input_t get_bot_input()
{
	// TODO: based on game info, make a move ==> decision making
	struct input_t input = {
		.fire_button = 0,
		.throttle_button = 0,
		.reverse_button = 0,
		.pause_button = 0,
	};
	return input;
};
