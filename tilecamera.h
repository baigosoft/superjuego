#ifndef TILECAMERA_H_
#define TILECAMERA_H_

#include "tile.h"
#include "collision.h"
#include "sprite.h"

typedef struct{
	
	float x,y;
	int xinimap,yinimap;
	int wmap,hmap;

}SE_tilecamera;


SE_tilecamera *SE_tilecamera_init(float posx,float posy,int xinimap,int yinimap,int wmap,int hmap);
void SE_tilecamera_clean(SE_tilecamera *tcam);
void SE_tilecamera_position_set(SE_tilecamera *tcam,float posx,float posy);
void SE_tilecamera_map_position_set(SE_tilecamera *tcam,int xinimap,int yinimap);
void SE_tilecamera_map_dimentions_set(SE_tilecamera *tcam,int wmap,int hmap);
void SE_tilecamera_tilearea_draw(SE_tilemap *tm,SE_tileset *ts,SE_tilecamera *tcam,float posx,float posy,float posz);
int SE_tilecamera_tilearea_collision(SE_tilemap *tm,SE_box *box,SE_tilecamera *tcam,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy);




















#endif
