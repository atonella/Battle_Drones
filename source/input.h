#pragma once

#include "assert.h"
#include "lib/debug/debug.h"
#include "utils/controller.h"

struct player_t;

enum joystick_8_way
{
	JOY_8_WAY_CENTER,
	JOY_8_WAY_UP,
	JOY_8_WAY_LEFT_UP,
	JOY_8_WAY_LEFT,
	JOY_8_WAY_LEFT_DOWN,
	JOY_8_WAY_DOWN,
	JOY_8_WAY_RIGHT_DOWN,
	JOY_8_WAY_RIGHT,
	JOY_8_WAY_RIGHT_UP,
};

enum direction
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_UP,
};

struct input_t
{
	unsigned int fire_button;
	unsigned int pause_button;
	enum joystick_8_way joystick_direction;
};

// struct input_t get_human_input(unsigned int player);
// struct input_t get_bot_input();
void get_human_input(struct player_t* player);
void get_bot_input(struct player_t* player);
enum joystick_8_way eval_joystick_position(const struct player_t* player);
