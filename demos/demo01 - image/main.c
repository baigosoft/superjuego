#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../render.h"
#include "../../image.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;



void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image = SE_image_load("prueba.png");


}





int main(int argc,char* args[])
{

	/*variable para salir*/
	int quit = 0;


	/*inicializamos la pantalla con ancho,alto y cantidad de colores*/
	SE_screen_init(640,480,32);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();


	while(quit == 0)
	{
		
		/*limpiamos la pantalla con un color*/
		SE_screen_clear(0,0,0,0);
	
		/*dibujamos la imagen con todos los parametros*/		
		SE_image_full_draw(image,100,100,0,256,256,1,1,0,0,0,1,1,1,1);
	
		/*flipeamos todo el cuadro*/
		SE_screen_flip();

			
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
