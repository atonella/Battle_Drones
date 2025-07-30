#pragma once

#include "game.h"
#include "lib/print/print.h"

struct player_stats_t
{
	unsigned int player_id;
	unsigned int kills;
	unsigned int deaths;
	char printable_stats[22];
};

/*
	Modifies the passed array of player_stats_t structures with statistics for each player in the current battle.
*/
void collect_player_stats(struct player_stats_t* stats);
/*
	Displays player statistics on the screen:
		- player ID
		- kills
		- deaths
*/
void display_player_stats(struct player_stats_t* stats);