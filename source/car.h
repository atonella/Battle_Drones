#pragma once
#include "utils/vector.h" // provides a C data type for vector lists

struct car_t
{
	unsigned int y;
	unsigned int x;
	// unsigned int health;
	unsigned int velocity;
	unsigned int scaling_factor;
};

// TODO: maybe move to battle.h and player.h
const struct packet_t vectors_battle_car[]
	= {
		  { MOVE, { 0, 0 } },
		  { DRAW, { 0, 25 } }, // front (i/ii)
		  { DRAW, { -15, 0 } }, // front, side, right
		  { DRAW, { -5, 3 } }, // tire
		  { DRAW, { -5, 0 } }, // tire
		  { DRAW, { -5, -3 } }, // tire
		  { DRAW, { -20, 0 } }, // side, right
		  { DRAW, { -5, 3 } }, // tire
		  { DRAW, { -5, 0 } }, // tire
		  { DRAW, { -5, -3 } }, // tire
		  { DRAW, { -10, 0 } }, // rear, side, right
		  { DRAW, { 0, -50 } }, // rear
		  { DRAW, { 10, 0 } }, // rear, side, left
		  { DRAW, { 5, -3 } }, // tire
		  { DRAW, { 5, 0 } }, // tire
		  { DRAW, { 5, 3 } }, // tire
		  { DRAW, { 20, 0 } }, // side left
		  { DRAW, { 5, -3 } }, // tire
		  { DRAW, { 5, 0 } }, // tire
		  { DRAW, { 5, 3 } }, // tire
		  { DRAW, { 15, 0 } }, // front, side, left
		  { DRAW, { 0, 25 } }, // front (ii/ii)
		  { MOVE, { -25, 0 } }, // Player 1 identifier
		  // circle
		  { DRAW, { 0, 3 } },
		  { DRAW, { -3, 3 } },
		  { DRAW, { -6, 0 } },
		  { DRAW, { -3, -3 } },
		  { DRAW, { 0, -6 } },
		  { DRAW, { 3, -3 } },
		  { DRAW, { 6, 0 } },
		  { DRAW, { 3, 3 } },

		  { DRAW, { 0, 3 } },
		  // canon
		  { MOVE, { 25, 0 } },
		  { DRAW, { 7, 0 } },
		  { STOP, { 0, 0 } },
	  };
