#include "files.h"

SE_image *images;
SE_image *imagefont;

SE_font *fntscore;

void loadfiles()
{

	images = SE_image_load("data/images.png");
	imagefont = SE_image_load("data/font512.png");

	fntscore = SE_font_create(imagefont,16,16,32,32);

}
