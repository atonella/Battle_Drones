// ***************************************************************************
// vectrex cartridge init block - edit to set game title
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------

struct cartridge_t
{
	char copyright[11];			// copyright string, must start with "g GCE" and must end with "\x80"
	const void* music;			// 16 bit memory adress of title music data
	signed int title_height;	// signed 8 bit value, height of game title letters
	unsigned int title_width;	// unsigned 8 bit value, width of game title letters
	int title_y;				// signed 8 bit value, y coordinate of game title
	int title_x;				// signed 8 bit value, x coordinate of game title
	char title[]; 				// game title string, must end with "\x80\x00"
};

// ---------------------------------------------------------------------------

extern const struct cartridge_t game_header;

// ***************************************************************************
// end of file
// ***************************************************************************
