#ifndef TILE_H_
#define TILE_H_

#include "animation.h"
#include "collision.h"

#define IMAGE 0
#define ANIM 1

typedef struct{

	int tile_type;/*tipo imagen (IMAGE) o animacion (ANIM)*/
	SE_image *tileimg;
	SE_animator *tileani;

}SE_tile;

typedef struct{	

	SE_tile **tiles;/*tiles*/
	int numtileimg;/*numero de imagenes o animaciones*/	
	float wtile,htile;/*ancho y alto del tile*/
	
}SE_tileset;

typedef struct{		

	int numtileimg;/*numero de imagenes del tilemap*/
	int *mapimage;/*mapa de las imagenes*/
	int *mapcoll;/*mapa de colisiones*/
	
	float wtile,htile;/*ancho y alto de cada tile*/
	int numtilex,numtiley;/*cantidad de tiles en x e y en el mapa*/
	int numtile;/*numero total de tiles*/

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
void SE_tilemap_loaddata(SE_tilemap *tm,char *path);
void SE_tilemap_mapimage_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapimage_bin_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapcoll_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapcoll_bin_load(SE_tilemap *tm,char *path);
void SE_tilemap_draw(SE_tilemap *tm,SE_tileset *ts,float posx,float posy,float posz);
int SE_tilemap_collision(SE_tilemap *tm,SE_box *box,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy);



















#endif
