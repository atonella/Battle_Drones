#include "player.h"
#include "game.h"

#define ARENA_LIMIT_UP 74
#define ARENA_LIMIT_LOW -127
#define ARENA_LIMIT_LEFT -121
#define ARENA_LIMIT_RIGHT 121

// boundary checks: (1) determine direction (2) check for boundary
static inline __attribute__((always_inline)) int would_not_hit_horizontal_boundary(const struct player_t* player, int delta)
{
	return (delta > 0 && player->position.y + delta < ARENA_LIMIT_UP) || // upper boundary
		(delta < 0 && player->position.y + delta > ARENA_LIMIT_LOW); // lower boundary, FIXME: treat possible overflow
}

static inline __attribute__((always_inline)) int would_not_hit_vertical_boundary(const struct player_t* player, int delta)
{
	return (delta < 0 && player->position.x + delta > ARENA_LIMIT_LEFT) || // left boundary
		(delta > 0 && player->position.x + delta < ARENA_LIMIT_RIGHT); // right boundary
}

static inline __attribute__((always_inline)) int check_for_drone_collision(const struct player_t* drone1, const struct player_t* drone2)
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

static inline __attribute__((always_inline)) int check_for_bullet_drone_collision(const struct bullet_t* bullet, const struct player_t* drone)
{
	// drone can't hit itself
	if (bullet->owner_id == drone->player_id)
	{
		return 0;
	}
	// calculate distance between bullet and drone
	int diff_y = bullet->position.y - (drone->position.y);
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	if (diff_y >= DRONE_HEIGHT)
	{
		// no hit possible -> exit early
		return 0;
	}
	int diff_x = bullet->position.x - drone->position.x;
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

// TODO maybe combine with switch case below
// FIXME: Overflow possible (Arena Border -1 + BULLET_SPEED)
void update_bullet_position(struct bullet_t* bullet)
{
	// move bullet based on direction
	switch (bullet->direction)
	{
		case JOY_8_WAY_CENTER:
			break;
		case JOY_8_WAY_UP:
			bullet->position.y += BULLET_SPEED;
			break;
		case JOY_8_WAY_DOWN:
			bullet->position.y -= BULLET_SPEED;
			break;
		case JOY_8_WAY_LEFT:
			bullet->position.x -= BULLET_SPEED;
			break;
		case JOY_8_WAY_RIGHT:
			bullet->position.x += BULLET_SPEED;
			break;
		case JOY_8_WAY_LEFT_UP:
			bullet->position.x -= BULLET_SPEED;
			bullet->position.y += BULLET_SPEED;
			break;
		case JOY_8_WAY_RIGHT_UP:
			bullet->position.x += BULLET_SPEED;
			bullet->position.y += BULLET_SPEED;
			break;
		case JOY_8_WAY_LEFT_DOWN:
			bullet->position.x -= BULLET_SPEED;
			bullet->position.y -= BULLET_SPEED;
			break;
		case JOY_8_WAY_RIGHT_DOWN:
			bullet->position.x += BULLET_SPEED;
			bullet->position.y -= BULLET_SPEED;
			break;
		default:
			break;
	}

	// check for collision with arena border
	// FIXME: BUG (OVERFLOW)
	if (bullet->position.x < ARENA_LIMIT_LEFT || bullet->position.x > ARENA_LIMIT_RIGHT || bullet->position.y < ARENA_LIMIT_LOW || bullet->position.y > ARENA_LIMIT_UP)
	{
		bullet->is_active = BULLET_INACTIVE;
		return; // return early, because only 1 type of collision possible
	}
	// check for collision with drones
	// OPTIMIZE: this approach is very resource instense
	for (unsigned int i = 0; i < current_game.no_of_players; i++)
	{
		struct player_t* drone = &current_game.players[i];
		if (check_for_bullet_drone_collision(bullet, drone))
		{
			bullet->is_active = BULLET_INACTIVE;
			// TODO: add damage handling here; add sound effect; add visual effects

			break;
		}
	}
}

void move_player(struct player_t* player)
{
	int delta = SPEED_MAX;
	int reduced_delta = delta / 2; // slower speed, if sliding against wall // TODO:

	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;
		// vertically
		case JOY_8_WAY_UP:
			if (would_not_hit_horizontal_boundary(player, delta))
				player->position.y += delta;
			break;

		case JOY_8_WAY_DOWN:
			if (would_not_hit_horizontal_boundary(player, -delta))
				player->position.y -= delta;
			break;
		// horizontally
		case JOY_8_WAY_LEFT:
			if (would_not_hit_vertical_boundary(player, -delta))
				player->position.x -= delta;
			break;

		case JOY_8_WAY_RIGHT:
			if (would_not_hit_vertical_boundary(player, delta))
				player->position.x += delta;
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
					player->position.x -= would_not_hit_horizontal_boundary(player, delta) ? delta : reduced_delta;
				}
				if (would_not_hit_horizontal_boundary(player, delta))
				{
					player->position.y += would_not_hit_vertical_boundary(player, -delta) ? delta : reduced_delta;
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
					player->position.x += would_not_hit_horizontal_boundary(player, delta) ? delta : reduced_delta;
				}
				if (would_not_hit_horizontal_boundary(player, delta))
				{
					player->position.y += would_not_hit_vertical_boundary(player, delta) ? delta : reduced_delta;
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
					player->position.x -= would_not_hit_horizontal_boundary(player, -delta) ? delta : reduced_delta;
				}
				if (would_not_hit_horizontal_boundary(player, -delta))
				{
					player->position.y -= would_not_hit_vertical_boundary(player, -delta) ? delta : reduced_delta;
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
					player->position.x += would_not_hit_horizontal_boundary(player, -delta) ? delta : reduced_delta;
				}
				if (would_not_hit_horizontal_boundary(player, -delta))
				{
					player->position.y -= would_not_hit_vertical_boundary(player, delta) ? delta : reduced_delta;
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
	struct position_t original_position = {
		.x = player->position.x,
		.y = player->position.y
	};
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
			bullet->position = player->position;
			bullet->direction = player->input.joystick_direction;
			bullet->is_active = BULLET_ACTIVE;
			bullet->owner_id = player->player_id;
		}
	}

	// move the player
	move_player(player);

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
			// Collision detected => revert movement; stop speed
			player->position = original_position;
			break;
		}
	}
}
