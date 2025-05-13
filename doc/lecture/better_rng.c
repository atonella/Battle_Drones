// ****************************************************************************************
// good 32-bit seed pseudo 8-bit random number generator (rng)
// ****************************************************************************************

#include <stdio.h>

// ----------------------------------------------------------------------------------------
// data type

struct rng_t
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char x;
};

// ---------------------------------------------------------------------------
// set seeds

void init_rng(struct rng_t* p, unsigned char seed0, unsigned char seed1, unsigned char seed2, unsigned char seed3)
{
	p->a = seed0;
	p->b = seed1;
	p->c = seed2;
	p->x = seed3;
}

// ---------------------------------------------------------------------------
// 8-bit random number (full 2^32 period and full range of values 0 - 255)

unsigned int rand(struct rng_t* p)
{
	p->x++;               					//x is incremented every round and is not affected by any other variable
	p->a = (p->a ^ p->c ^ p->x);       		//note the mix of addition and XOR
	p->b = (p->b + p->a);         			//and the use of very few instructions
	p->c = ((p->c + (p->b >> 1)) ^ p->a);	//the right shift is to ensure that high-order bits from b can affect  
	return p->c;          					//low order bits of other variables
}

// ----------------------------------------------------------------------------------------
// usage:

int main(void)
{
	// rng
	struct rng_t my_rng;

	// initialize rng
	init_rng(&my_rng, 47, 11, 42, 1);				// seed values
	
	// lets us keep track of how many times each random value occurs
	unsigned int count[256];
	for (unsigned int i = 0; i < 256; ++i)
	{
		count[i] = 0;	// set count to zero
	}

	// generate 256000 random numbers and count how often each number appears
	for (unsigned int i = 0; i < 256000; ++i)
	{
		unsigned char r = rand(&my_rng);
		++count[r];
	}
	
	// print results, each value from 0 to 255 should appear ~1000 times
	for (unsigned int i = 0; i < 256; ++i)
	{
		printf("value %u: %u x times\n", i, count[i]);
	}
	printf("\n");
}

// ****************************************************************************************
// end of file
// ****************************************************************************************