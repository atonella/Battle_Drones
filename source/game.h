// ***************************************************************************
// game
// ***************************************************************************

#pragma once

#include "battle.h"

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
};

// ---------------------------------------------------------------------------

// Extern declaration = declaration of variable; compiler searches for definition
extern struct game_t current_game;

// ---------------------------------------------------------------------------

int game(void);
void game_play(void);

// ***************************************************************************
// end of file
// ***************************************************************************
