#pragma once

#include "input.h"

#define DEFAULT_HEALTH 100
#define MAX_HEALTH 128

struct player_t
{
	unsigned int is_human;
	unsigned int health;
	// score
	// status
	// coordinate y,x (union?)
	// struct battlecar_t battlecar;
	struct input_t (*get_input)(unsigned int player);
};

void move_player(struct input_t input);
