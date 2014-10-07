#include "tile.h"


int SE_calc_xy(int x,int y,int numtilesx,int numtilesy)
{	

	int t = (y*numtilesx) + x;
	return t;

}

SE_tile *SE_tile_init()
{

	SE_tile *tl;
	tl = (SE_tile*)malloc(sizeof(SE_tile));
	tl->tile_type = 0;
	tl->tileimg = NULL;
	tl->tileani = NULL;

	return tl;
	
}

void SE_tile_img_add(SE_tile *tl,SE_image *img)
{

		tl->tile_type = IMAGE;
		tl->tileimg = img;

}

void SE_tile_ani_add(SE_tile *tl,SE_animator *ani)
{

		tl->tile_type = ANIM;
		tl->tileani = ani;	

}

SE_tileset *SE_tileset_init(float width_tile,float height_tile)
{

	SE_tileset **ts;
	ts = (SE_tileset*)malloc(sizeof(SE_tileset));
	ts->tiles = NULL;
	ts->numtileimg = 0;
	ts->wtile = width_tile;
	ts->htile = height_tile;

	return ts;	
	
}

void SE_tileset_dimentions_set(SE_tileset *ts,float width_tile,float height_tile)
{

	ts->wtile = width_tile;
	ts->htile = height_tile;


}

float SE_tileset_width(SE_tileset *ts)
{

	return ts->wtile;

}

float SE_tileset_height(SE_tileset *ts)
{

	return ts->htile;

}

void SE_tileset_animation_add(SE_tileset *ts,SE_ani *ani)
{

	if(ts->numtileimg == 0)
	{
		ts->numtileimg++;
		ts->tileani = (SE_animator**)malloc(sizeof(SE_animator*));
		ts->tileani[0] = SE_animator_init(ani);

	}else if(ts->numtileimg > 0){
				
		ts->numtileimg++;
		ts->tileani = (SE_animator**)realloc(ts->tileani,ts->numtileimg * sizeof(SE_animator*));
		ts->tileani[ts->numtileimg - 1] = SE_animator_init(ani);			

	}

}

void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz)
{

	SE_animator_draw(ts->tileani[num_tile_image],posx,posy,posz,ts->wtile,ts->htile);	

}

void SE_tileset_clean(SE_tileset *ts)
{

	int i;
	int numtileimg = ts->numtileimg;
	for(i = 0 ;i < numtileimg;i++)
	{
		SE_animator_clean(ts->tileani[i]);	
	}
	free(ts->tileani);
	free(ts);
 
}

SE_tilemap *SE_tilemap_init(int num_tile_images,float width_tile,float height_tile,int numtilex,int numtiley)
{
	SE_tilemap *tm;
	int i;
	int numtiles;

	tm = (SE_tilemap*)malloc(sizeof(SE_tilemap));

	tm->numtileimg = num_tile_images;
	
	tm->wtile = width_tile;
	tm->htile = height_tile;

	tm->numtilex = numtilex;
	tm->numtiley = numtiley;
	numtiles = numtilex * numtiley;
	

	tm->mapimage = (int*)calloc(numtiles,sizeof(int));
	tm->mapcoll = (int*)calloc(numtiles,sizeof(int));

	for(i=0;i<numtiles;i++)
	{
		tm->mapimage[i] = 0; 
		tm->mapcoll[i] = 0; 
	}
	

	printf("Se ha creado con exito el tilemap\n");

	return tm;

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

void SE_tilemap_mapimage_load(SE_tilemap *tm,char *path)
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
			tm->mapimage[i] = a;

		}	

	}else{
		printf("no existe el archivo de mapa de imagen");
	}	

	fclose(arch);
			
}


void SE_tilemap_mapimage_bin_load(SE_tilemap *tm,char *path)
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
			tm->mapimage[i] = int(v[0]);
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

void SE_tilemap_draw(SE_tilemap *tm,SE_tileset *ts,float posx,float posy,float posz)
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
					
			t = tm->mapimage[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/
			x = (i*w) + posx;/*posicion del tile en x*/
			y = (j*h) + posy;/*posicion del tile en y*/			
			
			/*void SE_tileset_draw(SE_tileset *ts,int num_tile_image,float posx,float posy,float posz)*/
			SE_tileset_draw(ts,t,x,y,posz);
			
			
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
			t = tm->mapimage[SE_calc_xy(i,j,ntilex,ntiley)];/*valor del tile en la posicion*/
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


