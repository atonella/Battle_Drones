// ***************************************************************************
// utility functions
// ***************************************************************************

#pragma once
#include <vectrex.h>
#include "sound.h"

// ---------------------------------------------------------------------------
// scale factor used for all absolute sprite coordinates

#define GRID_SCALE 0x7F

// ---------------------------------------------------------------------------
// position vector beam at absolute sprite coordinates

static inline __attribute__((always_inline))
void reset_beam(void)
{
	Reset0Ref();
}

static inline __attribute__((always_inline)) 
void scale_beam(const unsigned int scale)
{
	dp_VIA_t1_cnt_lo = scale;
}

static inline __attribute__((always_inline)) 
void position_beam(const int y, const int x)
{
	reset_beam();
	scale_beam(GRID_SCALE);
	Moveto_d(y, x);
}

static inline __attribute__((always_inline)) 
void position_beam_yx(const long int yx)
{
	reset_beam();
	scale_beam(GRID_SCALE);
	Moveto_dd(yx);
}

static inline __attribute__((always_inline)) 
void position_beam_s(const int y, const int x, const unsigned int scale)
{
	reset_beam();
	scale_beam(scale);
	Moveto_d(y, x);
}

static inline __attribute__((always_inline)) 
void position_beam_yxs(const long int yx, const unsigned int scale)
{
	reset_beam();
	scale_beam(scale);
	Moveto_dd(yx);
}

static inline __attribute__((always_inline))
void recalibrate(void)
{
	Recalibrate();
}

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline)) 
void sync()
{
	// game loop header start - do not change
	DP_to_C8();
	Explosion_Snd(current_explosion);
	Init_Music_chk(current_music);
	Wait_Recal();
	Do_Sound();
	// game loop header end
}

// ---------------------------------------------------------------------------
// workaround: gcc6809 cannot handle shift by non-constant int (long int works)

static inline __attribute__((always_inline)) 
unsigned int shift_left(unsigned int operand, unsigned int bits)
{ 
	return (unsigned int) ((long unsigned int) operand << (long unsigned int) bits);
}

static inline __attribute__((always_inline)) 
unsigned int shift_right(unsigned int operand, unsigned int bits)
{ 
	return (unsigned int) ((long unsigned int) operand >> (long unsigned int) bits);
}

static inline __attribute__((always_inline)) 
int rotate_left(int operand, unsigned int bits)
{ 
	return (int) ((long int) operand << (long unsigned int) bits);
}

static inline __attribute__((always_inline)) 
int roate_right(int operand, unsigned int bits)
{ 
	return (int) ((long int) operand >> (long unsigned int) bits);
}

// ---------------------------------------------------------------------------
// workaround: gcc6809 cannot handle division by non-constant int (long int works)

static inline __attribute__((always_inline)) 
unsigned int divu(unsigned int dividend, unsigned int divisor)
{ 
	return (unsigned int) ((long unsigned int) dividend / (long unsigned int) divisor);
}

static inline __attribute__((always_inline)) 
int divs(int dividend, int divisor)
{ 
	return (int) ((long int) dividend / (long int) divisor);
}
// ---------------------------------------------------------------------------
// text settings

#define TEXT_HEIGHT_L	-8	// 0xF8
#define TEXT_HEIGHT_C	-8	// 0xF8
#define TEXT_HEIGHT_G	-7	// 0xF9
#define TEXT_HEIGHT_M	-7	// 0xF9
#define TEXT_HEIGHT_S	-6  // 0xFA

#define TEXT_WIDTH_L	80	// 0x50
#define TEXT_WIDTH_C	72	// 0x48
#define TEXT_WIDTH_G	72	// 0x48
#define TEXT_WIDTH_M	60	// 0x3C
#define TEXT_WIDTH_S	40	// 40	// 0x28

static inline __attribute__((always_inline)) 
void set_text_large(void)
{ 
	Vec_Text_HW = (unsigned long int) (((unsigned long int)((unsigned int) TEXT_HEIGHT_L)) * 256L + ((unsigned int) TEXT_WIDTH_L));
}

static inline __attribute__((always_inline)) 
void set_text_copyright(void)
{ 
	Vec_Text_HW = (unsigned long int) (((unsigned long int)((unsigned int) TEXT_HEIGHT_C)) * 256L + ((unsigned int) TEXT_WIDTH_C));
}

static inline __attribute__((always_inline)) 
void set_text_copyright_mb(void)
{ 
	Vec_Text_HW = (unsigned long int) (((unsigned long int)((unsigned int) TEXT_HEIGHT_G)) * 256L + ((unsigned int) TEXT_WIDTH_G));
}

static inline __attribute__((always_inline)) 
void set_text_medium(void)
{ 
	Vec_Text_HW = (unsigned long int) (((unsigned long int)((unsigned int) TEXT_HEIGHT_M)) * 256L + ((unsigned int) TEXT_WIDTH_M));
}

static inline __attribute__((always_inline)) 
void set_text_small(void)
{ 
	Vec_Text_HW = (unsigned long int) (((unsigned long int)((unsigned int) TEXT_HEIGHT_S)) * 256L + ((unsigned int) TEXT_WIDTH_S));
}

#define CENTER_TEXT(width, length) (-((int)(((18.0*width*(length + 1.0))/2.0) / 127.0)))

// ---------------------------------------------------------------------------
// scale factor used for all absolute sprite coordinates

extern const int angle2dx[];
extern const int angle2dy[];

static inline __attribute__((always_inline))int angle_to_dx(unsigned int angle)
{
	return angle2dx[angle >> 1];
}

static inline __attribute__((always_inline))int angle_to_dy(unsigned int angle)
{
	return angle2dy[angle >> 1];
}

// ***************************************************************************
// end of file
// ***************************************************************************
