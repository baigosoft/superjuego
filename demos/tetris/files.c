#include "files.h"

SE_image *images;
SE_image *imagefont;

void loadfiles()
{

	images = SE_image_load("images.png");
	imagefont = SE_image_load("font512.png");

}
