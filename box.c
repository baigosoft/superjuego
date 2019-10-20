#include "box.h"

SE_box SE_box_init(float posx,float posy,float width,float height)
{

	SE_box box;

	box.x = posx;
	box.y = posy;
	box.w = width;
	box.h = height;

	return box;

}

void SE_box_position_set(SE_box *box,float posx,float posy)
{

	box->x = posx;
	box->y = posy;

}


void SE_box_dimentions_set(SE_box *box,float width,float height)
{

	box->w = width;
	box->h = height;

}
