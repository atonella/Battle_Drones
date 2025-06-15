#include "player.h"

void move_player(struct player_t* player)
{
	char s[4] = "00\x80";
	// TODO:
	if (player->input.fire_button)
	{
		// shoot
	}

	// Either throttle or reverse possible
	if (player->input.throttle_button)
	{
		player->acceleration += (player->acceleration < 8) ? 1 : 0; // TODO:
	}
	else if (player->input.reverse_button)
	{
		player->acceleration += (player->acceleration > -8) ? -1 : 0; // TODO:
	}
	else
	{
		player->acceleration = player->acceleration - (player->acceleration > 0 ? 1 : 0);
	}

	switch (player->input.joystick_direction)
	{
		case JOY_8_WAY_CENTER:
			break;

		case JOY_8_WAY_UP:
			player->position.y += 1; // WARNING: IM AUGE BEHALTEN
			// player->position.y += player->acceleration * 1; // WARNING: IM AUGE BEHALTEN
			s[0] = (char)('0' + (player->position.y / 10));
			s[1] = (char)('0' + (player->position.y % 10));
			Print_Str_d(30, 0, (void*)s);
			break;

		case JOY_8_WAY_LEFT_UP:
			break;

		case JOY_8_WAY_LEFT:
			player->position.x -= 1;
			break;

		case JOY_8_WAY_LEFT_DOWN:
			break;

		case JOY_8_WAY_DOWN:
			player->position.y -= 1;
			break;

		case JOY_8_WAY_RIGHT_DOWN:
			break;

		case JOY_8_WAY_RIGHT:
			player->position.x += 1;
			break;

		case JOY_8_WAY_RIGHT_UP:
			break;

		default:
			assert(1 == 0);
			break;
	}
	// if (player->input.)
}
