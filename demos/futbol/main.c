#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../render.h"
#include "../../image.h"
#include "../../animation.h"
#include "../../collision.h"
#include "../../sprite.h"
#include "ball.h"
#include "field.h"
#include "player.h"
#include "team.h"





SDL_Event event;











int field_to_screen(int value_field,int dx_screen)
{
	
	/*la idea es que convierta a pixeles, mediante un diferencial
		Ejemplo:
			10000 cm -> 600 px
			10 cm -> x = (10*600)/10000 = dx = 0,6 px aprox. igual a 1 px
			la idea es usar un diferencial lo más redondeado posible, que se yo
	*/

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

	


	while(quit == 0)
	{
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(1,1,1,1);
			
			/*dibujamos sprite con todos los parametros disponibles*/
			SE_sprite_draw_fx(penguin,playerx,playery,0,128,128,1,1,0,0,0,1,1,1,1);
				

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
