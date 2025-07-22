// ***************************************************************************
// level
// ***************************************************************************

#pragma once
#include "player.h"
#include "utils/controller.h"
#include "utils/vector.h"
#include <vectrex.h>

#define BLOW_UP 1

// ---------------------------------------------------------------------------

// battle arena size: 213 x 254 (y,x)
const struct packet_t battle_arena[]
	= {
		  // y | x
		  { MOVE, { 80, -127 } },
		  // 80 | -127
		  // upper boarder
		  { DRAW, { 0, 127 } },
		  { DRAW, { 0, 127 } },
		  // 80 | 127
		  // right boarder
		  { DRAW, { -113, 0 } },
		  { DRAW, { -100, 0 } },
		  // -133 | 127
		  // bottom boarder
		  { DRAW, { 0, -127 } },
		  { DRAW, { 0, -127 } },
		  // -133 | -127
		  // left boarder
		  { DRAW, { 100, 0 } },
		  { DRAW, { 113, 0 } },
		  // 80 | -127
		  VL_END
	  };

// Generated with VIDE
const signed char DroneVectorList[] = {
	(signed char)+0, +3 * BLOW_UP, -3 * BLOW_UP, // move from center
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)+0, -2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)+0, -4 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)+0, -6 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+0, +4 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)+0, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +4 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)+1 // endmarker (high bit in pattern not set)
};

const signed char DroneVectorList_0[] = {
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
const signed char DroneVectorList_1[] = {
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
const signed char DroneVectorList_2[] = {
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
const signed char DroneVectorList_3[] = {
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
