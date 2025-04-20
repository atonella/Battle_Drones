// ***************************************************************************
// circle
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------

extern const int circle_even[];
extern const int circle_odd[];

// ---------------------------------------------------------------------------

struct magic_pointer_t
{
	union
	{
		struct
		{
			unsigned int page;
			unsigned int index;
		};
		const int* ptr_i;
		const long int* ptr_l;
	};
};

// ---------------------------------------------------------------------------

struct circle_t
{
	struct magic_pointer_t even;
	struct magic_pointer_t odd;
};

// ---------------------------------------------------------------------------

extern struct circle_t circle;

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
void inline_init_circle(void)
{
	circle.even.page = 0x01;
	circle.odd.page = 0x02;
}

// ---------------------------------------------------------------------------

long int full_circle_yx(unsigned int angle);

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
long int inline_full_circle_yx(unsigned int angle)
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

const int* full_circle_yx_adr(unsigned int angle);

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
const int* inline_full_circle_yx_adr(unsigned int angle)
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

int full_circle_sine(unsigned int angle);

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
int inline_full_circle_sine(unsigned int angle)
{
	circle.odd.index = angle;
	++angle;
	circle.even.index = angle;
	if (angle & 0b00000001)
	{
		return *(circle.odd.ptr_i);
	}
	else
	{
		return *(circle.even.ptr_i);
	}
}

// ---------------------------------------------------------------------------

long int get_circle_yx(unsigned int angle);

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
long int inline_get_circle_yx(unsigned int angle)
{
	return *((const long int*) (((void*) (&(circle_even[0]))) + ((long unsigned int) angle)));
}

// ---------------------------------------------------------------------------

long int even_circle_yx(unsigned int angle);

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
long int inline_even_circle_yx(unsigned int angle)
{
	circle.even.index = angle;
	return *(circle.even.ptr_l);
}

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
const int* get_circle_yx_adr(unsigned int angle)
{
	return ((&(circle_even[0])) + ((long unsigned int) angle));
}

// ---------------------------------------------------------------------------
// unused stuff
// ---------------------------------------------------------------------------

#if 0
static inline __attribute__((always_inline))
long int get_circle_yx_w(long unsigned int angle_w)
{
	return *((const long int*) (((void*) (&(circle[0]))) + angle_w));
}
#endif

// ---------------------------------------------------------------------------

#if 0
static inline __attribute__((always_inline))
int get_circle_sin(unsigned int angle)
{
	union signed_word_t
	{
		struct
		{
			int h;		// y coordinate byte
			int l;		// x coordinate byte
		};
		long int w;		// yx coordinate word
	};
	
	union signed_word_t w;
	w.w = get_circle_yx(angle);
	return w.l;
}
#endif

// ---------------------------------------------------------------------------

#if 0
static inline __attribute__((always_inline))
int get_circle_cos(unsigned int angle)
{
	union signed_word_t
	{
		struct
		{
			int h;		// y coordinate byte
			int l;		// x coordinate byte
		};
		long int w;		// yx coordinate word
	};
	
	union signed_word_t w;
	w.w = get_circle_yx(angle);
	return w.h;
}
#endif 


// ---------------------------------------------------------------------------
// deprecated stuff!
// ---------------------------------------------------------------------------
#if 0
#define INLINE_GET_CIRCLE_YX_EXTENDED 0
#define INLINE_GET_CIRCLE_SINE_EXTENDED 0

#if INLINE_GET_CIRCLE_YX_EXTENDED
static inline __attribute__((always_inline))
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
#else
long int get_circle_yx_extended(unsigned int angle);
#endif

// ---------------------------------------------------------------------------
// make this a function, speed up code by using pointers

static inline __attribute__((always_inline))
const int* get_circle_yx_adr_extended(unsigned int angle)
{
	if (angle & 0b00000001)
	{
		return ((&(circle_odd[0])) + ((long unsigned int) (--angle)));
	}
	else
	{
		return ((&(circle_even[0])) + ((long unsigned int) angle));
	}
}
// ---------------------------------------------------------------------------

#if INLINE_GET_CIRCLE_SINE_EXTENDED
static inline __attribute__((always_inline))
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
#else
int get_circle_sine_extended(unsigned int angle);
#endif


#endif
// ***************************************************************************
// end of file
// ***************************************************************************
