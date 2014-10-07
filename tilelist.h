#ifndef TILELIST_H_
#define TILELIST_H_

#include "animation.h"
#include "collision.h"

typedef struct{	

	SE_animator **tileani;/*imagen o animacion de tile*/
	int numtileimg;/*numero de imagenes o animaciones*/	
	float wtile,htile;/*ancho y alto del tile*/

}SE_tileset;

struct struct_tile{
	int type;
	struct struct_tile *next;
};

typedef struct struct_tile SE_tile;

typedef struct{		

	int numtileimg;/*numero de imagenes del tilemap*/

	SE_tile *mapimage;
	SE_tile *mapcoll;

	float wtile,htile;/*ancho y alto de cada tile*/
	int numtilex,numtiley;/*cantidad de tiles en x e y en el mapa*/
	int numtile;/*numero total de tiles*/

	int area_width;
	int area_height;
	int currentposx;
	int currentposy;

}SE_tilemap;

/*calcula posicion en el tilemap*/
int SE_calc_xy(int x,int y,int numtilesx,int numtilesy);

/*TILESET*/

SE_tileset *SE_tileset_init(float width_tile,float height_tile);
void SE_tileset_dimentions_set(SE_tileset *ts,float width_tile,float height_tile);
float SE_tileset_width(SE_tileset *ts);
float SE_tileset_height(SE_tileset *ts);
void SE_tileset_animation_add(SE_tileset *ts,SE_ani *ani);
void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz);
void SE_tileset_clean(SE_tileset *ts);

/*TILEMAP*/

SE_tilemap *SE_tilemap_init(int num_tile_images,float width_tile,float height_tile,int numtilex,int numtiley);
void SE_tilemap_data_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapimage_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapcollision_load(SE_tilemap *tm,char *path);
void SE_tilemap_draw(SE_tilemap *tm,SE_tileset *ts,float posx,float posy,float posz);
int SE_tilemap_collision(SE_tilemap *tm,SE_box *box,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy);
void SE_tilemap_clean(SE_tilemap *tm);

void SE_tilemap_area_set(SE_tilemap *tm,int width,int height);
void SE_tilemap_area_position(SE_tilemap *tm,int posx,int posy);


void SE_tilemap_mapimage_areaload(SE_tilemap *tm,char *path);

void leerdatos(SE_tilemap *tm);


















#endif
