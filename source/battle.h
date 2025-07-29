#pragma once
#include "math/better_rng.h"
#include "player.h"
#include "utils/controller.h"
#include "utils/vector.h"
#include <vectrex.h>

/*
	To prevent overflow, take bullet travel distance into account.
	Values should not exceed:
		max_val(int) - BULLET_TRAVEL_DISTANCE_PER_TICK = 121
		min_val(int) + BULLET_TRAVEL_DISTANCE_PER_TICK = -122
	Diagonally bullets travel less in x or y direction, therefore only
	non-diagonal travel distance is taken into account.
*/
#define ARENA_LIMIT_UP 90
#define ARENA_LIMIT_LOW -120
#define ARENA_LIMIT_LEFT -120
#define ARENA_LIMIT_RIGHT 120
#define BLOW_UP 1
#define WINNER_NOT_SET 255

// ---------------------------------------------------------------------------

extern const struct packet_t battle_arena[];
extern const signed char drone_vector_list_0[];
extern const signed char drone_vector_list_1[];
extern const signed char drone_vector_list_2[];
extern const signed char drone_vector_list_3[];

// ---------------------------------------------------------------------------

struct player_stats_t
{
	unsigned int player_id;
	unsigned int kills;
	unsigned int deaths;
	char printable_stats[22];
	unsigned int has_won;
};
// ---------------------------------------------------------------------------

enum battle_status
{
	BATTLE_PLAY,
	BATTLE_FINISHED,
};

// ---------------------------------------------------------------------------

struct battle_t
{
	enum battle_status status;
	unsigned int winner_player_id;
};

// ---------------------------------------------------------------------------

extern struct battle_t current_battle;

// ---------------------------------------------------------------------------

/*
	The battle_init function initializes the game state for a battle. The
	complete configuration of the players (incl. controllers) based on the
	chosen game mode is done here. Random number generators for the bots and
	the	respawn positions are also done here.
*/
void battle_init(void);
/*
	The battle_play function implements the main game loop for the actual battle.
	It handles rendering, player input, game state updates, collision detection
	and win condition checks, player respawn logic, bullet rendering, and pause
	handling.
*/
void battle_play(void);
/*
	Prints the winning player and all stats to the screen. Players can choose
	if the want to play again or return to the title screen.

	Returns:
		0, int: if not playing again (returning to title screen)
		1, int: if playing again

*/
int battle_show_winner_screen(void);

// ***************************************************************************
// end of file
// ***************************************************************************
