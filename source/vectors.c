#include "battle.h"

// battle arena size: 222 x 252 (y,x)
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
	(signed char)+0, +5 * BLOW_UP, -8 * BLOW_UP, // move from center
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, +4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, -3 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, -2 * BLOW_UP, // pattern, y, x
	(signed char)+0, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)-1, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, +6 * BLOW_UP, // pattern, y, x
	(signed char)-1, +6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)+0, -6 * BLOW_UP, +0 * BLOW_UP, // pattern, y, x
	(signed char)-1, -2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, +3 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, -4 * BLOW_UP, // pattern, y, x
	(signed char)-1, +0 * BLOW_UP, -6 * BLOW_UP, // pattern, y, x
	(signed char)+0, +0 * BLOW_UP, +3 * BLOW_UP, // pattern, y, x
	(signed char)-1, +2 * BLOW_UP, +2 * BLOW_UP, // pattern, y, x
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