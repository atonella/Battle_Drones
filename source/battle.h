// ***************************************************************************
// level
// ***************************************************************************

#pragma once
#include "player.h"
#include "utils/controller.h"
#include "utils/vector.h"
#include <vectrex.h>

#define BLOW_UP 1
// To prevent overflow, take bullet travel distance into account: values should not exceed max_val(int) - BULLET_TRAVEL_DISTANCE_PER_TICK = 121.
// Diagonally bullets travel less in x or y direction, therefore only non-diagonal travel distance is taken into account.
#define ARENA_LIMIT_UP 90
#define ARENA_LIMIT_LOW -120
#define ARENA_LIMIT_LEFT -120
#define ARENA_LIMIT_RIGHT 120

// ---------------------------------------------------------------------------

extern const struct packet_t battle_arena[];
extern const signed char drone_vector_list_0[];
extern const signed char drone_vector_list_1[];
extern const signed char drone_vector_list_2[];
extern const signed char drone_vector_list_3[];

// ---------------------------------------------------------------------------

enum battle_status
{
	BATTLE_PLAY,
	BATTLE_PAUSE,
	BATTLE_FINISHED,
};

// ---------------------------------------------------------------------------

struct battle_t
{
	enum battle_status status;
};

// ---------------------------------------------------------------------------

extern struct battle_t current_battle;

// ---------------------------------------------------------------------------

void battle_init(void);
void battle_play(void);

// ***************************************************************************
// end of file
// ***************************************************************************
