#include "tile.h"


int SE_calc_xy(int x,int y,int numtilesx,int numtilesy)
{	

	int t = (y*numtilesx) + x;
	return t;

}

void SE_tile_img_segment_add(SE_tile *tl,SE_image *img,float xtex,float ytex,float wtex,float htex)
{

		tl->tile_type = IMAGE;
		tl->tileimg = img;
		tl->xtex = xtex;
		tl->ytex = ytex;
		tl->wtex = wtex;
		tl->htex = htex;

}


void SE_tile_ani_add(SE_tile *tl,SE_ani *ani)
{

		tl->tile_type = ANIM;
		tl->tileani = SE_animator_init(ani);	

}

int SE_tile_type(SE_tile *tl)
{

	return tl->tile_type;	

}

void SE_tile_draw(SE_tile *tl,float posx,float posy,float posz)
{

	int type = SE_tile_type(tl);
	switch(type)
	{
		case IMAGE:
			SE_image_segment_draw(tl->tileimg,tl->xtex,tl->ytex,tl->wtex,tl->htex,posx,posy,posz);
			break;
		case ANIM:
			SE_animator_draw(tl->tileani,posx,posy,posz);
			break;
		default:
			SE_image_segment_draw(tl->tileimg,tl->xtex,tl->ytex,tl->wtex,tl->htex,posx,posy,posz);
			break;
	}
}



SE_tileset *SE_tileset_init(float width_tile,float height_tile)
{

	SE_tileset *ts;
	ts = (SE_tileset*)malloc(sizeof(SE_tileset));
	ts->tiles = NULL;
	ts->numtileset = 0;

	return ts;	
	
}



void SE_tileset_img_segment_add(SE_tileset *ts,SE_image *img,float xtex,float ytex,float wtex,float htex)
{

	if(ts->numtileset == 0)
	{
		ts->numtileset++;
		ts->tiles = (SE_tile*)malloc(sizeof(SE_tile));
		ts->tiles->tile_type = 0;
		ts->tiles->tileimg = NULL;
		ts->tiles->tileani = NULL;

		SE_tile_img_segment_add(ts->tiles,img,xtex,ytex,wtex,htex);

	}else if(ts->numtileset > 0){
				
		ts->numtileset++;
		ts->tiles = (SE_tile*)realloc(ts->tiles,ts->numtileset * sizeof(SE_tile));
		ts->tiles[ts->numtileset - 1].tile_type = 0;
		ts->tiles[ts->numtileset - 1].tileimg = NULL;
		ts->tiles[ts->numtileset - 1].tileani = NULL;

		SE_tile_img_segment_add(&ts->tiles[ts->numtileset - 1],img,xtex,ytex,wtex,htex);

	}

}

void SE_tileset_img_add(SE_tileset *ts,SE_image *img)
{

	SE_tileset_img_segment_add(ts,img,0,0,img->width,img->height);

}

void SE_tileset_ani_add(SE_tileset *ts,SE_ani *ani)
{

	if(ts->numtileset == 0)
	{
		ts->numtileset++;
		ts->tiles = (SE_tile*)malloc(sizeof(SE_tile));
		ts->tiles->tile_type = 0;
		ts->tiles->tileimg = NULL;
		ts->tiles->tileani = NULL;

		SE_tile_ani_add(ts->tiles,ani);

	}else if(ts->numtileset > 0){
				
		ts->numtileset++;
		ts->tiles = (SE_tile*)realloc(ts->tiles,ts->numtileset * sizeof(SE_tile));
		ts->tiles[ts->numtileset - 1].tile_type = 0;
		ts->tiles[ts->numtileset - 1].tileimg = NULL;
		ts->tiles[ts->numtileset - 1].tileani = NULL;

		SE_tile_ani_add(&ts->tiles[ts->numtileset - 1],ani);

	}


}

void SE_tileset_draw(SE_tileset *ts,int num_tile,float posx,float posy,float posz)
{

	SE_tile_draw(&ts->tiles[num_tile],posx,posy,posz);

}

void SE_tileset_clean(SE_tileset *ts)
{

	free(ts->tiles);	
	free(ts);
 
}

SE_tilemap *SE_tilemap_init(SE_tileset *tset,int numtileset,float width_tile,float height_tile,int numtilex,int numtiley)
{
	SE_tilemap *tm;
	int i;
	int numtiles;

	tm = (SE_tilemap*)malloc(sizeof(SE_tilemap));

	tm->tset = tset;

	tm->wtile = width_tile;
	tm->htile = height_tile;

	tm->numtilex = numtilex;
	tm->numtiley = numtiley;
	numtiles = numtilex * numtiley;
	

	tm->maptile = (int*)calloc(numtiles,sizeof(int));
	tm->mapcoll = (int*)calloc(numtiles,sizeof(int));

	for(i=0;i<numtiles;i++)
	{
		tm->maptile[i] = 0; 
		tm->mapcoll[i] = 0; 
	}
	

	printf("Se ha creado con exito el tilemap\n");

	return tm;

}


void SE_tilemap_tileset_set(SE_tilemap *tm,SE_tileset *tset)
{

	tm->tset = NULL;
	tm->tset = tset;

}

void SE_tilemap_loaddata(SE_tilemap *tm,char *path)
{
	FILE *arch;
	char line[30];
	char tag[20];
	char value[10];
	int v;
	arch = fopen(path,"r");
	while(!feof(arch))
	{
		
		fgets(line,30,arch);
		
		sscanf(line,"%[^ :]%*[ :]%[^:;]",tag,value);
			
		/*printf("%s",tag);*/
		v = atoi(value);
		/*printf("%d",v);*/

		if(strcmp(tag,"#TILEX") == 0)tm->numtilex = v;
		if(strcmp(tag,"#TILEY") == 0)tm->numtiley = v;
		if(strcmp(tag,"#WTILE") == 0)tm->wtile = v;
		if(strcmp(tag,"#HTILE") == 0)tm->htile = v;
		
		memset(line,0,30);
		memset(tag,0,20);
		memset(value,0,10);

		
	
	}

	fclose(arch);

}

void SE_tilemap_maptile_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;

	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	arch = fopen(path,"r");

	if((arch=fopen(path,"rb")) != NULL) 
	{
		for(i=0;i<numtiles;i++)
		{
		
			fscanf(arch,"%d",&a);			
			tm->maptile[i] = a;

		}	

	}else{
		printf("no existe el archivo de mapa de imagen");
	}	

	fclose(arch);
			
}


void SE_tilemap_maptile_bin_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;
	int c;
	char v[1];
	
	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	if((arch=fopen(path,"r")) != NULL) 
	{
		
		for(i=0;i<numtiles;i++)
		{
			c=fread(v,1,1,arch);
			tm->maptile[i] = int(v[0]);
		}

	}else{
		printf("no existe el archivo de mapa de imagen");
	}

	fclose(arch);
				
}

void SE_tilemap_mapcoll_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;

	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	arch = fopen(path,"r");

	if((arch=fopen(path,"r")) != NULL) 
	{
		for(i=0;i<numtiles;i++)
		{
		
			fscanf(arch,"%d",&a);			
			tm->mapcoll[i] = a;

		}	

	}else{
		printf("no existe el archivo de mapa de imagen");
	}	

	fclose(arch);
			
}

void SE_tilemap_mapcoll_bin_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;
	int c;
	char v[1];
	
	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	if((arch=fopen(path,"rb")) != NULL) 
	{
		for(i=0;i<numtiles;i++)
		{
			c=fread(v,1,1,arch);
			tm->mapcoll[i] = int(v[0]);
		}

	}else{
		printf("no existe el archivo de mapa de colision");
	}

	fclose(arch);	
		
}

void SE_tilemap_draw(SE_tilemap *tm,float posx,float posy,float posz)
{

	int t;
	int i;
	int j;
	int w = tm->wtile;
	int h = tm->htile;

	int ntilex = tm->numtilex;
	int ntiley = tm->numtiley;

	float x;
	float y;


	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
					
			t = tm->maptile[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/
			x = (i*w) + posx;/*posicion del tile en x*/
			y = (j*h) + posy;/*posicion del tile en y*/			
			
			/*void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz)*/
			SE_tileset_draw(tm->tset,t,x,y,posz);
			
			
		}
	}

}


int SE_tilemap_collision(SE_tilemap *tm,SE_box *box,float tilemap_posx,float tilemap_posy,float box_posx,float box_posy)
{

	SE_box temp,temp2;

	temp.x = tilemap_posx;
	temp.y = tilemap_posy;
	temp.w = tm->wtile;
	temp.h = tm->htile;

	temp2.x = box->x;
	temp2.y = box->y;
	temp2.w = box->w;
	temp2.h = box->h;

	int ntilex = tm->numtilex;
	int ntiley = tm->numtiley;

	float x;
	float y;
	
	int t = 0;

	int value = 0;

	int i,j;

		
	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
			t = tm->maptile[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/
			x = ((float)i*temp.w);
			y = ((float)j*temp.h);			
			
			if(t > 0)
			{		
				value = SE_box_check_position(&temp,&temp2,x,y,box_posx,box_posy);
				if(value > 0) return value;				
			}			
		}
	}
	
	return 0;


}



SE_tilearea *SE_tilearea_init(float posx,float posy,float posz,int xinimap,int yinimap,int wmap,int hmap)
{

	SE_tilearea *trea;
	trea = (SE_tilearea*)malloc(sizeof(SE_tilearea));
	trea->x = posx;
	trea->y = posy;
	trea->z = posz;
	trea->xinimap = xinimap;
	trea->yinimap = yinimap;
	trea->wmap = wmap;
	trea->hmap = hmap;	

	return trea;

}


void SE_tilearea_clean(SE_tilearea *trea)
{

	free(trea);

}

void SE_tilearea_positionx_set(SE_tilearea *trea,float posx)
{

	trea->x = posx;

}

void SE_tilearea_positiony_set(SE_tilearea *trea,float posy)
{

	trea->y = posy;

}

void SE_tilearea_positionz_set(SE_tilearea *trea,float posz)
{

	trea->z = posz;

}

void SE_tilearea_position_set(SE_tilearea *trea,float posx,float posy,float posz)
{

	trea->x = posx;
	trea->y = posy;
	trea->z = posz;

}


void SE_tilearea_map_position_set(SE_tilearea *trea,int xinimap,int yinimap)
{

	trea->xinimap = xinimap;
	trea->yinimap = yinimap;

}

void SE_tilearea_map_dimentions_set(SE_tilearea *trea,int wmap,int hmap)
{

	trea->wmap = wmap;
	trea->hmap = hmap;

}

void SE_tilearea_draw(SE_tilearea *trea,SE_tilemap *tm)
{

	int t;
	int i,j;

	int xmap = 0;
	int ymap = 0;

	int w = tm->wtile;
	int h = tm->htile;

	float posx;
	float posy;	
	
	if(trea->wmap > tm->numtilex)
	{
		trea->wmap = tm->numtilex;
	}
	if(trea->hmap > tm->numtiley)
	{
		trea->hmap = tm->numtiley;
	}
	if(trea->xinimap < 0)
	{
		trea->xinimap = 0;
	}
	if((trea->xinimap + trea->wmap) > tm->numtilex)
	{
		trea->xinimap = tm->numtilex - trea->wmap;
	}
	if(trea->yinimap < 0)
	{
		trea->yinimap = 0;
	}
	if((trea->yinimap + trea->hmap) > tm->numtiley)
	{
		trea->yinimap = tm->numtiley - trea->hmap;
	}


	for(j = 0;j < trea->hmap;j++)
	{
		for(i = 0;i < trea->wmap;i++)
		{	
			xmap = i + trea->xinimap;
			ymap = j + trea->yinimap;			
		
			t = tm->maptile[SE_calc_xy(xmap,ymap,tm->numtilex,tm->numtiley)];/*valor del tile en la posicion*/
			posx = (i*w) + trea->x;/*posicion del tile en x*/
			posy = (j*h) + trea->y;/*posicion del tile en y*/			
			
			SE_tileset_draw(tm->tset,t,posx,posy,trea->z);
			
			
		}
	}




}


int SE_tilecamera_tilearea_collision(SE_tilearea *trea,SE_tilemap *tm,SE_box *box,float box_posx,float box_posy)
{

	int xmap = 0;
	int ymap = 0;

	int w = tm->wtile;
	int h = tm->htile;

	SE_box temp,temp2;

	float posx;
	float posy;
	
	int t = 0;

	int value = 0;

	int i,j;

	temp.x = trea->x;
	temp.y = trea->y;
	temp.w = tm->wtile;
	temp.h = tm->htile;

	temp2.x = box->x;
	temp2.y = box->y;
	temp2.w = box->w;
	temp2.h = box->h;

	if(trea->wmap > tm->numtilex)
	{
		trea->wmap = tm->numtilex;
	}
	if(trea->hmap > tm->numtiley)
	{
		trea->hmap = tm->numtiley;
	}
	if(trea->xinimap < 0)
	{
		trea->xinimap = 0;
	}
	if((trea->xinimap + trea->wmap) > tm->numtilex)
	{
		trea->xinimap = tm->numtilex - trea->wmap;
	}
	if(trea->yinimap < 0)
	{
		trea->yinimap = 0;
	}
	if((trea->yinimap + trea->hmap) > tm->numtiley)
	{
		trea->yinimap = tm->numtiley - trea->hmap;
	}



		
	for(j=0;j < trea->hmap;j++)
	{
		for(i=0;i < trea->wmap;i++)
		{	
			xmap = i + trea->xinimap;
			ymap = j + trea->yinimap;
			
			t = tm->mapcoll[SE_calc_xy(xmap,ymap,tm->numtilex,tm->numtiley)];/*valor del tile en la posicion*/
	
			temp.x = i*w + trea->x;
			temp.y = j*w + trea->y;		
			
			if(t > 0)
			{		
				value = SE_box_check_position(&temp,&temp2,xmap,ymap,box_posx,box_posy);
				if(value > 0) return value;				
			}			
		}
	}
	
	return 0;

}
