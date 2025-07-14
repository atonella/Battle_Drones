#include "player.h"

#define ACCELERATION_MAX 2

// boundary checks: (1) determine direction (2) check for boundary
static inline __attribute__((always_inline)) int would_hit_vertical_boundary(const struct player_t* player, int delta)
{
	return (delta > 0 && player->position.y + delta >= 88) || // upper boundary
		(delta < 0 && player->position.y + delta <= -117); // lower boundary
}

static inline __attribute__((always_inline)) int would_hit_horizontal_boundary(const struct player_t* player, int delta)
{
	return (delta < 0 && player->position.x + delta <= -105) || // left boundary
		(delta > 0 && player->position.x + delta >= 105); // right boundary
}

void move_player(struct player_t* player)
{
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

	int delta = player->acceleration * 1; // TODO: noch nicht sinnvoll

	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;

		case JOY_8_WAY_UP:
			if (!would_hit_vertical_boundary(player, delta))
				player->position.y += delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_DOWN:
			if (!would_hit_vertical_boundary(player, -delta))
				player->position.y -= delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_LEFT:
			if (!would_hit_horizontal_boundary(player, -delta))
				player->position.x -= delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_RIGHT:
			if (!would_hit_horizontal_boundary(player, delta))
				player->position.x += delta;
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_LEFT_UP:
			if (!would_hit_horizontal_boundary(player, -delta) && !would_hit_vertical_boundary(player, delta))
			{
				player->position.x -= delta;
				player->position.y += delta;
			}
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_RIGHT_UP:
			if (!would_hit_horizontal_boundary(player, delta) && !would_hit_vertical_boundary(player, delta))
			{
				player->position.x += delta;
				player->position.y += delta;
			}
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_LEFT_DOWN:
			if (!would_hit_horizontal_boundary(player, -delta) && !would_hit_vertical_boundary(player, -delta))
			{
				player->position.x -= delta;
				player->position.y -= delta;
			}
			else
				player->acceleration = 0;
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			if (!would_hit_horizontal_boundary(player, delta) && !would_hit_vertical_boundary(player, -delta))
			{
				player->position.x += delta;
				player->position.y -= delta;
			}
			else
				player->acceleration = 0;
			break;

		default:
			// assert(1 == 0);
			break;
	}
}
