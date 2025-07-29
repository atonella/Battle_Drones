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

void collect_player_stats(struct player_stats_t* stats);
void display_player_stats();