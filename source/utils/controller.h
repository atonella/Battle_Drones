// ***************************************************************************
// controller
// ***************************************************************************

#pragma once
#include <vectrex.h>

// ---------------------------------------------------------------------------
// controller initialization, each controller axis can be individually
// switched on or off; for performance reasons, activate only what you
// really need

static inline __attribute__((always_inline)) 
void enable_controller_1_x(void)
{
		Vec_Joy_Mux_1_X = 1;
}

static inline __attribute__((always_inline)) 
void enable_controller_1_y(void)
{
		Vec_Joy_Mux_1_Y = 3;
}

static inline __attribute__((always_inline)) 
void enable_controller_2_x(void)
{
		Vec_Joy_Mux_2_X = 5;
}

static inline __attribute__((always_inline)) 
void enable_controller_2_y(void)
{
		Vec_Joy_Mux_2_Y = 7;
}

static inline __attribute__((always_inline)) 
void disable_controller_1_x(void)
{
		Vec_Joy_Mux_1_X = 0;
}

static inline __attribute__((always_inline)) 
void disable_controller_1_y(void)
{
		Vec_Joy_Mux_1_Y = 0;
}

static inline __attribute__((always_inline)) 
void disable_controller_2_x(void)
{
		Vec_Joy_Mux_2_X = 0;
}

static inline __attribute__((always_inline)) 
void disable_controller_2_y(void)
{
		Vec_Joy_Mux_2_Y = 0;
}

// ---------------------------------------------------------------------------
// read controller buttons

// must be called once each time you want to check the buttons
static inline __attribute__((always_inline)) 
void check_buttons(void)
{
	Read_Btns();
}

static inline __attribute__((always_inline)) 
unsigned int buttons_pressed(void)
{
	return Vec_Buttons;
}

static inline __attribute__((always_inline)) 
unsigned int buttons_held(void)
{
	return Vec_Btn_State;
}

// call these functions below to check if a specific button is pressed,
// the button must be released before another press is registered,
// return value is 0 or 1, so these functions can be used as check in
// conditional statements

static inline __attribute__((always_inline)) 
unsigned int button_1_1_pressed(void)
{
	return (buttons_pressed() & 0b00000001);
}

static inline __attribute__((always_inline)) 
unsigned int button_1_2_pressed(void)
{
	return (buttons_pressed() & 0b00000010);
}
static inline __attribute__((always_inline)) 
unsigned int button_1_3_pressed(void)
{
	return (buttons_pressed() & 0b00000100);
}
static inline __attribute__((always_inline)) 
unsigned int button_1_4_pressed(void)
{
	return (buttons_pressed() & 0b00001000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_1_pressed(void)
{
	return (buttons_pressed() & 0b00010000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_2_pressed(void)
{
	return (buttons_pressed() & 0b00100000);
}
static inline __attribute__((always_inline)) 
unsigned int button_2_3_pressed(void)
{
	return (buttons_pressed() & 0b01000000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_4_pressed(void)
{
	return (buttons_pressed() & 0b10000000);
}

// call these functions below to check if a specific button is held,
// return value is 0 or 1, so these functions can be used as check in
// conditional statements

static inline __attribute__((always_inline)) 
unsigned int button_1_1_held(void)
{
	return (buttons_held() & 0b00000001);
}

static inline __attribute__((always_inline)) 
unsigned int button_1_2_held(void)
{
	return (buttons_held() & 0b00000010);
}
static inline __attribute__((always_inline)) 
unsigned int button_1_3_held(void)
{
	return (buttons_held() & 0b00000100);
}
static inline __attribute__((always_inline)) 
unsigned int button_1_4_held(void)
{
	return (buttons_held() & 0b00001000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_1_held(void)
{
	return (buttons_held() & 0b00010000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_2_held(void)
{
	return (buttons_held() & 0b00100000);
}
static inline __attribute__((always_inline)) 
unsigned int button_2_3_held(void)
{
	return (buttons_held() & 0b01000000);
}

static inline __attribute__((always_inline)) 
unsigned int button_2_4_held(void)
{
	return (buttons_held() & 0b10000000);
}

// ---------------------------------------------------------------------------
// read controller joysticks

// must be called once each time you want to check the joysticks
static inline __attribute__((always_inline)) 
void check_joysticks(void)
{
	Joy_Digital();
}

static inline __attribute__((always_inline)) 
int joystick_1_x(void)
{
	return Vec_Joy_1_X;
}

static inline __attribute__((always_inline)) 
int joystick_1_y(void)
{
	return Vec_Joy_1_Y;
}

static inline __attribute__((always_inline)) 
int joystick_2_x(void)
{
	return Vec_Joy_2_X;
}

static inline __attribute__((always_inline)) 
int joystick_2_y(void)
{
	return Vec_Joy_2_Y;
}

// call these functions below to check if a joystick is moved in
// a specific direction,
// return value is 0 or 1, so these functions can be used as check in
// conditional statements

static inline __attribute__((always_inline)) 
int joystick_1_left(void)
{
	return (joystick_1_x() < 0);
}

static inline __attribute__((always_inline)) 
int joystick_1_right(void)
{
	return (joystick_1_x() > 0);
}

static inline __attribute__((always_inline)) 
int joystick_1_down(void)
{
	return (joystick_1_y() < 0);
}

static inline __attribute__((always_inline)) 
int joystick_1_up(void)
{
	return (joystick_1_y() > 0);
}

static inline __attribute__((always_inline)) 
int joystick_2_left(void)
{
	return (joystick_2_x() < 0);
}

static inline __attribute__((always_inline)) 
int joystick_2_right(void)
{
	return (joystick_2_x() > 0);
}

static inline __attribute__((always_inline)) 
int joystick_2_down(void)
{
	return (joystick_2_y() < 0);
}

static inline __attribute__((always_inline)) 
int joystick_2_up(void)
{
	return (joystick_2_y() > 0);
}

// ***************************************************************************
// end of file
// ***************************************************************************
