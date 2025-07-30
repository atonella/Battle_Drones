#pragma once

union position_t
{
	struct
	{
		int y;
		int x;
	} coordinates;
	long int yx;
};