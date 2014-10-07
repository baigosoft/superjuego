#include "tilelist.h"


int SE_calc_xy(int x,int y,int numtilesx,int numtilesy)
{	

	int t = (y*numtilesx) + x;
	return t;

}

SE_tileset *SE_tileset_init(float width_tile,float height_tile)
{

	SE_tileset *ts;
	ts = (SE_tileset*)malloc(sizeof(SE_tileset));
	ts->tileani = NULL;
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

	tm = (SE_tilemap*)malloc(sizeof(SE_tilemap));

	tm->numtileimg = num_tile_images;
	
	tm->wtile = width_tile;
	tm->htile = height_tile;

	tm->numtilex = numtilex;
	tm->numtiley = numtiley;

	tm->area_width = numtilex;
	tm->area_height = numtiley;
	
	tm->currentposx = 0;
	tm->currentposy = 0;
	

	tm->mapimage = NULL;
	tm->mapcoll = NULL;

	printf("Se ha creado con exito el tilemap\n");

	return tm;

}


void SE_tilemap_data_load(SE_tilemap *tm,char *path)
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




/*
void SE_tilemap_mapimage_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;

	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	arch = fopen(path,"r");

	SE_tile *newtile,*previous;
	
	for(i=0;i<numtiles;i++)
	{
		
		fscanf(arch,"%d",&a);
		newtile = (SE_tile*)malloc(sizeof(SE_tile));
		newtile->type = a;
		if(tm->mapimage == NULL)
		{		
			newtile->next = tm->mapimage;		
			tm->mapimage = newtile;
		}else{
			previous = tm->mapimage;
			while(previous->next != NULL)
			{
				previous = previous->next;
			}	
			newtile->next = previous->next;
			previous->next = newtile;				
		}
			
	}	
	
	fclose(arch);
			
}

void SE_tilemap_mapcollision_load(SE_tilemap *tm,char *path)
{

	FILE *arch;	
	int a = 0;
	int i = 0;

	int numtiles = (tm->numtilex) * (tm->numtiley);
	
	arch = fopen(path,"r");

	SE_tile *newtile,*previous;
	
	for(i=0;i<numtiles;i++)
	{
		
		fscanf(arch,"%d",&a);
		newtile = (SE_tile*)malloc(sizeof(SE_tile));
		newtile->type = a;

		if(tm->mapcoll == NULL)
		{		
			newtile->next = tm->mapcoll;		
			tm->mapcoll = newtile;
		}else{
			previous = tm->mapcoll;
			while(previous->next != NULL)
			{
				previous = previous->next;
			}	
			newtile->next = previous->next;
			previous->next = newtile;				
		}
			
	}
	
	
	fclose(arch);
			
}
*/

void SE_tilemap_area_set(SE_tilemap *tm,int width,int height)
{

	if(width < 0 || width > tm->numtilex)
	{	
		printf("valor de ancho de area fuera de rango");
	}else{

		tm->area_width = width;
	}

	if(height < 0 || height > tm->numtiley)
	{	
		printf("valor de alto de area fuera de rango");
	}else{
		tm->area_height = height;
	}

}


void SE_tilemap_area_position(SE_tilemap *tm,int posx,int posy)
{

	if(posx < 0 || posx > tm->numtilex - tm->area_width)
	{
		printf("valor de posicion en x de area fuera de rango");
	}else{
		tm->currentposx = posx;		
	}

	if(posy < 0 || posy > tm->numtiley - tm->area_height)
	{
		printf("valor de posicion en y de area fuera de rango");
	}else{
		tm->currentposy = posy;
	}

}

void SE_tilemap_mapimage_areaload(SE_tilemap *tm,char *path)
{	
	FILE *arch;	
	char a[1];
	int c;
	int i,j;

	int x_ini = tm->currentposx;
	int y_ini = tm->currentposy;
	int width = tm->area_width;
	int height = tm->area_height;

	int numtiles = (tm->numtilex) * (tm->numtiley);
	int ntilex = tm->numtilex;
	int ntiley = tm->numtiley;
	
	int posini = 0;
	int countrow = y_ini;

	arch = fopen(path,"r");

	SE_tile *newtile,*previous;

	for(j=0;j < height;j++)	
	{
		posini = SE_calc_xy(x_ini,countrow,ntilex,ntiley);
  		fseek(arch,posini,SEEK_SET);
		countrow++;

		for(i=0;i < width;i++)
		{		
			c = fread(a,1,1,arch);
		
			newtile = (SE_tile*)malloc(sizeof(SE_tile));
			newtile->type = int(a[0]);

			if(tm->mapimage == NULL)
			{		
				newtile->next = tm->mapimage;		
				tm->mapimage = newtile;
			}else{
				previous = tm->mapimage;
				while(previous->next != NULL)
				{
					previous = previous->next;
				}	
				newtile->next = previous->next;
				previous->next = newtile;	
			}			
		}

	}		
	
	
	fclose(arch);
}

void SE_tilemap_toprow_load(SE_tilemap *tm,char *path,int number_row)
{

	FILE *arch;
	arch = fopen(path,"r");	

	int width = tm->area_width;
	int height = tm->area_height;	
	int i,j;	
	int count = 0;
	int pos = 0;
	int c;

	int temprow[width];

	tm->currentposy = tm->currentposy - 1;
	pos = SE_calc_xy(tm->currentposx,tm->currentposy,tm->numtilex,tm->numtiley);
  	fseek(arch,pos,SEEK_SET);
	c = fread(temprow,width,1,arch);
	
	SE_tile *v;
	v = tm->mapimage;

	fclose(arch);


}

void SE_tilemap_bottomrow_load(SE_tilemap *tm,int number_row)
{




}



void SE_tilemap_leftcolumn_load(SE_tilemap *tm,int number_col)
{




}

void SE_tilemap_rightcolumn_load(SE_tilemap *tm,int number_col)
{




}



void leerdatos(SE_tilemap *tm)
{

	SE_tile *v;
	v = tm->mapimage;
	while(v)
	{		
		printf("%d",v->type);
		v = v->next;	
	}

}

/*
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

	SE_tile *v;
	v = tm->mapimage;
	
	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
					
			t = v->type;

			x = (i*w) + posx;
			y = (j*h) + posy;			
			
			if(t > 0)
			{			
				SE_tileset_draw(ts,t - 1,x,y,posz);
			}

			if(v->next)v = v->next;
			
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

	SE_tile *v;
	v = tm->mapcoll;

	int t = 0;

	int value = 0;

	int i,j;

		
	for(j=0;j<ntiley;j++)
	{
		for(i=0;i<ntilex;i++)
		{	
			
			x = ((float)i*temp.w);
			y = ((float)j*temp.h);			
			
			if(v->type > 0)
			{		
				value = SE_box_check_position(&temp,&temp2,x,y,box_posx,box_posy);
				if(value > 0) return value;				
			}
						
			if(v->next)v = v->next;
			
			
		}
	}
	
	return 0;





}


void SE_tilemap_clean(SE_tilemap *tm)
{
	
	SE_tile *n1;
	SE_tile	*n2;

	while(tm->mapimage)
	{
		n1 = tm->mapimage;
		tm->mapimage = n1->next;
		free(n1);
	}
	
	while(tm->mapcoll)
	{
		n2 = tm->mapcoll;
		tm->mapcoll = n2->next;
		free(n2);
	}

	free(tm);
	

}



void SE_camera(SE_tilemap *tm,SE_tileset *ts,int xini,int yini,int wmap,int hmap,float posx,float posy,float posz)
{

	int t;
	int i,j;
	int xmap;
	int ymap;
	int xend = xini + wmap;
	int yend = yini + hmap;
	int w = tm->wtile;
	int h = tm->htile;

	int ntilex = wmap;
	int ntiley = hmap;

	float x;
	float y;
	

	for(j = 0;j < ntiley;j++)
	{
		for(i = 0;i < ntilex;i++)
		{	
			xmap = i + xini;
			ymap = j + yini;			
		
			t = tm->mapimage[SE_calc_xy(xmap,ymap,tm->numtilex,tm->numtiley)];
			x = (i*w) + posx;
			y = (j*h) + posy;			
			

			SE_tileset_draw(ts,t,x,y,posz);
			
			
		}
	}




}
*/

