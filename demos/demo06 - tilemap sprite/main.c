#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "super.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *tile01;
SE_image *tile02;
SE_image *tile;



/*creamos el tileset*/
SE_tileset *tileset01;

/*creamos el tilemap*/
SE_tilemap *tilemap01;

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
	

	tile = SE_image_load("tiles.png");	
	//tile01 = SE_image_load("tile01.png");
	//tile02 = SE_image_load("tile02.png");

	/*inicializamos tileset*/
	tileset01 = SE_tileset_init(2,32,32);

	//SE_tileset_img_add(tileset01,tile01,0);
	//SE_tileset_img_add(tileset01,tile02,1);

	SE_tileset_img_segment_add(tileset01,tile,0,0,0);
	SE_tileset_img_segment_add(tileset01,tile,1,32,0);


	/*inicializamos tilemap*/
	tilemap01 = SE_tilemap_init(tileset01,2,32,32,20,15);

	/*cargamos tilemap con el archivo de texto*/
	SE_tilemap_maptile_load(tilemap01,"mapa.txt");
	SE_tilemap_mapcoll_load(tilemap01,"mapacollision.txt");

	imgchara01 = SE_image_load("chara01.png");
	imgchara02 = SE_image_load("chara02.png");

	anichara = SE_ani_init(64,64,2);

	SE_ani_addframe(anichara,imgchara01,0,30);
	SE_ani_addframe(anichara,imgchara02,1,30);

	sprchara = SE_sprite_init(anichara);

	SE_sprite_box_init(sprchara,1);
	SE_sprite_box_set(sprchara,0,0,0,64,64);
	
}





int main(int argc,char* args[])
{

	Uint8 *keys;

	/*variable para salir*/
	int quit = 0;


	
	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(640,480,32);

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

			SE_tilemap_draw(tilemap01,0,0,0);

			//SE_tileset_draw(tileset01,0,100,0,0);
		
			SE_sprite_draw(sprchara,playerx,playery,0);


			/*flipamos el cuadro*/
			SE_screen_flip();

			keys=SDL_GetKeyState(NULL);

			if (keys[SDLK_UP]) 
			{
				playery -= 1;
				if(SE_tilemap_collision(tilemap01,tilex,tiley,sprchara->box,playerx,playery) > 0) playery +=1;
			}
			if (keys[SDLK_DOWN]) 
			{
				playery += 1;
				if(SE_tilemap_collision(tilemap01,tilex,tiley,sprchara->box,playerx,playery) > 0) playery -=1;
			}
			if (keys[SDLK_LEFT])
			{
				playerx -= 1;
				if(SE_tilemap_collision(tilemap01,tilex,tiley,sprchara->box,playerx,playery) > 0) playerx +=1;
			}
			if (keys[SDLK_RIGHT])
			{
				playerx += 1;
				if(SE_tilemap_collision(tilemap01,tilex,tiley,sprchara->box,playerx,playery) > 0) playerx -=1;
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
