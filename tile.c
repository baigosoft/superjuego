#include "tile.h"

/*TILE*/

void SE_tile_img_add(SE_tile *tl,SE_image *img,float xtex,float ytex,float wtex,float htex);
void SE_tile_ani_add(SE_tile *tl,SE_ani *ani);
int SE_tile_type(SE_tile *tl);
void SE_tile_draw(SE_tile *tl,float posx,float posy,float posz);

/*TILESET*/

void SE_tileset_draw(SE_tileset *ts,int num_tile,float posx,float posy,float posz);

/*TILE*/

int SE_calc_xy(int x,int y,int numtilesx,int numtilesy)
{	

	int t = (y*numtilesx) + x;
	return t;

}

void SE_tile_img_add(SE_tile *tl,SE_image *img,float xtex,float ytex,float wtex,float htex)
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



SE_tileset *SE_tileset_init(int numtileset,float width_tile,float height_tile)
{

	SE_tileset *ts;
	ts = (SE_tileset*)malloc(sizeof(SE_tileset));
	ts->tiles = (SE_tile*)malloc(numtileset * sizeof(SE_tile));
	ts->numtileset = numtileset;
	ts->wtile = width_tile;
	ts->htile = height_tile;
	return ts;	
	
}



void SE_tileset_img_segment_add(SE_tileset *ts,SE_image *img,int num_tile,float xtex,float ytex)
{

	SE_tile_img_add(&ts->tiles[num_tile],img,xtex,ytex,ts->wtile,ts->htile);

}

void SE_tileset_create_from_img(SE_tileset *ts,SE_image *img,int numimagex,int numimagey)
{

	int i,j;
	int count = 0;
	float w = ts->wtile;
	float h = ts->htile;

	for(j=0;j<numimagey;j++)
	{			
		for(i=0;i<numimagex;i++)
		{
			SE_tileset_img_segment_add(ts,img,count,i*w,j*h);
			count++;
		}
	}
}

void SE_tileset_img_add(SE_tileset *ts,SE_image *img,int num_tile)
{

	SE_tileset_img_segment_add(ts,img,num_tile,0,0);

}

void SE_tileset_ani_add(SE_tileset *ts,SE_ani *ani,int num_tile)
{

	SE_tile_ani_add(&ts->tiles[num_tile],ani);

}

void SE_tileset_draw(SE_tileset *ts,int num_tile,float posx,float posy,float posz)
{

	SE_tile_draw(&ts->tiles[num_tile],posx,posy,posz);

}

void SE_tileset_clean(SE_tileset *ts)
{

	free(ts->tiles);	
	free(ts);

	printf("SE_tileset:se elimino puntero de tileset\n");
 
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

	tm->tile_collision = 0; 

	numtiles = numtilex * numtiley;
	

	//tm->maptile = (int*)calloc(numtiles,sizeof(int));
	//tm->mapcoll = (int*)calloc(numtiles,sizeof(int));

	tm->maptile = (int*)malloc(numtiles * sizeof(int));
	tm->mapcoll = (int*)malloc(numtiles * sizeof(int));

	for(i=0;i<numtiles;i++)
	{
		tm->maptile[i] = 0; 
		tm->mapcoll[i] = 0; 
	}
	

	printf("Se ha creado con exito el tilemap\n");

	return tm;

}


void SE_tilemap_clean(SE_tilemap *tm)
{

	free(tm->maptile);
	free(tm->mapcoll);
	free(tm);

	printf("SE_tilemap:se elimino puntero de tilemap\n");
	

}


void SE_tilemap_tileset_set(SE_tilemap *tm,SE_tileset *tset)
{

	tm->tset = NULL;
	tm->tset = tset;

}

void SE_tilemap_data_load(SE_tilemap *tm,const char *path)
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

void SE_tilemap_maptile_load(SE_tilemap *tm,const char *path)
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


void SE_tilemap_maptile_bin_load(SE_tilemap *tm,const char *path)
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

void SE_tilemap_mapcoll_load(SE_tilemap *tm,const char *path)
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

void SE_tilemap_mapcoll_bin_load(SE_tilemap *tm,const char *path)
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

	int t = 0;
	int i;
	int j;
	int w = tm->wtile;
	int h = tm->htile;

	int ntilex = tm->numtilex;
	int ntiley = tm->numtiley;

	float x = 0;
	float y = 0;


	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
					
			t = tm->maptile[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/
			x = (i*w) + posx;/*posicion del tile en x*/
			y = (j*h) + posy;/*posicion del tile en y*/			
			
			if(((x >= -w) && (x <= (screen_width + w))) || ((y >= -h) && (y <= (screen_height + h))))
			{
				SE_tileset_draw(tm->tset,t,x,y,posz);
			}
			
		}
	}

}



int SE_tilemap_collision(SE_tilemap *tm,float tm_posx,float tm_posy,SE_box *box,float box_posx,float box_posy)
{

	SE_box temp,temp2;

	temp.x = tm_posx;
	temp.y = tm_posy;
	temp.w = tm->wtile;
	temp.h = tm->htile;

	temp2.x = box->x + box_posx;
	temp2.y = box->y + box_posy;
	temp2.w = box->w;
	temp2.h = box->h;

	int ntilex = tm->numtilex;
	int ntiley = tm->numtiley;

	int w = tm->wtile;
	int h = tm->htile;

	float x;
	float y;
	
	int t = 0;

	int value = 0;

	int i,j;

		
	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
			t = tm->mapcoll[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/

			temp.x = i*temp.w + tm_posx;
			temp.y = j*temp.h + tm_posy;			

			if(((temp.x >= -w) && (temp.x <= (screen_width + w))) || ((temp.y >= -h) && (temp.y <= (screen_height + h))))	
			{
				if(t > 0)
				{	
				
					value = SE_coll_check(&temp,&temp2);
					if(value > 0)
					{
						tm->tile_collision = t;
						//printf("%d\n",value); 
						return value;
					}			
				}			
			}
		}
	}
	
	return 0;


}
