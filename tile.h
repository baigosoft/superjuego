#ifndef TILE_H_
#define TILE_H_

#include "animation.h"
#include "collision.h"

#define IMAGE 0
#define ANIM 1

typedef struct{

	int tile_type;/*tipo imagen (IMAGE) o animacion (ANIM)*/
	SE_image *tileimg;/*puntero a la imagen si tile_type es IMAGE*/
	float xtex,ytex,wtex,htex;/*coordenadas para la textura de la imagen*/
	SE_animator *tileani;/*puntero a la animacion si tile_type es ANIM*/

}SE_tile;

typedef struct{	

	SE_tile *tiles;/*tiles*/
	int numtileset;/*numero de imagenes o animaciones*/	
	
}SE_tileset;

typedef struct{		

	SE_tileset *tset;/*tileset asociado al tilemap*/	
	int *maptile;/*mapa de las imagenes*/
	int *mapcoll;/*mapa de colisiones*/
	
	float wtile,htile;/*ancho y alto de cada tile*/
	int numtilex,numtiley;/*cantidad de tiles en x e y en el mapa*/

}SE_tilemap;

typedef struct{
	
	float x,y,z;
	int xinimap,yinimap;
	int wmap,hmap;

}SE_tilearea;


/*calcula posicion en el tilemap*/
int SE_calc_xy(int x,int y,int numtilesx,int numtilesy);

/*TILE*/

SE_tile *SE_tile_init();

void SE_tile_img_segment_add(SE_tile *tl,SE_image *img,float xtex,float ytex,float wtex,float htex);

void SE_tile_ani_add(SE_tile *tl,SE_ani *ani);

int SE_tile_type(SE_tile *tl);

void SE_tile_draw(SE_tile *tl,float posx,float posy,float posz);



/*TILESET*/

SE_tileset *SE_tileset_init(float width_tile,float height_tile);
void SE_tileset_dimentions_set(SE_tileset *ts,float width_tile,float height_tile);
void SE_tileset_img_segment_add(SE_tileset *ts,SE_image *img,float xtex,float ytex,float wtex,float htex);
void SE_tileset_img_add(SE_tileset *ts,SE_image *img);
void SE_tileset_animation_add(SE_tileset *ts,SE_ani *ani);
void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz);
void SE_tileset_clean(SE_tileset *ts);

/*TILEMAP*/

SE_tilemap *SE_tilemap_init(SE_tileset *tset,int numtileset,float width_tile,float height_tile,int numtilex,int numtiley);
void SE_tilemap_tileset_set(SE_tilemap *tm,SE_tileset *tset);
void SE_tilemap_loaddata(SE_tilemap *tm,char *path);
void SE_tilemap_maptile_load(SE_tilemap *tm,char *path);
void SE_tilemap_maptile_bin_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapcoll_load(SE_tilemap *tm,char *path);
void SE_tilemap_mapcoll_bin_load(SE_tilemap *tm,char *path);
void SE_tilemap_draw(SE_tilemap *tm,float posx,float posy,float posz);
int SE_tilemap_collision(SE_tilemap *tm,SE_box *box,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy);

/*TILEAREA*/
SE_tilearea *SE_tilearea_init(float posx,float posy,float posz,int xinimap,int yinimap,int wmap,int hmap);
void SE_tilearea_clean(SE_tilearea *trea);
void SE_tilearea_positionx_set(SE_tilearea *trea,float posx);
void SE_tilearea_positiony_set(SE_tilearea *trea,float posy);
void SE_tilearea_positionz_set(SE_tilearea *trea,float posz);
void SE_tilearea_position_set(SE_tilearea *trea,float posx,float posy,float posz);
void SE_tilearea_map_position_set(SE_tilearea *trea,int xinimap,int yinimap);
void SE_tilearea_map_dimentions_set(SE_tilearea *trea,int wmap,int hmap);
void SE_tilearea_draw(SE_tilearea *trea,SE_tilemap *tm);
int SE_tilecamera_tilearea_collision(SE_tilearea *trea,SE_tilemap *tm,SE_box *box,float box_posx,float box_posy);


















#endif
