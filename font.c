#include "font.h"



SE_font *SE_font_create(SE_image *img,int columns, int rows, int fontw, int fonth)
{
	
	SE_font *fnt;
	fnt = (SE_font*)malloc(sizeof(SE_font));	

	fnt->textimage = img;

	fnt->col = columns;
	fnt->row = rows;
	fnt->w = fontw;
	fnt->h = fonth;
	fnt->space = 10;
	fnt->letterspc = 0;
	fnt->lineh = 0;

	return fnt;

}


void SE_font_space_set(SE_font *fnt,int value)
{

	fnt->space = value;

}

int SE_font_space(SE_font *fnt)
{

	return fnt->space;

}


void SE_font_letterspacing_set(SE_font *fnt,int value)
{

	fnt->letterspc = value;

}

int SE_font_letterspacing(SE_font *fnt)
{

	return fnt->letterspc;

}

void SE_font_lineheight_set(SE_font *fnt,int value)
{

	fnt->lineh = value;

}

int SE_font_lineheight(SE_font *fnt)
{

	return fnt->lineh;

}

void SE_font_draw_fx(SE_font *fnt,const char *text,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,float rotx,float roty,float rotz,float red,float green,float blue,float alpha)
{

int totalc = strlen(text);
int i;
int ascii = 0;
float xtex = 0;
float ytex = 0;
float wtex = fnt->w;
float htex = fnt->h;
int col = fnt->col;
int row = fnt->row;
float x = posx;
float y = posy;

	for(i=0;i<totalc;i++)
	{

		if(text[i] == ' ')
		{	
			x += fnt->space;
		}else if(text[i] == '\n'){
			x = posx;
			y += htex + (fnt->lineh);
		}else{
			ascii = (unsigned char)text[i];
			xtex = (ascii % col) * wtex;
			ytex = (ascii / col) * htex;

			SE_image_segment_draw_fx(fnt->textimage,xtex,ytex,wtex,htex,x,y,0,width,height,zoomx,zoomy,rotx,roty,rotz,red,green,blue,alpha);

			x += wtex + (fnt->letterspc);

			
		}
		
	}
}

void SE_font_draw(SE_font *fnt,const char *text,float posx,float posy,float posz)
{

	SE_font_draw_fx(fnt,text,posx,posy,posz,fnt->w,fnt->h,1,1,0,0,0,1,1,1,1);

}

void SE_font_draw_transf(SE_font *fnt,SE_transf *tr,const char *text)
{

	SE_font_draw_fx(fnt,
					text,
					tr->x,tr->y,tr->z,
					tr->width,tr->height,
					tr->zoomx,tr->zoomy,
					tr->rotx,tr->roty,tr->rotz,
					tr->r,tr->g,tr->b,tr->alpha);


}

void SE_font_clean(SE_font *fnt)
{

	SE_image_clean(fnt->textimage);
	free(fnt);
	if(fnt != 0)
	{
		printf("error, no se pudo borrar puntero de fuente");
	}

}
