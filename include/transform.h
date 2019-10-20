#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct{

	float x,y,z;
	float width,height;
	float zoomx,zoomy;
	float rotx,roty,rotz;
	float r,g,b;
	float alpha;

}SE_transf;


SE_transf SE_transf_init();

void SE_transf_position_set(SE_transf *tr,float posx,float posy,float posz);
void SE_transf_dimentions_set(SE_transf *tr,float width,float height);
void SE_transf_zoom_set(SE_transf *tr,float zoomx,float zoomy);
void SE_transf_rotation_set(SE_transf *tr,float rotx,float roty,float rotz);
void SE_transf_rgb_set(SE_transf *tr,float red,float green,float blue);
void SE_transf_alpha_set(SE_transf *tr,float alpha);
















#endif
