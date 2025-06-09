#include "player.h"

void move_player(struct player_t* player)
{
	// TODO: Sonntag das implementieren
	if (player->input.fire_button)
	{
		// shoot
	}
	if (player->input.throttle_button)
	{
		player->acceleration += (player->acceleration < 10) ? 1 : 0; // TODO:
	}
	if (player->input.reverse_button)
	{
		player->acceleration += player->acceleration > -10 ? -1 : 0; // TODO:
	}
	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;

		case JOY_8_WAY_UP:
			player->position.y += (unsigned)(player->acceleration * 2); // WARNING: IM AUGE BEHALTEN
			break;

		case JOY_8_WAY_LEFT_UP:
			break;

		case JOY_8_WAY_LEFT:
			break;

		case JOY_8_WAY_LEFT_DOWN:
			break;

		case JOY_8_WAY_DOWN:
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			break;

		case JOY_8_WAY_RIGHT:
			break;

		case JOY_8_WAY_RIGHT_UP:
			break;

		default:
			break;
	}
	// if (player->input.)
}
