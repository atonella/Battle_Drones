#include "player.h"
#include "game.h"

#define ACCELERATION_MAX 2
#define DRONE_WIDTH 14 // empirical value
#define DRONE_HEIGHT 14 // empirical value

// boundary checks: (1) determine direction (2) check for boundary
static inline __attribute__((always_inline)) int would_not_hit_horizontal_boundary(const struct player_t* player, int delta)
{
	return (delta > 0 && player->position.y + delta < 88) || // upper boundary
		(delta < 0 && player->position.y + delta > -117); // lower boundary
}

static inline __attribute__((always_inline)) int would_not_hit_vertical_boundary(const struct player_t* player, int delta)
{
	return (delta < 0 && player->position.x + delta > -105) || // left boundary
		(delta > 0 && player->position.x + delta < 105); // right boundary
}

int check_for_drone_collision(const struct player_t* drone1, const struct player_t* drone2)
{
	// calculate distance between drone1 and drone2
	int diff_x = drone1->position.x - drone2->position.x;
	if (diff_x < 0)
	{
		diff_x = -diff_x;
	}
	int diff_y = drone1->position.y - drone2->position.y;
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	// check for collision
	// TODO: does only work now, without rotation of drone
	return (diff_x < (DRONE_WIDTH) && diff_y < (DRONE_HEIGHT));
}

void move_player(struct player_t* player)
{
	// for restoring position if collision detected
	struct position_t original_position = {
		.x = player->position.x,
		.y = player->position.y
	};

	if (player->input.fire_button)
	{
		// TODO:
		// shoot
	}
	// Either throttle or reverse possible; checking for reverse first -> enables "breaking" while driving forwards
	// FIXME: bug if throttle + reverse + diagonally joystick direction pressed -> ultra fast and screen flickering | (14/07/2025: can't reproduce)
	if (player->input.reverse_button)
	{
		player->acceleration += (player->acceleration > -ACCELERATION_MAX) ? -1 : 0; // TODO: better
	}
	else if (player->input.throttle_button)
	{
		player->acceleration += (player->acceleration < ACCELERATION_MAX) ? 1 : 0; // TODO: better
	}
	else
	{
		// no button pressed: reduce acceleration steadily
		player->acceleration += player->acceleration > 0 ? -1 : 0;
		player->acceleration += player->acceleration < 0 ? 1 : 0;
	}

	int delta = player->acceleration * 1;
	int reduced_delta = delta / 2; // slower speed, if sliding against wall

	// move the player
	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;

		case JOY_8_WAY_UP:
			if (would_not_hit_horizontal_boundary(player, delta))
				player->position.y += delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_DOWN:
			if (would_not_hit_horizontal_boundary(player, -delta))
				player->position.y -= delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_LEFT:
			if (would_not_hit_vertical_boundary(player, -delta))
				player->position.x -= delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_RIGHT:
			if (would_not_hit_vertical_boundary(player, delta))
				player->position.x += delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_LEFT_UP:
			if (would_not_hit_vertical_boundary(player, -delta))
			{
				player->position.x -= would_not_hit_horizontal_boundary(player, delta) ? delta : reduced_delta;
			}
			if (would_not_hit_horizontal_boundary(player, delta))
			{
				player->position.y += would_not_hit_vertical_boundary(player, -delta) ? delta : reduced_delta;
			}
			break;

		case JOY_8_WAY_RIGHT_UP:
			if (would_not_hit_vertical_boundary(player, delta))
			{
				player->position.x += would_not_hit_horizontal_boundary(player, delta) ? delta : reduced_delta;
			}
			if (would_not_hit_horizontal_boundary(player, delta))
			{
				player->position.y += would_not_hit_vertical_boundary(player, delta) ? delta : reduced_delta;
			}
			break;

		case JOY_8_WAY_LEFT_DOWN:
			if (would_not_hit_vertical_boundary(player, -delta))
			{
				player->position.x -= would_not_hit_horizontal_boundary(player, -delta) ? delta : reduced_delta;
			}
			if (would_not_hit_horizontal_boundary(player, -delta))
			{
				player->position.y -= would_not_hit_vertical_boundary(player, -delta) ? delta : reduced_delta;
			}
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			if (would_not_hit_vertical_boundary(player, delta))
			{
				player->position.x += would_not_hit_horizontal_boundary(player, -delta) ? delta : reduced_delta;
			}
			if (would_not_hit_horizontal_boundary(player, -delta))
			{
				player->position.y -= would_not_hit_vertical_boundary(player, delta) ? delta : reduced_delta;
			}
			break;

		default:
			break;
	}

	// check collisions with other drones
	for (unsigned int i = 0; i < current_game.no_of_players; i++)
	{
		struct player_t* other = &current_game.players[i];
		// skip identical player
		if (other == player)
		{
			continue;
		}
		if (check_for_drone_collision(player, other))
		{
			// Collision detected => revert movement; stop acceleration
			player->position = original_position;
			player->acceleration = 0;
			other->acceleration = 0;
			break;
		}
	}
}
