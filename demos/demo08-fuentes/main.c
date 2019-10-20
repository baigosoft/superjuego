#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
//#include "../../render.h"
//#include "../../font.h"

#include "super.h"




SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *ff;

SE_font *fuente;



















void cargarfuente()
{

ff = SE_image_load("font512.png");
fuente = SE_font_create(ff,16,16,32,32);
SE_font_settings(fuente,20);









}





int main(int argc,char* args[])
{


int quit = 0;
int rot = 0;

SE_screen_init(640,480,32);
cargarfuente();
float rotx = 0.0f;
float roty = 0.0f;
float rotz = 0.0f;



	while(quit == 0)
	{
			SE_screen_clear(0,0,0,0);
			SE_font_draw(fuente,"QUE CAGADOR\nESTE JUANCITO",0,0,0,1,1,rotz,0,0,1,1,1,1);

/*void SE_font_draw(SE_font *fnt, char *text,float posx,float posy,float posz,float zoomx,float zoomy,float rotx,float roty,float rotz,float red,float green,float blue,float alpha)*/
			
			rotz++;
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
