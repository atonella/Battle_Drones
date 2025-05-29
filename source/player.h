#pragma once

#define DEFAULT_HEALTH 100
#define MAX_HEALTH 128

struct player_t
{
	unsigned int is_human;
	unsigned int health;
	// score
	// status
	// coordinate y,x (union?)
};
