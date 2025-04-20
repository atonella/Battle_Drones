// ***************************************************************************
// vector
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------
// data structure describing a single vector

struct vector_t
{
	int y; 		// relative y coordinate
	int x; 		// relative x coordinate
};

// ---------------------------------------------------------------------------
// vector drawing modes for packet style vector lists

enum mode_t
{
	MOVE = 0,
	STOP = 1,
	DRAW = 255
};

// ---------------------------------------------------------------------------
// data structure describing a single extended vector

struct packet_t
{
	enum mode_t mode;			// drawing mode
	struct vector_t vector;		// relative vector;
};

struct terminator_t
{
	enum mode_t mode;			// dstop mode
};

// ---------------------------------------------------------------------------
// vector list types

enum list_t
{
	PACKET = 0,		// packet list: each vector has its own drawing mode
	DIFFY = 1,		// vector list: all vectors are drawn
	DUFFY = 2		// vector list: first vector is moved, all others are drawn
};

// ---------------------------------------------------------------------------
// data structure describing a vector list

struct vector_list_t
{
	enum list_t type;	// type of vector list
	unsigned int size;	// length of vector list
	void* vectors;		// generic pointer to array of vectors or packets
};

// ---------------------------------------------------------------------------

#define CONCAT_IMPL(a, x, y, z) a##x##y##x##z
#define MACRO_CONCAT(a, x, y, z) CONCAT_IMPL(a, x, y, z)

#define TERMINATOR 1

#if TERMINATOR
#define VL_END }; static const struct terminator_t MACRO_CONCAT(vl_term, _, __COUNTER__, __LINE__) __attribute__((used)) = { STOP
#define vl_END }; static struct terminator_t MACRO_CONCAT(vl_term, _, __COUNTER__, __LINE__) __attribute__((used))= { STOP
#else
#define VL_END {STOP, { 0, 0}}
#define vl_END {STOP, { 0, 0}}
#endif

// ***************************************************************************
// end of file
// ***************************************************************************
