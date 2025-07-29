#include "player_stats.h"

void collect_player_stats(struct player_stats_t* stats)
{
	// collect stats for each player
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		stats[i].player_id = current_battle.players[i].player_id;
		stats[i].kills = current_battle.players[i].kill_counter;
		stats[i].deaths = current_battle.players[i].death_counter;
	}
}

void display_player_stats(struct player_stats_t* stats)
{
	print_string(20, -85, "PLAYER  K   D\x80");
	print_string(10, -85, "------ --- ---\x80");

	// Print stats for each player
	for (unsigned int i = 0; i < current_battle.no_of_players; i++)
	{
		int line_y = 0 - ((int)i * 15);
		// PLAYER
		print_unsigned_int(line_y, -51, stats[i].player_id + 1);
		// K
		print_unsigned_int(line_y, -6, stats[i].kills);
		// D
		print_unsigned_int(line_y, 39, stats[i].deaths);
	}
}