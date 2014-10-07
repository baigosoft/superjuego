#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../render.h"
#include "../../image.h"
#include "../../animation.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;

/*creamos la estructura para la animacion*/
SE_ani *anim;

/*creamos el animador que controla la animacion*/
SE_animator *anima;



void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image = SE_image_load("run.png");

	/*iniciamos la animacion, con ancho y alto 128*/
	anim = SE_ani_init(128,128);

	/*asignamos las imagenes como frames a la animacion*/
	SE_ani_addframe_segment(anim,image,100,0,0,128,128);
	SE_ani_addframe_segment(anim,image,100,128,0,128,128);

	/*iniciamos animador, le asignamos la animacion que controlara*/
	anima = SE_animator_init(anim);

}





int main(int argc,char* args[])
{

	/*inicializamos la variable para salir*/
	int quit = 0;
	
	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(640,480,16);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();


	while(quit == 0)
	{
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0,0,0,0);
			
			/*dibujamos la animacion con todos los parametros disponibles*/
			SE_animator_draw_fx(anima,100,100,0,256,256,1,1,0,0,0,1,1,1,1);

			/*flipamos el cuadro*/
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
