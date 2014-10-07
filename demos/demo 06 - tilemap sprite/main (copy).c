#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../render.h"
#include "../../image.h"
#include "../../animation.h"
#include "../../sprite.h"
#include "../../collision.h"
#include "../../tile.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image00;
SE_image *image01;


/*creamos las animaciones*/
SE_ani *ani00;
SE_ani *ani01;


/*creamos el tileset*/
SE_tileset *tset;

/*creamos el tilemap*/
SE_tilemap *timap;

/*creamos las imagenes del personaje*/
SE_image *imgchara01;
SE_image *imgchara02;

/*creamos la animacion del personaje*/
SE_ani *anichara;

/*creamos la estructura para el sprite del personaje*/
SE_sprite *sprchara;

void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image00 = SE_image_load("tile01.png");
	image01 = SE_image_load("tile02.png");


	/*inicializamos las animaciones*/
	ani00 = SE_ani_init(32,32);
	ani01 = SE_ani_init(32,32);

	
	/*cargamos las animaciones con imagenes*/
	SE_ani_addframe(ani00,image00,10);
	SE_ani_addframe(ani01,image01,10);


	/*inicializamos tileset*/
	tset = SE_tileset_init(32,32);

	/*cargamos el tileset con animaciones*/
	SE_tileset_animation_add(tset,ani00);
	SE_tileset_animation_add(tset,ani01);


	/*inicializamos tilemap*/
	timap = SE_tilemap_init(7,32,32,20,15);

	/*cargamos tilemap con el archivo de texto*/
	SE_tilemap_mapimage_load(timap,"mapa.txt");
	SE_tilemap_mapcollision_load(timap,"mapacollision.txt");

	imgchara01 = SE_image_load("chara01.png");
	imgchara02 = SE_image_load("chara02.png");

	anichara = SE_ani_init(64,64);

	SE_ani_addframe(anichara,imgchara01,30);
	SE_ani_addframe(anichara,imgchara02,30);

	sprchara = SE_sprite_init(anichara);

	SE_sprite_box_add(sprchara,0,0,64,64);
	



}





int main(int argc,char* args[])
{

	Uint8 *keys;

	/*variable para salir*/
	int quit = 0;


	
	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(640,480,16);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();

	/*posicion del jugador*/
	int playerx = 0;
	int playery = 0;
	int tilex = 0;
	int tiley = 0;

	int valor = 0;

	
	while(quit == 0)
	{
		
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0,0,0,0);

			SE_tilemap_draw(timap,tset,tilex,tiley,0);

			

			SE_sprite_draw_fx(sprchara,playerx,playery,0,64,64,1,1,0,0,0,1,1,1,1);


			/*flipamos el cuadro*/
			SE_screen_flip();

			keys=SDL_GetKeyState(NULL);

			if (keys[SDLK_UP]) 
			{
				playery -= 1;
				if(SE_tilemap_collision(timap,sprchara->box,tilex,tiley,playerx,playery) > 0) playery +=1;
			}
			if (keys[SDLK_DOWN]) 
			{
				playery += 1;
				if(SE_tilemap_collision(timap,sprchara->box,tilex,tiley,playerx,playery) > 0) playery -=1;
			}
			if (keys[SDLK_LEFT])
			{
				playerx -= 1;
				if(SE_tilemap_collision(timap,sprchara->box,tilex,tiley,playerx,playery) > 0) playerx +=1;
			}
			if (keys[SDLK_RIGHT])
			{
				playerx += 1;
				if(SE_tilemap_collision(timap,sprchara->box,tilex,tiley,playerx,playery) > 0) playerx -=1;
			}
		
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
