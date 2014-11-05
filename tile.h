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

void SE_tile_img_add(SE_tile *tl,SE_image *img);

void SE_tile_ani_add(SE_tile *tl,SE_ani *ani);

int SE_tile_type(SE_tile *tl);

void SE_tile_draw(SE_tile *tl,float posx,float posy,float posz);



/*TILESET*/

SE_tileset *SE_tileset_init(float width_tile,float height_tile);
void SE_tileset_dimentions_set(SE_tileset *ts,float width_tile,float height_tile);
float SE_tileset_width(SE_tileset *ts);
float SE_tileset_height(SE_tileset *ts);
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





















#endif
