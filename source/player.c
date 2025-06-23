#include "player.h"

#define ACCELERATION_MAX 2

void move_player(struct player_t* player)
{
	if (player->input.fire_button)
	{
		// TODO:
		// shoot
	}

	// Either throttle or reverse possible; reverse first enables "breaking" while driving forwards
	// TODO: bug if throttle + reverse + diagonally joystick direction pressed -> ultra fast and screen flickering
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
		player->acceleration += player->acceleration > 0 ? -1 : 0;
		player->acceleration += player->acceleration < 0 ? 1 : 0;
	}

	switch (player->input.joystick_direction)
	{
		// TODO: begrenzung (collision detection)
		case JOY_8_WAY_CENTER:
			break;

		case JOY_8_WAY_UP:
			player->position.y += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_LEFT_UP:
			player->position.x -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			player->position.y += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_LEFT:
			player->position.x -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN

			break;

		case JOY_8_WAY_LEFT_DOWN:
			player->position.x -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			player->position.y -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_DOWN:
			player->position.y -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			player->position.x += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			player->position.y -= player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_RIGHT:
			player->position.x += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_RIGHT_UP:
			player->position.x += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			player->position.y += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			break;

		default:
			// assert(1 == 0);
			break;
	}
}
