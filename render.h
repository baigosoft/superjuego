#ifndef RENDER_H_
#define RENDER_H_


#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"
#include "SDL_image.h"
#include "utils.h"

typedef struct{

	float x,y,z;
	float width,height;
	float zoomx,zoomy;
	float rotx,roty,rotz;
	float r,g,b;
	float alpha;

}SE_transf;

void SE_screen_fullscreen(int fs);
int SE_screen_init(int width,int height,int bpp);
void SE_screen_enable2d();
void SE_screen_disable2d();
void SE_screen_clear(float r,float g,float b,float a);
void SE_screen_flip();
void SE_screen_rotate(float rotx,float roty,float rotz,float pointx,float pointy,float pointz);
void SE_screen_scale(float zoomx,float zoomy,float zoomz);
void SE_screen_resettransform();

/*SE_transf init*/

SE_transf *SE_transf_init(float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
						  float rotx,float roty,float rotz,float red,float green,float blue,float alpha);




/*SE_transf clean*/
void SE_transf_clean(SE_transf *tr);
														
/*SE_transf position*/
void SE_transf_positionx_set(SE_transf *tr,float posx);
void SE_transf_positiony_set(SE_transf *tr,float posy);
void SE_transf_positionz_set(SE_transf *tr,float posz);
void SE_transf_position_set(SE_transf *tr,float posx,float posy,float posz);

/*SE_transf rotation*/
void SE_trasf_width_set(SE_transf *tr,float width);
void SE_trasf_height_set(SE_transf *tr,float height);
void SE_transf_dimentions_set(SE_transf *tr,float width,float height);

/*SE_transf zoom*/
void SE_transf_zoomx_set(SE_transf *tr,float zoomx);
void SE_transf_zoomy_set(SE_transf *tr,float zoomy);
void SE_transf_zoom_set(SE_transf *tr,float zoom);

/*SE_transf rotation*/
void SE_transf_rotationx_set(SE_transf *tr,float rotx);
void SE_transf_rotationy_set(SE_transf *tr,float roty);
void SE_transf_rotationz_set(SE_transf *tr,float rotz);
void SE_transf_rotation_set(SE_transf *tr,float rotx,float roty,float rotz);

/*SE_transf tint*/
void SE_transf_rgb_set(SE_transf *tr,float red,float green,float blue);

/*SE_transf alpha transparency*/
void SE_transf_alpha_set(SE_transf *tr,float alpha);














#endif


