#include "collision.h"


float SE_box_width(SE_box *box)
{

	return box->w;

}

void SE_box_width_set(SE_box *box,float width)
{

	box->w = width;

}

float SE_box_heigth(SE_box *box)
{

	return box->h;

}

void SE_box_height_set(SE_box *box,float height)
{

	box->h = height;

}

void SE_box_dimentions_set(SE_box *box,float width,float height)
{

	SE_box_width_set(box,width);
	SE_box_height_set(box,height);

}


float SE_box_x(SE_box *box)
{

	return box->x;

}

void SE_box_x_set(SE_box *box,float posx)
{

	box->x = posx;

}

float SE_box_y(SE_box *box)
{

	return box->y;

}

void SE_box_y_set(SE_box *box,float posy)
{

	box->y = posy;

}

void SE_box_position_set(SE_box *box,float posx,float posy)
{

	SE_box_x_set(box,posx);
	SE_box_y_set(box,posy);	

}


int SE_box_check_position(SE_box *box1,SE_box *box2,float posx1,float posy1,float posx2,float posy2)
{

	float left1,left2;
	float right1,right2;
	float bottom1,bottom2;
	float top1,top2;

	
	left1 = posx1 + box1->x;
	right1 = left1 + box1->w;
	top1 = posy1 + box1->y;
	bottom1 = top1 + box1->h;

	left2 = posx2 + box2->x;
	right2 = left2 + box2->w;
	top2 = posy2 + box2->y;
	bottom2 = top2 + box2->h;

	
	if(bottom1 <= top2)return 0;
	
	
	if(top1 >= bottom2)return 0;

	
	if(right1 <= left2)return 0;
	
	
	if(left1 >= right2)return 0;


	return 1;
	


}

int SE_box_check(SE_box *box1,SE_box *box2)
{

	SE_box_check_position(box1,box2,0,0,0,0);

}
