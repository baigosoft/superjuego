#ifndef TILE_H_
#define TILE_H_

#include "animation.h"
#include "box.h"
#include "collision.h"
#include "sprite.h"

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
	float wtile,htile;/*ancho y alto de cada tile*/
	
}SE_tileset;

typedef struct{		

	SE_tileset *tset;/*tileset asociado al tilemap*/	
	int *maptile;/*mapa de las imagenes*/
	int *mapcoll;/*mapa de colisiones*/

	int tile_collision;/*ultimo tile con el que hubo colision*/
	
	float wtile,htile;/*ancho y alto de cada tile*/
	int numtilex,numtiley;/*cantidad de tiles en x e y en el mapa*/

}SE_tilemap;




/*calcula posicion en el tilemap*/
int SE_calc_xy(int x,int y,int numtilesx,int numtilesy);





/*TILESET*/

SE_tileset *SE_tileset_init(int numtileset,float width_tile,float height_tile);
void SE_tileset_img_segment_add(SE_tileset *ts,SE_image *img,int num_tile,float xtex,float ytex);
void SE_tileset_create_from_img(SE_tileset *ts,SE_image *img,int numimagex,int numimagey);
void SE_tileset_img_add(SE_tileset *ts,SE_image *img,int num_tile);
void SE_tileset_ani_add(SE_tileset *ts,SE_ani *ani,int num_tile);
void SE_tileset_clean(SE_tileset *ts);

/*TILEMAP*/

SE_tilemap *SE_tilemap_init(SE_tileset *tset,int numtileset,float width_tile,float height_tile,int numtilex,int numtiley);
void SE_tilemap_clean(SE_tilemap *tm);
void SE_tilemap_tileset_set(SE_tilemap *tm,SE_tileset *tset);
void SE_tilemap_data_load(SE_tilemap *tm,const char *path);
void SE_tilemap_maptile_load(SE_tilemap *tm,const char *path);
void SE_tilemap_maptile_bin_load(SE_tilemap *tm,const char *path);
void SE_tilemap_mapcoll_load(SE_tilemap *tm,const char *path);
void SE_tilemap_mapcoll_bin_load(SE_tilemap *tm,const char *path);
void SE_tilemap_draw(SE_tilemap *tm,float posx,float posy,float posz);
int SE_tilemap_collision(SE_tilemap *tm,float tm_posx,float tm_posy,SE_box *box,float box_posx,float box_posy);





















#endif
