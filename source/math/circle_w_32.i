// ***************************************************************************
// circle
// ***************************************************************************

#include "math.h"

// ---------------------------------------------------------------------------

#undef RADIUS
#define RADIUS 127

// ---------------------------------------------------------------------------
// page alignment

__asm(
	".area .text\n\t"
	".bndry 256\n\t"
);

// ---------------------------------------------------------------------------
// table of 16-bit cos / sin pairs for full circle with 64 entries
// 64 word-size entry pairs (256 bytes)

const int CIRCLE_W_64_NAME[] = 
{
	(long int) (cos_0  * RADIUS),		(long int) (sin_0  * RADIUS),	
	(long int) (cos_4  * RADIUS),		(long int) (sin_4  * RADIUS),	
	(long int) (cos_8  * RADIUS),		(long int) (sin_8  * RADIUS),	
	(long int) (cos_12 * RADIUS),		(long int) (sin_12 * RADIUS),	

	(long int) (cos_16 * RADIUS),		(long int) (sin_16 * RADIUS),	
	(long int) (cos_20 * RADIUS),		(long int) (sin_20 * RADIUS),	
	(long int) (cos_24 * RADIUS),		(long int) (sin_24 * RADIUS),	
	(long int) (cos_28 * RADIUS),		(long int) (sin_28 * RADIUS),	

	(long int) (cos_32 * RADIUS),		(long int) (sin_32 * RADIUS),	
	(long int) (cos_36 * RADIUS),		(long int) (sin_36 * RADIUS),	
	(long int) (cos_40 * RADIUS),		(long int) (sin_40 * RADIUS),	
	(long int) (cos_44 * RADIUS),		(long int) (sin_44 * RADIUS),	

	(long int) (cos_48 * RADIUS),		(long int) (sin_48 * RADIUS),	
	(long int) (cos_52 * RADIUS),		(long int) (sin_52 * RADIUS),	
	(long int) (cos_56 * RADIUS),		(long int) (sin_56 * RADIUS),	
	(long int) (cos_60 * RADIUS),		(long int) (sin_60 * RADIUS),	

	(long int) (cos_64 * RADIUS),		(long int) (sin_64 * RADIUS),	
	(long int) (cos_68 * RADIUS),		(long int) (sin_68 * RADIUS),	
	(long int) (cos_72 * RADIUS),		(long int) (sin_72 * RADIUS),	
	(long int) (cos_76 * RADIUS),		(long int) (sin_76 * RADIUS),	

	(long int) (cos_80 * RADIUS),		(long int) (sin_80 * RADIUS),	
	(long int) (cos_84 * RADIUS),		(long int) (sin_84 * RADIUS),	
	(long int) (cos_88 * RADIUS),		(long int) (sin_88 * RADIUS),	
	(long int) (cos_92 * RADIUS),		(long int) (sin_92 * RADIUS),	

	(long int) (cos_96 * RADIUS),		(long int) (sin_96 * RADIUS),	
	(long int) (cos_100 * RADIUS),		(long int) (sin_100 * RADIUS),	
	(long int) (cos_104 * RADIUS),		(long int) (sin_104 * RADIUS),	
	(long int) (cos_108 * RADIUS),		(long int) (sin_108 * RADIUS),	

	(long int) (cos_112 * RADIUS),		(long int) (sin_112 * RADIUS),	
	(long int) (cos_116 * RADIUS),		(long int) (sin_116 * RADIUS),	
	(long int) (cos_120 * RADIUS),		(long int) (sin_120 * RADIUS),	
	(long int) (cos_124 * RADIUS),		(long int) (sin_124 * RADIUS),	

	(long int) (cos_128 * RADIUS),		(long int) (sin_128 * RADIUS),	
	(long int) (cos_132 * RADIUS),		(long int) (sin_132 * RADIUS),	
	(long int) (cos_136 * RADIUS),		(long int) (sin_136 * RADIUS),	
	(long int) (cos_140 * RADIUS),		(long int) (sin_140 * RADIUS),	

	(long int) (cos_144 * RADIUS),		(long int) (sin_144 * RADIUS),	
	(long int) (cos_148 * RADIUS),		(long int) (sin_148 * RADIUS),	
	(long int) (cos_152 * RADIUS),		(long int) (sin_152 * RADIUS),	
	(long int) (cos_156 * RADIUS),		(long int) (sin_156 * RADIUS),	

	(long int) (cos_160 * RADIUS),		(long int) (sin_160 * RADIUS),	
	(long int) (cos_164 * RADIUS),		(long int) (sin_164 * RADIUS),	
	(long int) (cos_168 * RADIUS),		(long int) (sin_168 * RADIUS),	
	(long int) (cos_172 * RADIUS),		(long int) (sin_172 * RADIUS),	

	(long int) (cos_176 * RADIUS),		(long int) (sin_176 * RADIUS),	
	(long int) (cos_180 * RADIUS),		(long int) (sin_180 * RADIUS),	
	(long int) (cos_184 * RADIUS),		(long int) (sin_184 * RADIUS),	
	(long int) (cos_188 * RADIUS),		(long int) (sin_188 * RADIUS),	

	(long int) (cos_192 * RADIUS),		(long int) (sin_192 * RADIUS),	
	(long int) (cos_196 * RADIUS),		(long int) (sin_196 * RADIUS),	
	(long int) (cos_200 * RADIUS),		(long int) (sin_200 * RADIUS),	
	(long int) (cos_204 * RADIUS),		(long int) (sin_204 * RADIUS),	

	(long int) (cos_208 * RADIUS),		(long int) (sin_208 * RADIUS),	
	(long int) (cos_212 * RADIUS),		(long int) (sin_212 * RADIUS),	
	(long int) (cos_216 * RADIUS),		(long int) (sin_216 * RADIUS),	
	(long int) (cos_220 * RADIUS),		(long int) (sin_220 * RADIUS),	

	(long int) (cos_224 * RADIUS),		(long int) (sin_224 * RADIUS),	
	(long int) (cos_228 * RADIUS),		(long int) (sin_228 * RADIUS),	
	(long int) (cos_232 * RADIUS),		(long int) (sin_232 * RADIUS),	
	(long int) (cos_236 * RADIUS),		(long int) (sin_236 * RADIUS),	

	(long int) (cos_240 * RADIUS),		(long int) (sin_240 * RADIUS),	
	(long int) (cos_244 * RADIUS),		(long int) (sin_244 * RADIUS),	
	(long int) (cos_248 * RADIUS),		(long int) (sin_248 * RADIUS),	
	(long int) (cos_252 * RADIUS),		(long int) (sin_252 * RADIUS),	
};

// ***************************************************************************
// end of file
// ***************************************************************************
