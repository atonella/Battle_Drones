#include "player.h"
#include "game.h"

// boundary checks: (1) determine direction (2) check for boundary
static inline __attribute__((always_inline)) int would_not_hit_horizontal_boundary(const struct player_t* player, int delta)
{
	return (delta > 0 && player->position.coordinates.y + delta < ARENA_LIMIT_UP) || // upper boundary
		(delta < 0 && player->position.coordinates.y + delta > ARENA_LIMIT_LOW); // lower boundary
}

static inline __attribute__((always_inline)) int would_not_hit_vertical_boundary(const struct player_t* player, int delta)
{
	return (delta < 0 && player->position.coordinates.x + delta > ARENA_LIMIT_LEFT) || // left boundary
		(delta > 0 && player->position.coordinates.x + delta < ARENA_LIMIT_RIGHT); // right boundary
}

// This is slightly faster than using Obj_Hit() bios routine.
static inline __attribute__((always_inline)) int check_for_bullet_drone_collision(const struct bullet_t* bullet, const struct player_t* drone)
{
	if (bullet->owner_id == drone->player_id)
	{
		// drone can't hit itself
		return 0;
	}
	// calculate distance between bullet and drone
	int diff_y = bullet->position.coordinates.y - (drone->position.coordinates.y);
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	if (diff_y >= DRONE_HEIGHT)
	{
		// no hit possible -> exit early
		return 0;
	}
	int diff_x = bullet->position.coordinates.x - drone->position.coordinates.x;
	if (diff_x < 0)
	{
		diff_x = -diff_x;
	}
	// check for collision
	return (diff_x < DRONE_WIDTH_HALF && diff_y < DRONE_HEIGHT_HALF);
}

static struct bullet_t* find_free_bullet(struct player_t* player)
{
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		if (player->bullets[i].is_active == BULLET_INACTIVE)
		{
			return &player->bullets[i];
		}
	}
	// no inactive bullet
	return 0;
}

void update_bullet_position(struct bullet_t* bullet)
{
	// move bullet based on direction
	switch (bullet->direction)
	{
		case JOY_8_WAY_CENTER:
			break;
		case JOY_8_WAY_UP:
			bullet->position.coordinates.y += BULLET_TRAVEL_DISTANCE_PER_TICK;
			break;
		case JOY_8_WAY_DOWN:
			bullet->position.coordinates.y -= BULLET_TRAVEL_DISTANCE_PER_TICK;
			break;
		case JOY_8_WAY_LEFT:
			bullet->position.coordinates.x -= BULLET_TRAVEL_DISTANCE_PER_TICK;
			break;
		case JOY_8_WAY_RIGHT:
			bullet->position.coordinates.x += BULLET_TRAVEL_DISTANCE_PER_TICK;
			break;
		case JOY_8_WAY_LEFT_UP:
			bullet->position.coordinates.x -= BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			bullet->position.coordinates.y += BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			break;
		case JOY_8_WAY_RIGHT_UP:
			bullet->position.coordinates.x += BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			bullet->position.coordinates.y += BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			break;
		case JOY_8_WAY_LEFT_DOWN:
			bullet->position.coordinates.x -= BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			bullet->position.coordinates.y -= BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			break;
		case JOY_8_WAY_RIGHT_DOWN:
			bullet->position.coordinates.x += BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			bullet->position.coordinates.y -= BULLET_TRAVEL_DISTANCE_PER_TICK_DIAGONALLY;
			break;
		default:
			break;
	}
	// check for collision with drones
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		struct player_t* drone = &current_battle.players[i];
		if (check_for_bullet_drone_collision(bullet, drone))
		{
			// bullet hits a drone
			bullet->is_active = BULLET_INACTIVE;
			if (drone->health > BULLET_DAMAGE_DEFAULT)
			{
				drone->health -= BULLET_DAMAGE_DEFAULT;
			}
			else
			{
				// drone got destroyed
				// move drone out of arena
				drone->position.coordinates.x = 0;
				drone->position.coordinates.y = 127;
				drone->health = PLAYER_HEALTH_DEFAULT;
				drone->respawn_counter = 200;
				drone->death_counter += 1;
				current_battle.players[bullet->owner_id].kill_counter += 1;
			}
		}
	}
	// check for collision with arena border
	if (bullet->position.coordinates.x < ARENA_LIMIT_LEFT || bullet->position.coordinates.x > ARENA_LIMIT_RIGHT || bullet->position.coordinates.y < ARENA_LIMIT_LOW || bullet->position.coordinates.y > ARENA_LIMIT_UP)
	{
		bullet->is_active = BULLET_INACTIVE;
	}
}

void move_player(struct player_t* player)
{
	int delta = SPEED_MAX;

	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;
		// vertically
		case JOY_8_WAY_UP:
			if (would_not_hit_horizontal_boundary(player, delta))
				player->position.coordinates.y += delta;
			break;

		case JOY_8_WAY_DOWN:
			if (would_not_hit_horizontal_boundary(player, -delta))
				player->position.coordinates.y -= delta;
			break;
		// horizontally
		case JOY_8_WAY_LEFT:
			if (would_not_hit_vertical_boundary(player, -delta))
				player->position.coordinates.x -= delta;
			break;

		case JOY_8_WAY_RIGHT:
			if (would_not_hit_vertical_boundary(player, delta))
				player->position.coordinates.x += delta;
			break;
		// diagonally
		case JOY_8_WAY_LEFT_UP:
			// adjust the diagonally speed to approx. the same as horizontally/vertically
			player->diagonally_counter += 7;
			if (player->diagonally_counter > 10)
			{
				player->diagonally_counter -= 10;
				if (would_not_hit_vertical_boundary(player, -delta))
				{
					player->position.coordinates.x -= would_not_hit_horizontal_boundary(player, delta);
				}
				if (would_not_hit_horizontal_boundary(player, delta))
				{
					player->position.coordinates.y += would_not_hit_vertical_boundary(player, -delta);
				}
			}
			break;

		case JOY_8_WAY_RIGHT_UP:
			player->diagonally_counter += 7;
			if (player->diagonally_counter > 10)
			{
				player->diagonally_counter -= 10;
				if (would_not_hit_vertical_boundary(player, delta))
				{
					player->position.coordinates.x += would_not_hit_horizontal_boundary(player, delta);
				}
				if (would_not_hit_horizontal_boundary(player, delta))
				{
					player->position.coordinates.y += would_not_hit_vertical_boundary(player, delta);
				}
			}
			break;

		case JOY_8_WAY_LEFT_DOWN:
			player->diagonally_counter += 7;
			if (player->diagonally_counter > 10)
			{
				player->diagonally_counter -= 10;
				if (would_not_hit_vertical_boundary(player, -delta))
				{
					player->position.coordinates.x -= would_not_hit_horizontal_boundary(player, -delta);
				}
				if (would_not_hit_horizontal_boundary(player, -delta))
				{
					player->position.coordinates.y -= would_not_hit_vertical_boundary(player, -delta);
				}
			}
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			player->diagonally_counter += 7;
			if (player->diagonally_counter > 10)
			{
				player->diagonally_counter -= 10;
				if (would_not_hit_vertical_boundary(player, delta))
				{
					player->position.coordinates.x += would_not_hit_horizontal_boundary(player, -delta);
				}
				if (would_not_hit_horizontal_boundary(player, -delta))
				{
					player->position.coordinates.y -= would_not_hit_vertical_boundary(player, delta);
				}
			}
			break;

		default:
			break;
	}
}

void update_player(struct player_t* player)
{
	// for restoring position if collision detected

	long int original_position = player->position.yx; // copy position
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		// update bullet if active
		if (player->bullets[i].is_active == BULLET_ACTIVE)
		{
			update_bullet_position(&player->bullets[i]);
		}
	}
	// check if player is pressing fire button
	if (player->input.fire_button && player->input.joystick_direction != JOY_8_WAY_CENTER)
	{
		// create new bullet, if bullet buffer is not full
		struct bullet_t* bullet = find_free_bullet(player);
		if (bullet != 0)
		{
			bullet->position.yx = player->position.yx; // copy position
			bullet->direction = player->input.joystick_direction;
			bullet->is_active = BULLET_ACTIVE;
			bullet->owner_id = player->player_id;
		}
	}

	move_player(player);

	// check collisions with other drones
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		struct player_t* other = &current_battle.players[i];
		if (other == player)
		{
			// skip identical player
			continue;
		}
		if (check_for_drone_collision(player, other))
		{
			// Collision detected => revert movement
			player->position.yx = original_position; // copy position
			break;
		}
	}
}
