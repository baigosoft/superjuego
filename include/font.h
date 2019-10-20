#ifndef FONT_H_
#define FONT_H_

#include "transform.h"
#include "image.h"
#include "string.h"


typedef struct
{

	SE_image *textimage;
	int numletters;
	int w,h;
	int col,row;
	int space;/*valor de espacio en blanco*/
	int letterspc;/*letter spacing*/
	int lineh;/*line height*/
	


}SE_font;





SE_font *SE_font_create(SE_image *img,int columns, int rows, int fontw, int fonth);/*crea fuente*/

void SE_font_space_set(SE_font *fnt,int value);/*setea espacio en blanco*/

int SE_font_space(SE_font *fnt);/*devuelve valor de espacio en blanco*/

void SE_font_letterspacing_set(SE_font *fnt,int value);/*setea valor de espacio entre letras*/

int SE_font_letterspacing(SE_font *fnt);/*devuelve valor de espacio entre letras*/

void SE_font_lineheight_set(SE_font *fnt,int value);/*setea valor de espacio entre lineas*/

int SE_font_lineheight(SE_font *fnt);/*devuelve valor de espacio entre lineas*/

/*renderiza el texto con todos los atributos disponibles*/
void SE_font_draw_fx(SE_font *fnt, 
					 const char *text,
					 float posx,float posy,float posz,
					 float width,float height,
					 float zoomx,float zoomy,
					 float rotx,float roty,float rotz,
					 float red,float green,float blue,
					 float alpha);

/*renderiza el texto con atributos de posicion*/
void SE_font_draw(SE_font *fnt,const char *text,float posx,float posy,float posz);

/*renderiza el texto con SE_transf*/
void SE_font_draw_transf(SE_font *fnt,SE_transf *tr,const char *text);

/*borra la fuente*/
void SE_font_clean(SE_font *fnt);





























#endif
