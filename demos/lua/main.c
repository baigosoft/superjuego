#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "super.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;



void cargarcosas()
{




}





int main(int argc,char* args[])
{

	/*variable para salir*/
	int quit = 0;

	//SE_screen_init(640,480,32);

	SE_lua_init("test.lua");

	printf("chau");

	/*
	while(quit == 0)
	{
		
		
			

			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{

					quit = 1;

				}
			

			}
			
		
	}
	*/

return 0;







}
