#include "input.h"
#include "player.h"

void get_human_input(struct player_t* player)
{
	// TODO: optimize
	check_buttons();
	struct input_t input = {
		.fire_button = 0,
		.throttle_button = 0,
		.reverse_button = 0,
		.pause_button = 0,
		.joystick_direction = JOY_8_WAY_CENTER,
	};
	if (player->player_id == 0)
	{
		input.fire_button = button_1_4_pressed();
		input.throttle_button = button_1_3_held();
		input.reverse_button = button_1_2_held();
		input.pause_button = button_1_1_pressed();
	}
	else if (player->player_id == 1)
	{
		input.fire_button = button_2_4_pressed();
		input.throttle_button = button_2_3_held();
		input.reverse_button = button_2_2_held();
		input.pause_button = button_2_1_pressed();
	}
	else
	{
		// should never be evaluated
		assert(1 == 0);
	}
	check_joysticks();
	input.joystick_direction = eval_joystick_position(player);
#if DEBUG_ENABLED
	debug_print_input(input);
#endif
	player->input = input; // TODO: optimize by setting values directly
}

void get_bot_input(struct player_t* player)
{
	// TODO: based on game info, make a move ==> decision making
	struct input_t input = {
		.fire_button = 0,
		.throttle_button = 0,
		.reverse_button = 0,
		.pause_button = 0,
		.joystick_direction = JOY_8_WAY_CENTER,
	};
	player->input = input;
	// return input;
};

typedef int (*joystick_func)();
joystick_func get_joystick_direction[2][4] = {
	{ joystick_1_left, joystick_1_right, joystick_1_down, joystick_1_up },
	{ joystick_2_left, joystick_2_right, joystick_2_down, joystick_2_up },
};

int check_joystick_direction(unsigned int player_id, unsigned int axis)
{
	return get_joystick_direction[player_id][axis]();
}

enum joystick_8_way eval_joystick_position(struct player_t* player)
{
	/*
	Determines the direction of the joystick belonging to the passed player.

	Worst Case: 5 if-statements
	*/
	enum joystick_8_way direction;
	if (check_joystick_direction(player->player_id, DIR_LEFT))
	{
		// left half
		if (check_joystick_direction(player->player_id, DIR_DOWN))
		{
			direction = JOY_8_WAY_LEFT_DOWN;
		}
		else if (check_joystick_direction(player->player_id, DIR_UP))
		{
			direction = JOY_8_WAY_LEFT_UP;
		}
		else
		{
			direction = JOY_8_WAY_LEFT;
		}
	}
	else if (check_joystick_direction(player->player_id, DIR_RIGHT))
	{
		// right half
		if (check_joystick_direction(player->player_id, DIR_DOWN))
		{
			direction = JOY_8_WAY_RIGHT_DOWN;
		}
		else if (check_joystick_direction(player->player_id, DIR_UP))
		{
			direction = JOY_8_WAY_RIGHT_UP;
		}
		else
		{
			direction = JOY_8_WAY_RIGHT;
		}
	}
	else if (check_joystick_direction(player->player_id, DIR_UP))
	{
		direction = JOY_8_WAY_UP;
	}
	else if (check_joystick_direction(player->player_id, DIR_DOWN))
	{
		direction = JOY_8_WAY_DOWN;
	}
	else
	{
		direction = JOY_8_WAY_CENTER;
	}
	return direction;
}
