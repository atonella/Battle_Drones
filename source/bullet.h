#pragma once
#include "input.h"
#include "position.h"

#define BULLET_SPEED 8
#define BULLET_ACTIVE 1
#define BULLET_INACTIVE 0

struct bullet_t
{
	struct position_t position;
	enum joystick_8_way direction;
	unsigned int is_active;
	unsigned int owner_id;
};
