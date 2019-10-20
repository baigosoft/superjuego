#include "ball.h"


JF_ball *JF_ball_init(int width,int height,int x,int y,int z)
{

	JF_ball *b;
	b = (JF_ball*)malloc(sizeof(JF_ball));
	b->ball_status = 0;
	b->ball_width = width;
	b->ball_height = height;
	b->ball_x = x;
	b->ball_y = y;
	b->ball_z = z;
	
	return b;

}

void JF_ball_status_set(JF_ball *b,int status)
{

	b->ball_status =  status;

}

void JF_ball_dimentions_set(JF_ball *b,int width,int height)
{

	b->ball_width = width;
	b->ball_height = height;

}

void JF_ball_position_set(JF_ball *b,int x,int y,int z)
{

	b->ball_x = x;
	b->ball_y = y;
	b->ball_z = z;

}

void JF_ball_clean(JF_ball *b)
{

	free(b);

}
