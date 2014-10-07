#ifndef FONT_H_
#define FONT_H_

#include "image.h"
#include "string.h"


typedef struct
{

	SE_image *textimage;
	int numletters;
	int w,h;
	int col,row;
	int space;


}SE_font;





SE_font *SE_font_create(SE_image *img,int columns, int rows, int fontw, int fonth);

void SE_font_settings(SE_font *fnt,int space);

void SE_font_draw_fx(SE_font *fnt, char *text,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,float rotx,float roty,float rotz,float red,float green,float blue,float alpha);

void SE_font_draw(SE_font *fnt, char *text,float posx,float posy,float posz);

void SE_font_clean(SE_font *fnt);





























#endif
