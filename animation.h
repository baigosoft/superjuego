/*
    Superjuego Engine
    Copyright (C) 2011 Jorge Luís Cabral y Gabriel Ernesto Cabral

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: baigosoft@hotmail.com
*/

#ifndef ANIMATION_H_
#define ANIMATION_H_


#include "image.h"



#define START 1
#define STOP 0

typedef struct
{

	SE_image *image;/*puntero a la imagen que vamos a usar en el frame*/
	float xt,yt;/*coordenada de la textura*/
	float wt,ht;/*ancho y alto de la textura*/
	int delay;/*delay(retardo) del cuadro*/

		
}SE_frame;

typedef struct
{

	SE_frame *fr;/*puntero donde almacenamos el frame, o el array de frames*/

	int numframes;/*numero de frames que hay*/

	float width,height;	

}SE_ani;

typedef struct
{

	SE_ani *ani;/*puntero que apunta a la animacion que vamos a controlar*/

	int numframes;/*numero de frames de la animacion*/

	float delayperc;/*porcentaje de delay*/
	
	int status;/*estado (puede ser START o STOP)*/
	int counter;/*contador de delay*/
	int currentframe;/*numero de frame actual*/
	int initframe,endframe;
	
}SE_animator;

/*frame*/
void SE_frame_image_add_segment(SE_frame *fr,SE_image *img,float x_tex,float y_tex,float width_tex,float height_tex);
void SE_frame_image_add(SE_frame *fr,SE_image *img);

void SE_frame_delay_set(SE_frame *fr,int delay);

void SE_frame_draw(SE_frame *fr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha);

/*ANIMATION*/

SE_ani* SE_ani_init(float width,float height);

float SE_ani_width(SE_ani *ani);
float SE_ani_height(SE_ani *ani);

void SE_ani_frame_delay_set(SE_ani *ani,int frame_number,int delay);

void SE_ani_addframe_segment(SE_ani *ani,SE_image *img,int delay,float xtex,float ytex,float wtex,float htex);
void SE_ani_addframe(SE_ani *ani,SE_image *img,int delay);

void SE_ani_draw(SE_ani *ani,int frame_number, float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha);

void SE_ani_clean(SE_ani *ani);


/*ANIMATOR*/

SE_animator *SE_animator_init(SE_ani *ani);

int SE_animator_status(SE_animator *ator);

void SE_animator_start(SE_animator *ator);
void SE_animator_stop(SE_animator *ator);

void SE_animator_initframe_set(SE_animator *ator,int initframe);
void SE_animator_endframe_set(SE_animator *ator,int endframe);

void SE_animator_reset(SE_animator *ator);

void SE_animator_delaypercent(SE_animator *ator,float delayperc);

void SE_animator_draw_fx(SE_animator *ator,
						 float posx,float posy,float posz,
						 float width,float height,float zoomx,float zoomy,
						 float rotationx,float rotationy,float rotationz,
						 float red,float green,float blue,float alpha);

void SE_animator_draw_wh(SE_animator *ator,float posx,float posy,float posz,float width,float height);

void SE_animator_draw(SE_animator *ator,float posx,float posy,float posz);

void SE_animator_draw_transf(SE_animator *ator,SE_transf *tr);

void SE_animator_clean(SE_animator *ator);












#endif

