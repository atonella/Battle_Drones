#pragma once
// data type

struct rng_t
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char x;
};
struct rng_t bot_rng;

void init_rng(struct rng_t* p, unsigned char seed0, unsigned char seed1, unsigned char seed2, unsigned char seed3);
unsigned int rand(struct rng_t* p);
