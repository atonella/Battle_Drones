// ****************************************************************************************
// simple 8-bit linear feedback shift register (lsfr) pseudo random number generator (rng)
// ****************************************************************************************

#include <stdio.h>

// ----------------------------------------------------------------------------------------
// data type

struct simple_rng_t
{
	unsigned char lsfr;	// current random value
	unsigned char tabs;	// xor bits
};

// ----------------------------------------------------------------------------------------
// initialize rng and set initial seed (first value to be returnd)

unsigned char init_simple_rng(struct simple_rng_t* p, unsigned char seed)
{
	p->lsfr = seed;
	p->tabs = 0b10111000;  // this will produce the maximum period of 255 values (1 - 255)
}

// ----------------------------------------------------------------------------------------
// 8-bit pseudo random numbers (note that the random number will never be zero!)

unsigned char simple_rand(struct simple_rng_t* p)
{
	unsigned char random = p->lsfr;

	unsigned char lsb = p->lsfr & 0b00000001;
	p->lsfr >>= 1;
	if (lsb) p->lsfr ^= p->tabs;
	
	return random;
}

// ----------------------------------------------------------------------------------------
// usage:

int main(void)
{
	struct simple_rng_t	my_rng;
	init_simple_rng(&my_rng, 42);				// seed value

	// show 256 random numbers, last and first will be idential (the cycle repeats)
	for (long int i = 0; i < 256; ++i)
	{
		unsigned char r = simple_rand(&my_rng);
		printf("%u, ", r);
	}
		
}

// ****************************************************************************************
// end of file
// ****************************************************************************************