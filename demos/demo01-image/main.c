#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "super.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;



void cargarcosas()
{

	/*cargamos la imagen en la estructura definida anteriormente*/
	image = SE_image_load("prueba.png");


}





int main(int argc,char* args[])
{

	/*variable para salir*/
	int quit = 0;


	/*inicializamos la pantalla con ancho,alto y cantidad de colores*/
	SE_screen_init(640,480,32);

	/*seteamos el framerate a 60 cuadros*/
	SE_timer_setframerate(60);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();


	while(quit == 0)
	{
		
		/*limpiamos la pantalla con un color*/
		SE_screen_clear(0,0,0,0);
	
		/*dibujamos la imagen con todos los parametros*/		
		SE_image_draw_fx(image,100,100,0,256,256,1,1,0,0,0,1,1,1,1);
	
		/*flipeamos todo el cuadro*/
		SE_screen_flip();

		/*controlamos el framerate con esta funcion*/
		SE_timer_waitframerate();
			
			/*trocito de codigo de SDL que usamos para detectar si se cierra la ventana*/	
			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{
					/*si el evento es salir, ponemos quit a 1 y liberamos el puntero de imagen*/
					quit = 1;
					SE_image_clean(image);
				}
			

			}
			
		
	}

return 0;







}
