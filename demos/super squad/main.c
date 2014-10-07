#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../render.h"
#include "../../image.h"
#include "../../animation.h"
#include "../../collision.h"
#include "../../sprite.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image00;
SE_image *image01;


/*creamos la estructura para la animacion*/
SE_ani *anim;

/*creamos la estructura para el sprite*/
SE_sprite *jessica;



void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image00 = SE_image_load("jessica-corre00.png");
	image01 = SE_image_load("jessica-corre01.png");


	/*iniciamos la animacion, con ancho y alto 128*/
	anim = SE_ani_init(64,128);

	/*asignamos las imagenes como frames a la animacion*/
	SE_ani_addframe(anim,image00,10);
	SE_ani_addframe(anim,image01,10);



	/*inicializamos el sprite*/
	jessica = SE_sprite_init(anim);

	/*agregamos caja de colision a sprite*/
	SE_sprite_box_add(jessica,0,0,64,128);

}





int main(int argc,char* args[])
{

	Uint8 *keys;

	/*inicializamos la variable para salir*/
	int quit = 0;
	
	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(640,480,16);

	/*llamamos a la funcion cargarsprites()*/
	cargarcosas();

	/*posicion del jugador*/
	int playerx = 0;
	int playery = 0;


	while(quit == 0)
	{
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(1,1,1,1);
			
			/*dibujamos sprite con todos los parametros disponibles*/
			SE_sprite_draw_fx(jessica,playerx,playery,0,64,128,1,1,0,0,0,1,1,1,1);
				

			/*flipamos el cuadro*/
			SE_screen_flip();

			/*codigo para mover al personaje*/
			keys=SDL_GetKeyState(NULL);

			if ((keys[SDLK_UP]) && (playery > 0)) {playery -= 1;}
			if ((keys[SDLK_DOWN]) && (playery < 352)) {playery += 1;}
			if ((keys[SDLK_LEFT]) && (playerx > 0)) {playerx -= 1;}
			if ((keys[SDLK_RIGHT]) && (playerx < 512)) {playerx += 1;}
			
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
