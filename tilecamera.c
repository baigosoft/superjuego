#include "tilecamera.h"

SE_tilecamera *SE_tilecamera_init(float posx,float posy,int xinimap,int yinimap,int wmap,int hmap)
{

	SE_tilecamera *tcam;
	tcam = (SE_tilecamera*)malloc(sizeof(SE_tilecamera));
	tcam->x = posx;
	tcam->y = posy;
	tcam->xinimap = xinimap;
	tcam->yinimap = yinimap;
	tcam->wmap = wmap;
	tcam->hmap = hmap;	

	return tcam;

}

void SE_tilecamera_clean(SE_tilecamera *tcam)
{

	free(tcam);

}

void SE_tilecamera_position_set(SE_tilecamera *tcam,float posx,float posy)
{

	tcam->x = posx;
	tcam->y = posy;

}

void SE_tilecamera_map_position_set(SE_tilecamera *tcam,int xinimap,int yinimap)
{

	tcam->xinimap = xinimap;
	tcam->yinimap = yinimap;

}

void SE_tilecamera_map_dimentions_set(SE_tilecamera *tcam,int wmap,int hmap)
{

	tcam->wmap = wmap;
	tcam->hmap = hmap;

}


void SE_tilecamera_tilearea_draw(SE_tilemap *tm,SE_tileset *ts,SE_tilecamera *tcam,float posx,float posy,float posz)
{

	int t;
	int i,j;

	int xmap = 0;
	int ymap = 0;

	int w = tm->wtile;
	int h = tm->htile;

	float x;
	float y;	
	
	if(tcam->wmap > tm->numtilex)
	{
		tcam->wmap = tm->numtilex;
	}
	if(tcam->hmap > tm->numtiley)
	{
		tcam->hmap = tm->numtiley;
	}
	if(tcam->xinimap < 0)
	{
		tcam->xinimap = 0;
	}
	if((tcam->xinimap + tcam->wmap) > tm->numtilex)
	{
		tcam->xinimap = tm->numtilex - tcam->wmap;
	}
	if(tcam->yinimap < 0)
	{
		tcam->yinimap = 0;
	}
	if((tcam->yinimap + tcam->hmap) > tm->numtiley)
	{
		tcam->yinimap = tm->numtiley - tcam->hmap;
	}


	for(j = 0;j < tcam->hmap;j++)
	{
		for(i = 0;i < tcam->wmap;i++)
		{	
			xmap = i + tcam->xinimap;
			ymap = j + tcam->yinimap;			
		
			t = tm->mapimage[SE_calc_xy(xmap,ymap,tm->numtilex,tm->numtiley)];/*valor del tile en la posicion*/
			x = (i*w) + posx;/*posicion del tile en x*/
			y = (j*h) + posy;/*posicion del tile en y*/			
			
			/*void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz)*/
			SE_tileset_draw(ts,t,x,y,posz);
			
			
		}
	}




}


int SE_tilecamera_tilearea_collision(SE_tilemap *tm,SE_box *box,SE_tilecamera *tcam,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy)
{

	int xmap = 0;
	int ymap = 0;

	int w = tm->wtile;
	int h = tm->htile;

	SE_box temp,temp2;

	temp.x = tilemap_posx;
	temp.y = tilemap_posy;
	temp.w = tm->wtile;
	temp.h = tm->htile;

	temp2.x = box->x;
	temp2.y = box->y;
	temp2.w = box->w;
	temp2.h = box->h;

	if(tcam->wmap > tm->numtilex)
	{
		tcam->wmap = tm->numtilex;
	}
	if(tcam->hmap > tm->numtiley)
	{
		tcam->hmap = tm->numtiley;
	}
	if(tcam->xinimap < 0)
	{
		tcam->xinimap = 0;
	}
	if((tcam->xinimap + tcam->wmap) > tm->numtilex)
	{
		tcam->xinimap = tm->numtilex - tcam->wmap;
	}
	if(tcam->yinimap < 0)
	{
		tcam->yinimap = 0;
	}
	if((tcam->yinimap + tcam->hmap) > tm->numtiley)
	{
		tcam->yinimap = tm->numtiley - tcam->hmap;
	}

	float x;
	float y;
	
	int t = 0;

	int value = 0;

	int i,j;

		
	for(j=0;j < tcam->hmap;j++)
	{
		for(i=0;i < tcam->wmap;i++)
		{	
			xmap = i + tcam->xinimap;
			ymap = j + tcam->yinimap;
			
			t = tm->mapcoll[SE_calc_xy(xmap,ymap,tm->numtilex,tm->numtiley)];/*valor del tile en la posicion*/
	
			temp.x = i*w + tilemap_posx;
			temp.y = j*w + tilemap_posy;		
			
			if(t > 0)
			{		
				value = SE_box_check_position(&temp,&temp2,xmap,ymap,box_posx,box_posy);
				if(value > 0) return value;				
			}			
		}
	}
	
	return 0;

}
