#ifndef BOX_H_
#define BOX_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct
{

	float x,y; /*posicion de la caja*/
	float w,h;/*ancho y alto de la caja de colision*/

}SE_box;/*caja de colision*/


SE_box SE_box_init(float posx,float posy,float width,float height);
void SE_box_position_set(SE_box *box,float posx,float posy);
void SE_box_dimentions_set(SE_box *box,float width,float height);












#endif
