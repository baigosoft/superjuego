#ifndef COLLISION_H_
#define COLLISION_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{

	float x,y; /*posicion de la caja*/
	float w,h;/*ancho y alto de la caja de colision*/

}SE_box;/*caja de colision*/



/*CAJAS DE COLISION*/
float SE_box_width(SE_box *box);/*devuelve el ancho de la caja*/
void SE_box_width_set(SE_box *box,float width);/*asigna un valor al ancho de la caja*/
float SE_box_heigth(SE_box *box);/*devuelve el alto de la caja*/
void SE_box_height_set(SE_box *box,float height);/*asigna un valor al alto de la caja*/
void SE_box_dimentions_set(SE_box *box,float width,float height);/*asigna valores al ancho y alto de la caja*/

float SE_box_x(SE_box *box);/*devuelve posicion en x de la caja*/
void SE_box_x_set(SE_box *box,float posx);/*asigna posicion en x a la caja*/
float SE_box_y(SE_box *box);/*devuelve posicion en y de la caja*/
void SE_box_y_set(SE_box *box,float posy);/*asigna posicion en y a la caja*/
void SE_box_position_set(SE_box *box,float posx,float posy);/*asigna posicion en x e y a la caja*/

int SE_box_check_position(SE_box *box1,SE_box *box2,float posx1,float posy1,float posx2,float posy2);/*controla si hay colision entre dos cajas, utilizando las posiciones de la caja como coordenadas relativas, y pasando como parametros las coordenadas reales de la caja en pantalla. Luego se suman las dos para obtener las coordenadas absolutas*/
int SE_box_check(SE_box *box1,SE_box *box2);/*controla si hay colision entre dos cajas, toma las posiciones de la caja como absolutas*/











#endif
