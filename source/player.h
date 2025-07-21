#pragma once

#include "bullet.h"
#include "input.h"
#include "position.h"

#define DEFAULT_HEALTH 100
#define MAX_HEALTH 128
#define MAX_BULLETS 3
#define SPEED_MAX 1
#define DRONE_WIDTH 15
#define DRONE_HEIGHT 15
#define DRONE_WIDTH_HALF DRONE_WIDTH / 2
#define DRONE_HEIGHT_HALF DRONE_HEIGHT / 2

struct player_t
{
	unsigned int player_id;
	unsigned int is_human;
	unsigned int health;
	struct position_t position;
	struct input_t input;
	unsigned int diagonally_counter;
	// score
	// status
	// coordinate y,x (union?)
	// struct input_t (*get_input)(struct player_t*); // TODO: ptr?
	void (*get_input)(struct player_t*); // TODO: ptr?
	struct bullet_t bullets[MAX_BULLETS];
	// unsigned int velocity;
	// unsigned int scaling_factor;
};

void update_player(struct player_t* player);
void update_bullet_position(struct bullet_t* bullet);
void move_player(struct player_t* player);