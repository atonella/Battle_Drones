#pragma once

#include "bullet.h"
#include "input.h"
#include "position.h"

#define PLAYER_HEALTH_DEFAULT 50
#define PLAYER_MAX_HEALTH 128
#define MAX_BULLETS 1
#define SPEED_MAX 1
#define DRONE_WIDTH 12
#define DRONE_HEIGHT 12
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
	unsigned int respawn_counter;
	unsigned int bot_difficulty;
};

inline __attribute__((always_inline)) int check_for_drone_collision(const struct player_t* drone1, const struct player_t* drone2)
{
	// calculate distance between drone1 and drone2
	int diff_x = drone1->position.x - drone2->position.x;
	if (diff_x < 0)
	{
		diff_x = -diff_x;
	}
	if (diff_x >= DRONE_WIDTH)
	{
		// no hit possible -> exit early
		return 0;
	}
	int diff_y = drone1->position.y - drone2->position.y;
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	// check for collision
	return (diff_x < (DRONE_WIDTH) && diff_y < (DRONE_HEIGHT));
}
void update_player(struct player_t* player);
void update_bullet_position(struct bullet_t* bullet);
void move_player(struct player_t* player);