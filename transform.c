#include "transform.h"


SE_transf SE_transf_init()
{

	SE_transf tr;

	tr.x = 0;	
	tr.y = 0;
	tr.z = 0;
	tr.width = 0;
	tr.height = 0;
	tr.zoomx = 1;	
	tr.zoomy = 1;
	tr.rotx = 0;	
	tr.roty = 0;		
	tr.rotz = 0;
	tr.r = 1;
	tr.g = 1;
	tr.b = 1;
	tr.alpha = 1;	

	return tr;							
			
}

void SE_transf_position_set(SE_transf *tr,float posx,float posy,float posz)
{

	tr->x = posx;	
	tr->y = posy;
	tr->z = posz;

}

void SE_transf_dimentions_set(SE_transf *tr,float width,float height)
{

	tr->width = width;
	tr->height = height;

}

void SE_transf_zoom_set(SE_transf *tr,float zoomx,float zoomy)
{

	tr->zoomx = zoomx;
	tr->zoomy = zoomy;

}

void SE_transf_rotation_set(SE_transf *tr,float rotx,float roty,float rotz)
{

	tr->rotx = rotx;	
	tr->roty = roty;
	tr->rotz = rotz;

}

void SE_transf_rgb_set(SE_transf *tr,float red,float green,float blue)
{

	tr->r = red;
	tr->g = green;
	tr->b = blue;

}

void SE_transf_alpha_set(SE_transf *tr,float alpha)
{

	tr->alpha = alpha;

}








