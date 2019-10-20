#ifndef RENDER_H_
#define RENDER_H_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>





extern int powerof2(int number);

extern SDL_Surface *screen;




typedef struct
{
GLuint texture;
int w;
int h;
float x,y;
}SE_image;

typedef struct
{
float x,y,z,w;
}SE_vector;

int SE_screen_width();
int SE_screen_height();
int SE_screen_bpp();

int SE_screen_init(int width,int height,int bpp);/*inicia graficos*/

void SE_screen_fullscreen(int fs);

/*funciones de opengl*/
void enable2d();/*setea proyeccion ortogonal*/
void disable2d();/*setea proyeccion en perspectiva*/


void SE_screen_clear(float r,float g,float b,float a);/*borra la pantalla con un color*/
void SE_screen_fade(float r,float g,float b,float a);/*sobreimprime pantalla a color especifico*/


SE_image *SE_image_load(char *path);/*carga la textura*/


void SE_image_draw(SE_image *img,float posx,float posy,float posz);
void SE_image_full_draw(SE_image *img,float posx,float posy,float posz,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha);
void SE_image_segment_draw(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha);	


void SE_image_clean(SE_image *img);/*borra textura*/
void SE_screen_flip();/*flipea el cuadro o escena*/

/*3d*/
void SE_image_triangle_draw(SE_image *img,SE_vector *vertex,float *u,float *v,float posx,float posy,float posz,float rotx, float roty, float rotz);
void SE_rotateatpoint(float rotx,float roty,float rotz,float pointx,float pointy,float pointz);
void SE_scale(float zoomx,float zoomy,float zoomz);
void SE_resettransform();

void SE_image_position(SE_image *img,float posx,float posy);

/*primitives*/
void SE_drawpoint(float x,float y,float z,float red,float green,float blue,float alpha);
void SE_drawline(float x1,float y1,float x2,float y2,float red,float green,float blue,float alpha);
void SE_drawrectangle(float x,float y,float z,float width,float height,int fill,float red,float green,float blue,float alpha);
void SE_drawcircle(float x,float y,float z,float radius,int sections,int fill,float red,float green,float blue,float alpha);






#endif


