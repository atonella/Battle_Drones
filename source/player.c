#include "player.h"
#include "game.h"

#define ACCELERATION_MAX 2
#define CAR_WIDTH 11 // empirical value
#define CAR_HEIGHT 16 // empirical value
#define CAR_WIDTH_HALF 6 // empirical value
#define CAR_HEIGHT_HALF 8 // empirical value

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

// TODO: does only work now (without rotation of car)
static inline __attribute__((always_inline)) int check_for_car_collision(const struct player_t* car1, const struct player_t* car2)
{
	// calculate distance between car1 and car2
	int diff_x = car1->position.x - car2->position.x;
	if (diff_x < 0)
	{
		diff_x = -diff_x;
	}
	if (diff_x >= CAR_WIDTH)
	{
		// no hit possible -> exit early
		return 0;
	}
	int diff_y = car1->position.y - car2->position.y;
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	// check for collision
	return (diff_x < (CAR_WIDTH) && diff_y < (CAR_HEIGHT));
}

// TODO: does only work now (without rotation of car)
static inline __attribute__((always_inline)) int check_for_bullet_car_collision(const struct bullet_t* bullet, const struct player_t* car)
{
	// car can't hit itself
	if (bullet->owner_id == car->player_id)
	{
		return 0;
	}
	// calculate distance between bullet and car
	int diff_y = bullet->position.y - (car->position.y - CAR_HEIGHT_HALF); // bugfix: real center of car is on the front (!= in the middle)
	if (diff_y < 0)
	{
		diff_y = -diff_y;
	}
	if (diff_y >= CAR_HEIGHT)
	{
		// no hit possible -> exit early
		return 0;
	}
	int diff_x = bullet->position.x - car->position.x;
	if (diff_x < 0)
	{
		diff_x = -diff_x;
	}
	// check for collision
	return (diff_x < CAR_WIDTH_HALF && diff_y < CAR_HEIGHT_HALF);
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
	if (bullet->position.x < -105 || bullet->position.x > 105 || bullet->position.y < -117 || bullet->position.y > 88)
	{
		bullet->is_active = BULLET_INACTIVE;
		return; // return early, because only 1 type of collision possible
	}
	// check for collision with car
	for (unsigned int i = 0; i < current_game.no_of_players; i++)
	{
		struct player_t* car = &current_game.players[i];
		if (check_for_bullet_car_collision(bullet, car))
		{
			bullet->is_active = BULLET_INACTIVE;
			// TODO: add damage handling here; add sound effect; add visual effects

			break;
		}
	}
}

void move_player(struct player_t* player)
{
	int delta = player->acceleration * 1;
	int reduced_delta = delta / 2; // slower speed, if sliding against wall

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

	// move the player
	move_player(player);

	// check collisions with other cars
	for (unsigned int i = 0; i < current_game.no_of_players; i++)
	{
		struct player_t* other = &current_game.players[i];
		// skip identical player
		if (other == player)
		{
			continue;
		}
		if (check_for_car_collision(player, other))
		{
			// Collision detected => revert movement; stop acceleration
			player->position = original_position;
			player->acceleration = 0;
			other->acceleration = 0;
			break;
		}
	}
}
