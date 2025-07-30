#pragma once

#define PAUSE_OFF 0
#define PAUSE_ON 1

struct pause_t
{
	unsigned int is_pause;
	unsigned int player_who_requested_pause;
};