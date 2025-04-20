// ***************************************************************************
// circle
// ***************************************************************************
#if 0
#include "circle.h"

// ---------------------------------------------------------------------------

struct circle_t circle;

// ---------------------------------------------------------------------------

long int full_circle_yx(unsigned int angle)
{
	circle.even.index = angle;
	--angle;
	circle.odd.index = angle;
	if (angle & 0b00000001)
	{
		return *(circle.even.ptr_l);
	}
	else
	{
		return *(circle.odd.ptr_l);
	}
}

// ---------------------------------------------------------------------------

const int* full_circle_yx_adr(unsigned int angle)
{
	circle.even.index = angle;
	--angle;
	circle.odd.index = angle;
	if (angle & 0b00000001)
	{
		return (circle.even.ptr_i);
	}
	else
	{
		return (circle.odd.ptr_i);
	}
}

// ---------------------------------------------------------------------------

int full_circle_sine(unsigned int angle)
{
	circle.odd.index = angle;
	++angle;
	circle.even.index = angle;
	if (angle & 0b00000001)
	{
		return *(circle.even.ptr_i);
	}
	else
	{
		return *(circle.odd.ptr_i);
	}
}

// ---------------------------------------------------------------------------

long int get_circle_yx(unsigned int angle)
{
	return *((const long int*) (((void*) (&(circle_even[0]))) + ((long unsigned int) angle)));
}

// ---------------------------------------------------------------------------

long int even_circle_yx(unsigned int angle)
{
	circle.even.index = angle;
	return *(circle.even.ptr_l);
}

// ---------------------------------------------------------------------------
// deprecated stuff
// ---------------------------------------------------------------------------
#if 0

#if !INLINE_GET_CIRCLE_YX_EXTENDED
long int get_circle_yx_extended(unsigned int angle)
{
	if (angle & 0b00000001)
	{
		return *((const long int*) (((void*) (&(circle_odd[0]))) + ((long unsigned int) (--angle))));
	}
	else
	{
		return *((const long int*) (((void*) (&(circle_even[0]))) + ((long unsigned int) angle)));
	}
}
#endif

// ---------------------------------------------------------------------------

#if !INLINE_GET_CIRCLE_SINE_EXTENDED
int get_circle_sine_extended(unsigned int angle)
{
	if (angle & 0b00000001)
	{
		return *((const int*) (((void*) (&(circle_odd[0]))) + ((long unsigned int) angle)));
	}
	else
	{
		return *((const int*) (((void*) (&(circle_even[0]))) + ((long unsigned int) ++angle)));
	}
}
#endif

#endif
#endif
// ***************************************************************************
// end of file
// ***************************************************************************
