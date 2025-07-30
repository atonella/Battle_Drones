#include "input.h"
#include "game.h"
#include "player.h"

void get_human_input(struct player_t* player)
{
	if (player->player_id == 0)
	{
		player->input.fire_button = button_1_4_pressed();
		player->input.pause_button = button_1_1_pressed();
	}
	else if (player->player_id == 1)
	{
		player->input.fire_button = button_2_4_pressed();
		player->input.pause_button = button_2_1_pressed();
	}
	else
	{
		// should never be evaluated
		assert(1 == 0);
	}
	player->input.joystick_direction = eval_joystick_position(player);
#if DEBUG_ENABLED
	debug_print_input(input);
#endif
}

void get_bot_input(struct player_t* player)
{
	player->input.fire_button = 0;
	player->input.joystick_direction = JOY_8_WAY_CENTER;

	// for random behavior
	unsigned int random_behavior = rand(&bot_rng) & 0x0F; // range: 0-15

	// find nearest human player to target
	struct player_t* target = 0;
	int closest_distance = 127; // large initial value
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		struct player_t* other = &current_battle.players[i];
		if (other == player || other->position.y > 120)
		{
			// skip itself and ignore destroyed invisible drones at position (127 | 0)
			continue;
		}
		// calculate distance approximately
		int diff_x = player->position.x - other->position.x;
		int diff_y = player->position.y - other->position.y;
		if (diff_x < 0)
		{
			diff_x = -diff_x;
		}
		if (diff_y < 0)
		{
			diff_y = -diff_y;
		}
		int distance = diff_x + diff_y; // approximation: pythagoras is to resource intensive

		if (distance < closest_distance)
		{
			closest_distance = distance;
			target = other;
		}
	}

	if (target != 0)
	{
		// direction to target
		int diff_x = target->position.x - player->position.x;
		int diff_y = target->position.y - player->position.y;

		// move towards target with a probability
		if (random_behavior < player->bot_difficulty)
		{
			// move
			// (1) horizontal (2) vertical
			if (diff_x < DRONE_WIDTH_HALF)
			{
				if (diff_y < -DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_LEFT_DOWN;
				}
				else if (diff_y > DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_LEFT_UP;
				}
				else
				{
					player->input.joystick_direction = JOY_8_WAY_LEFT;
				}
			}
			else if (diff_x > DRONE_WIDTH_HALF)
			{
				if (diff_y < -DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_RIGHT_DOWN;
				}
				else if (diff_y > DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_RIGHT_UP;
				}
				else
				{
					player->input.joystick_direction = JOY_8_WAY_RIGHT;
				}
			}
			else
			{
				// target in line vertically
				if (diff_y < -DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_DOWN;
				}
				else if (diff_y > DRONE_HEIGHT_HALF)
				{
					player->input.joystick_direction = JOY_8_WAY_UP;
				}
			}

			// fire if the target is within range (also shoot if target not aligned perfectly) and with a 1/16 chance
			if (((-DRONE_WIDTH < diff_x && diff_x < DRONE_WIDTH) || (-DRONE_HEIGHT < diff_y && diff_y < DRONE_HEIGHT)) && random_behavior == 1)
			{
				player->input.fire_button = 1;
			}
		}
		else
		{
			// move in random direction (also some sort of dodging bullets) by the rest of the probability
			player->input.joystick_direction = (enum joystick_8_way)(random_behavior & 0b111) + 1; // range: 1 .. 8 (JOY_8_WAY_CENTER excluded)
		}
	}
	else
	{
		// no target found, move into random direction
		player->input.joystick_direction = (enum joystick_8_way)(random_behavior % 9);
	}
}

typedef int (*joystick_func)();
joystick_func get_joystick_direction[2][4] = {
	{ joystick_1_left, joystick_1_right, joystick_1_down, joystick_1_up },
	{ joystick_2_left, joystick_2_right, joystick_2_down, joystick_2_up },
};

int check_joystick_direction(unsigned int player_id, unsigned int axis)
{
	return get_joystick_direction[player_id][axis]();
}

enum joystick_8_way eval_joystick_position(const struct player_t* player)
{
	/*
	Determines the direction of the joystick belonging to the passed player.

	Worst Case: 5 condition checks
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
	else if (check_joystick_direction(player->player_id, DIR_DOWN))
	{
		direction = JOY_8_WAY_DOWN;
	}
	else if (check_joystick_direction(player->player_id, DIR_UP))
	{
		direction = JOY_8_WAY_UP;
	}
	else
	{
		direction = JOY_8_WAY_CENTER;
	}
	return direction;
}
