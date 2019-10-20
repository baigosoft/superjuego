#ifndef RENDER_H_
#define RENDER_H_


#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"
#include "SDL_image.h"
#include "utils.h"

extern int screen_width,screen_height;

void SE_screen_fullscreen(int fs);
int SE_screen_init(int width,int height,int bpp);
void SE_screen_close();
void SE_screen_enable2d();
void SE_screen_disable2d();
void SE_screen_clear(float r,float g,float b,float a);
void SE_screen_flip();
void SE_screen_rotate(float rotx,float roty,float rotz,float pointx,float pointy,float pointz);
void SE_screen_scale(float zoomx,float zoomy,float zoomz);
void SE_screen_resettransform();



#endif


