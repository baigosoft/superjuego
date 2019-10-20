#ifndef SPRITE_H_
#define SPRITE_H_

#include "animation.h"
#include "collision.h"

#define IMG 0
#define ANI 1




typedef struct
{
	SE_box *box;
}SE_box_pf;/*colisiones por frame*/

typedef struct
{
	float offsetx,offsety;
	int type;/*indica si es tipo imagen o tipo animacion [IMG|ANI]*/
	SE_image *img;
	float xt,yt;/*coordenada de la textura de la imagen*/
	float wt,ht;/*ancho y alto de la textura de la imagen*/
	SE_animator *ator;
	SE_box *box;
	int numboxes;
	SE_box_pf *frbox;/*cajas de colision por frame*/
	int numfrboxes;/*numero de cajas de colision por frame*/	
}SE_sprite;



/*inicializa el sprite*/
SE_sprite *SE_sprite_init(int type);/*puede ser IMG o ANI*/

/*asigna segmento de imagen a sprite*/
void SE_sprite_img_segment_add(SE_sprite *spr,SE_image *img,float xt,float yt,float wt,float ht);

/*asigna imagen a sprite*/
void SE_sprite_img_add(SE_sprite *spr,SE_image *img);

/*asigna animacion a sprite*/
void SE_sprite_ani_add(SE_sprite *spr,SE_ani *ani);

/*devuelve ancho por defecto del sprite*/
float SE_sprite_width(SE_sprite *spr);

/*devuelve alto por defecto del sprite*/
float SE_sprite_height(SE_sprite *spr);

/*asigna valor del offset (posicion adicional que se suma a la posicion en pantalla)*/
void SE_sprite_offset_set(SE_sprite *spr,float offsetx,float offsety);

/*inicializa cajas de colisiones*/
void SE_sprite_box_init(SE_sprite *spr,int numboxes);

/*asigna valor a la caja de colision*/
void SE_sprite_box_set(SE_sprite *spr,int box_number,float offsetx,float offsety,float width_box,float height_box);

/*chequea colision entre 1 caja de un sprite con otra caja de otro sprite*/
int SE_sprite_collision_single(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2);

/*chequea colision entre todas las cajas de 2 sprites*/
int SE_sprite_collision(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2);

/*chequea colision entre todas las cajas de un sprite y una caja cualquiera*/
int SE_sprite_collision_box(SE_sprite *spr,SE_box *box,float posx_spr,float posy_spr,float posx_box,float posy_box);

/*chequea colision entre 1 caja de 1 frame de un sprite, con 1 caja de 1 frame de otro sprite*/
//int SE_sprite_collision_pf_single(SE_sprite *spr1,int frame_number1,int numbox1,
//								  SE_sprite *spr2,int frame_number2,int numbox2,
//								  float posx1,float posy1,float posx2,float posy2);

/*chequea colision entre 1 caja de frame actual de un sprite, con 1 caja de frame actual de otro sprite*/
//int SE_sprite_collision_pf_current(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2);

/*chequea colision entre todas las cajas de frame actual de 2 sprites*/
//int SE_sprite_collision_pf(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2);

/*elimina sprite*/
void SE_sprite_clean(SE_sprite *spr);

/*dibuja sprites con todos los parametros disponibles*/
void SE_sprite_draw_fx(SE_sprite *spr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha);

/*dibuja sprites con los parametros de posicion y dimensiones*/
void SE_sprite_draw_wh(SE_sprite *spr,float posx,float posy,float posz,float width,float height);

/*dibuja sprites con los parametros de posicion*/
void SE_sprite_draw(SE_sprite *spr,float posx,float posy,float posz);

/*dibuja sprites con parametros a traves de un struct transf*/
void SE_sprite_draw_transf(SE_sprite *spr,SE_transf *tr);






#endif
