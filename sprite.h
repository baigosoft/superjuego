#ifndef SPRITE_H_
#define SPRITE_H_

#include "animation.h"
#include "collision.h"


typedef struct
{
	float offsetx,offsety;
	SE_animator *ator;
	SE_box *box;
	int numboxes;
}SE_sprite;



/*inicializa el sprite*/
SE_sprite *SE_sprite_init(SE_ani *ani);

/*devuelve ancho por defecto del sprite*/
float SE_sprite_width(SE_sprite *spr);

/*devuelve alto por defecto del sprite*/
float SE_sprite_height(SE_sprite *spr);

/*asigna valor del offset (posicion adicional que se suma a la posicion en pantalla)*/
void SE_sprite_offset_set(SE_sprite *spr,float offsetx,float offsety);

/*crea un nueva caja de colision*/
void SE_sprite_box_add(SE_sprite *spr,float offsetx,float offsety,float width_box,float height_box);

/*asigna valor al offset de la caja de colision*/
void SE_sprite_box_set_offset(SE_sprite *spr,int numbox,float offsetx,float offsety);

/*asigna valor de ancho y alto a la caja de colision*/
void SE_sprite_box_set_dimentions(SE_sprite *spr,int numbox,float width_box,float height_box);

/*controla colision entre dos sprites*/
int SE_sprite_checkcollision(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2);

/*controla colision entre dos sprites que tienen muchas cajas de colision*/
int SE_sprite_checkcollision_multi(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2);

/*elimina sprite*/
void SE_sprite_clean(SE_sprite *spr);

/*dibuja sprites con todos los parametros disponibles*/
void SE_sprite_draw_fx(SE_sprite *spr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha);

/*dibuja sprites con los parametros mas importantes*/
void SE_sprite_draw(SE_sprite *spr,float posx,float posy,float posz,float width,float height);

void SE_sprite_draw_transf(SE_sprite *spr,SE_transf *tr);






#endif
