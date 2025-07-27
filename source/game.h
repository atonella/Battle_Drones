// ***************************************************************************
// game
// ***************************************************************************

#pragma once

#include "battle.h"
#include "math/better_rng.h"
#include "pause.h"
#include "player.h"

#define MAX_PLAYERS 4
#define NO_OF_GAMEMODES 3
// ---------------------------------------------------------------------------

enum gamemode
{
	SINGLEPLAYER = 1,
	MULTIPLAYER,
	DUEL,
};

struct game_t
{
	enum gamemode current_gamemode;
	unsigned int score[4];
	struct player_t players[4];
	unsigned int current_player;
	unsigned int no_of_players;
	struct pause_t pause;
};

// ---------------------------------------------------------------------------

// Extern declaration = declaration of variable; compiler searches for definition
extern struct game_t current_game;

// ---------------------------------------------------------------------------

int game(void);

void game_init(void);
__attribute__((__noreturn__)) void game_play(void);
void game_end(void);
void game_over(void);

// ***************************************************************************
// end of file
// ***************************************************************************
