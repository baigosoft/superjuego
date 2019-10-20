#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "super.h"






SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;

SE_tilemap *timap;




















void cargarsprites()
{

/*cargamos la imagen en la estructura definida*/
image = SE_image_load("tiles.png");

timap = SE_tilemap_init(32,32,20,15);

SE_tilemap_addimage_segment(timap,image,0,0,32,32);
SE_tilemap_addimage_segment(timap,image,32,0,32,32);
SE_tilemap_addimage_segment(timap,image,64,0,32,32);
SE_tilemap_addimage_segment(timap,image,96,0,32,32);
SE_tilemap_addimage_segment(timap,image,128,0,32,32);
SE_tilemap_addimage_segment(timap,image,160,0,32,32);
SE_tilemap_addimage_segment(timap,image,192,0,32,32);
SE_tilemap_addimage_segment(timap,image,224,0,32,32);
SE_tilemap_addimage_segment(timap,image,0,32,32,32);

SE_tilemap_loadmapimage(timap,"mapimage.txt");











}





int main(int argc,char* args[])
{


int quit = 0;
int rot = 0;


SE_initgraphics();
cargarsprites();

float rota = 0.0;
float rota2 = 0.0;


	while(quit == 0)
	{
		
			SE_clearscreen(0,0,0,0);
				
			SE_tilemap_draw(timap,0,0,0);		





		
		
			rota++;


		


		

			





		

			/*SE_image_draw(image);*/

			/*flipeamos todo el cuadro*/
			SE_flip();
			
			/*trocito de codigo de SDL que usamos para detectar si se cierra la ventana*/	
			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{
					quit = 1;
				}
			

			}


			

			
				

			
		
	}

return 0;







}
