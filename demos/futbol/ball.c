#include "ball.h"


ball *ball_init()
{

	ball *b;
	b = (ball*)malloc(sizeof(ball));
	b->ball_status = 0;
	b->ball_width = 0;
	b->ball_height = 0;
	b->ball_x = 0;
	b->ball_y = 0;
	b->ball_z = 0;
	
	return b;

}

void ball_status_set(ball *b,int status)
{

	b->ball_status =  status;

}

void ball_dimentions_set(ball *b,int width,int height)
{

	b->ball_width = width;
	b->ball_height = height;

}

void ball_x(ball *b,int posx)
{

	b->ball_x = posx;

}

void ball_y(ball *b,int posy)
{

	b->ball_y = posy;

}

void ball_z(ball *b,int posz)
{

	b->ball_z = posz;

}

void ball_clean(ball *b)
{

	free(b);

}
