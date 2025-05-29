// ***************************************************************************
// game
// ***************************************************************************

#pragma once

#include "player.h"

#define MAX_PLAYERS 4
#define NO_OF_GAMEMODES 3
// ---------------------------------------------------------------------------

enum gamemode
{
	SINGLEPLAYER = 1,
	MULTIPLAYER,
	DUELL,
};

struct game_t
{
	enum gamemode current_gamemode;
	unsigned int score[4];
	struct player_t players[4];
	unsigned int current_player;
	unsigned int no_of_players;
};

// ---------------------------------------------------------------------------

// Extern declaration = declaration of variable; compiler searches for definition
extern struct game_t current_game;

// ---------------------------------------------------------------------------

int game(void);

void game_init(void);
void game_play(void);
void game_end(void);
void game_over(void);

// ***************************************************************************
// end of file
// ***************************************************************************
