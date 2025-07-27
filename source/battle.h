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

// battle arena size: 213 x 254 (y,x)
const struct packet_t battle_arena[]
	= {
		  // y | x
		  { MOVE, { ARENA_LIMIT_UP + DRONE_HEIGHT_HALF, ARENA_LIMIT_LEFT - DRONE_WIDTH_HALF } },
		  // 96 | -126
		  // upper boarder
		  { DRAW, { 0, -ARENA_LIMIT_LEFT + DRONE_WIDTH_HALF } },
		  { DRAW, { 0, ARENA_LIMIT_RIGHT + DRONE_WIDTH_HALF } },
		  // 96 | 126
		  // right boarder
		  { DRAW, { -ARENA_LIMIT_UP - DRONE_HEIGHT_HALF, 0 } },
		  { DRAW, { ARENA_LIMIT_LOW - DRONE_HEIGHT_HALF, 0 } },
		  // -126 | 126
		  // bottom boarder
		  { DRAW, { 0, -ARENA_LIMIT_RIGHT - DRONE_WIDTH_HALF } },
		  { DRAW, { 0, ARENA_LIMIT_LEFT - DRONE_WIDTH_HALF } },
		  // -126 | -126
		  // left boarder
		  { DRAW, { -ARENA_LIMIT_LOW + DRONE_HEIGHT_HALF, 0 } },
		  { DRAW, { ARENA_LIMIT_UP + DRONE_HEIGHT_HALF, 0 } },
		  // 96 | -126
		  VL_END
	  };

// Generated with VIDE
const signed char drone_vector_list_0[] = {
	(signed char)+0, +7 * BLOW_UP, -3 * BLOW_UP, // move from center
	(signed char)-1, -4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +4 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)+0, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+1 // endmarker (high bit in pattern not set)
};
const signed char drone_vector_list_1[] = {
	(signed char)+0, +8 * BLOW_UP, -5 * BLOW_UP, // move from center
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+0, +3 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +3 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+0, +1 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +3 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+0, +5 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)+0, -3 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+0, -1 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+1 // endmarker (high bit in pattern not set)
};
const signed char drone_vector_list_2[] = {
	(signed char)+0, +7 * BLOW_UP, -7 * BLOW_UP, // move from center
	(signed char)-1, -4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)+0, -4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+1 // endmarker (high bit in pattern not set)
};
const signed char drone_vector_list_3[] = {
	(signed char)+0, +5, -8, // move from center
	(signed char)-1, +0, +6, // pattern, y, x
	(signed char)+0, +0, +4, // pattern, y, x
	(signed char)-1, +0, +6, // pattern, y, x
	(signed char)+0, +0, -3, // pattern, y, x
	(signed char)-1, -2, -2, // pattern, y, x
	(signed char)-1, +0, -6, // pattern, y, x
	(signed char)-1, +2, -2, // pattern, y, x
	(signed char)+0, -2, +2, // pattern, y, x
	(signed char)-1, -6, +0, // pattern, y, x
	(signed char)-1, +0, +6, // pattern, y, x
	(signed char)-1, +6, +0, // pattern, y, x
	(signed char)+0, -6, +0, // pattern, y, x
	(signed char)-1, -2, +2, // pattern, y, x
	(signed char)+0, +0, +3, // pattern, y, x
	(signed char)-1, +0, -6, // pattern, y, x
	(signed char)+0, +0, -4, // pattern, y, x
	(signed char)-1, +0, -6, // pattern, y, x
	(signed char)+0, +0, +3, // pattern, y, x
	(signed char)-1, +2, +2, // pattern, y, x
	(signed char)+1 // endmarker (high bit in pattern not set)
};

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
