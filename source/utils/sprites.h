// ***************************************************************************
// sprites
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------
// data structure describing a single vector

struct sprite_vector
{
	volatile int dy;	// relative y coordinate
	volatile int dx;	// relative x coordinate
};

// ---------------------------------------------------------------------------
// vector drawing modes

enum sprite_vector_mode
{
	MODE_MOVE = 0,
	MODE_STOP = 1,
	MODE_SOLID = 2,  // does not work with rotations!!!
	MODE_DRAW = 255
};

// ---------------------------------------------------------------------------
// data structure describing a single extended vector

struct sprite_packet
{
	enum sprite_vector_mode mode;	// drawing mode
	struct sprite_vector vector;	// relative vector;
};

// ---------------------------------------------------------------------------
// vector list (array of vectors or packets) types:

enum sprite_vector_list_type
{
	TYPE_PACKET = 0,	// packet list: each vector is either moved or drawn (solid)
	TYPE_MODE = 1,		// mode list: each vector is either moved or drawn (pattern)
	TYPE_PATTERN = 2,	// pattern list: each vector has its own pattern
	TYPE_DIFFY = 3,		// vector list: all vectors are drawn
	TYPE_DUFFY = 4 		// vector list: first vector is moved, all others are drawn
};

// ---------------------------------------------------------------------------
// data structure describing a vector list

struct sprite_shape
{
	enum sprite_vector_list_type type;	// type of vector list
	unsigned int size;					// length of vector list
	void* vectors;						// pointer to array of vectors or packets
};

// ---------------------------------------------------------------------------
// sprite life cycle state types:

enum sprite_state
{
	STATE_OFF = 0,
	STATE_BIRTH = 1,
	STATE_ALIVE = 2,
	STATE_DEATH = 3
};

// ---------------------------------------------------------------------------
// data structure describing a sprite

struct sprite
{
	int y;								// y coordinate
	int x;								// x coordinate
	unsigned int angle;					// rotational angle (lower 6 bits)
	unsigned int scale;					// scale factor
	const struct sprite_shape* shape;	// pointer to vector list
	enum sprite_state state;			// life cycle state
	unsigned int counter;				// life cycle counter
	unsigned int move;
	int dy;
	int dx;
};

// ---------------------------------------------------------------------------

void draw_sprite(const struct sprite* s);

// ***************************************************************************
// end of file sprites.h
// ***************************************************************************
