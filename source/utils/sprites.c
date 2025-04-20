// ***************************************************************************
// sprites
// ***************************************************************************

#include "../system/vectrex.h"
#include "sprites.h"

// ---------------------------------------------------------------------------
#if 0
void draw_sprite(const struct sprite* s) 
{
	if (s->angle != 0)
	{	
		if (s->shape->type == TYPE_PACKET)
		{
			volatile struct sprite_packet r[s->shape->size];
			Rot_VL_Mode(s->angle, s->shape->vectors, &r);
			Reset0Ref_D0();
			Moveto_d_7F(s->y, s->x);
			Draw_VLp_b(s->scale, &r);
		}
		else if (s->shape->type == TYPE_MODE)
		{
			volatile struct sprite_packet r[s->shape->size];
			Rot_VL_Mode(s->angle, s->shape->vectors, &r);
			Reset0Ref_D0();
			Moveto_d_7F(s->y, s->x);
			VIA_t1_cnt_lo = s->scale;
			Vec_Pattern = *((unsigned int*) s->shape->vectors + (s->shape->size * 3) - 1);
			Draw_VL_mode(&r); // uses the pattern stored in 0xc829
		}
		else if (s->shape->type == TYPE_PATTERN)
		{
			volatile struct sprite_packet r[s->shape->size];
			Rot_VL_Mode(s->angle, s->shape->vectors, &r);
			Reset0Ref_D0();
			Moveto_d_7F(s->y, s->x);
			VIA_t1_cnt_lo = s->scale;
			Vec_Pattern = *((unsigned int*) s->shape->vectors + (s->shape->size * 3) - 1);
			Draw_VLp(&r); // uses the pattern stored in 0xc829
		}
		else
		{
			volatile struct sprite_vector r[s->shape->size];
			Rot_VL_ab(s->angle, s->shape->size - 1, s->shape->vectors, &r);
			Reset0Ref_D0();
			Moveto_d_7F(s->y, s->x);

			if (s->shape->type == TYPE_DIFFY)
			{
				Draw_VL_ab(s->shape->size - 1, s->scale, &r);
			}
			else
			{
				Mov_Draw_VL_ab(s->shape->size - 1, s->scale, &r);
			}
		}
	}
	else
	{
		Reset0Ref_D0();
		Moveto_d_7F(s->y, s->x);

		switch(s->shape->type)
		{
		case TYPE_PACKET:
			Draw_VLp_b(s->scale, s->shape->vectors);
			break;
		case TYPE_MODE:
			VIA_t1_cnt_lo = s->scale;
			Vec_Pattern = *((unsigned int*) s->shape->vectors + (s->shape->size * 3) - 1);
			Draw_VL_mode(s->shape->vectors); // uses the pattern stored in 0xc829
			break;
		case TYPE_PATTERN:
			VIA_t1_cnt_lo = s->scale;
			Draw_VLp(s->shape->vectors);
			break;
		case TYPE_DIFFY:
			Draw_VL_ab(s->shape->size - 1, s->scale, s->shape->vectors);
			break;
		case TYPE_DUFFY:
			Mov_Draw_VL_ab(s->shape->size - 1, s->scale, s->shape->vectors);
			break;
		default:
			break;
		}
	}
}
#endif

// ***************************************************************************
// end of file
// ***************************************************************************
