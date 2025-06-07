// ***************************************************************************
// debug
// ***************************************************************************

#pragma once

#define DEBUG_ENABLED 1

// ---------------------------------------------------------------------------

enum debug_type_t
{
	DEBUG_TYPE_UNSIGNED_INT,
	DEBUG_TYPE_SIGNED_INT,
	DEBUG_TYPE_LONG_UNSIGNED_INT,
	DEBUG_TYPE_LONG_SIGNED_INT,
	DEBUG_TYPE_CHAR,
	DEBUG_TYPE_POINTER,
	DEBUG_TYPE_HEX,
	DEBUG_TYPE_LONG_HEX,
	DEBUG_TYPE_BINARY,
	DEBUG_TYPE_LONG_BINARY,
};
struct input_t;

// ---------------------------------------------------------------------------

void _f_debug(char* text, enum debug_type_t type, void* p_value, char* file, unsigned long int length, unsigned long int line);
void debug_print_input(struct input_t input);

// ***************************************************************************
// end of file
// ***************************************************************************
