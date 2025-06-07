#pragma once

#include "assert.h"
#include "lib/debug/debug.h"
#include "utils/controller.h"

struct input_t
{
	unsigned int pause_button;
	unsigned int reverse_button;
	unsigned int throttle_button;
	unsigned int fire_button;
};

struct input_t get_human_input(unsigned int player);
struct input_t get_bot_input();