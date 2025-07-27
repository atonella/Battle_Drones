#pragma once
// data type

struct rng_t
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char x;
};
struct rng_t bot_rng; // bot behavior
struct rng_t respawn_pos_rng; // player respawn location

void init_rng(struct rng_t* p, unsigned char seed0, unsigned char seed1, unsigned char seed2, unsigned char seed3);
unsigned int rand(struct rng_t* p);
