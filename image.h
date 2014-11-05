#ifndef IMAGE_H_
#define IMAGE_H_


#include "render.h"


extern int powerof2(int number);



typedef struct
{

	GLuint texture;/*the texture*/

	int width,height;/*width and height*/

}SE_image;

/*load texture*/
GLuint loadTexture(SDL_Surface *surface);

/*load image*/
SE_image *SE_image_load(char *path);


/*returns width and height*/
float SE_image_width(SE_image *img);
float SE_image_height(SE_image *img);

/*draw a rectangular segment of an image, with a lot of parameters*/
void SE_image_segment_draw_fx(SE_image *img,
						   float xtex,float ytex,float wtex,float htex,
						   float posx,float posy,float posz,
						   float width_image,float height_image,
						   float zoomx,float zoomy,
						   float rotx,float roty,float rotz,
						   float r,float g,float b,
						   float alpha);

/*draw a rectangular segment of an image, with position and dimentions parameters*/
void SE_image_segment_draw_wh(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz,float width,float height);

/*draw a rectangular segment of an image, with position parameters*/
void SE_image_segment_draw(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz);

/*draw a full area of an image, with a lot of parameters*/
void SE_image_draw_fx(SE_image *img,
					  float posx,float posy,float posz,
					  float width_image,float height_image,
					  float zoomx,float zoomy,
					  float rotx,float roty,float rotz,
					  float r,float g,float b,
					  float alpha);

/*draw a full area of an image, with position and dimentions parameters*/
void SE_image_draw_wh(SE_image *img,float posx,float posy,float posz,float width,float height);

/*draw a full area of an image, with position parameters */
void SE_image_draw(SE_image *img,float posx,float posy,float posz);

/*draw a rectangular segment of an image, with values loaded previously (np: no parameters)*/
void SE_image_segment_draw_transf(SE_image *img,SE_transf *tr,float xtex,float ytex,float wtex,float htex);

/*draw a full area of an image, with values loaded previously (np: no parameters)*/
void SE_image_draw_transf(SE_image *img,SE_transf *tr);

/*clean image*/
void SE_image_clean(SE_image *img);




#endif
