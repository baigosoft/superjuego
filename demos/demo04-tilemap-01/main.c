#include "super.h"





SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;

SE_tileset *tiset;

SE_tilemap *timap;


void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image = SE_image_load("tiles.png");

	/*inicializamos tileset (9 imagenes de 32 x 32)*/
	tiset = SE_tileset_init(9,32,32);

	/*agregamos las imagenes al tileset, aqui cargamos una imagen y luego colocamos las coordenadas en la textura*/
	SE_tileset_img_segment_add(tiset,image,0,0,0,32,32);
	SE_tileset_img_segment_add(tiset,image,1,32,0,32,32);
	SE_tileset_img_segment_add(tiset,image,2,64,0,32,32);
	SE_tileset_img_segment_add(tiset,image,3,96,0,32,32);
	SE_tileset_img_segment_add(tiset,image,4,128,0,32,32);
	SE_tileset_img_segment_add(tiset,image,5,160,0,32,32);
	SE_tileset_img_segment_add(tiset,image,6,192,0,32,32);
	SE_tileset_img_segment_add(tiset,image,7,224,0,32,32);
	SE_tileset_img_segment_add(tiset,image,8,0,32,32,32);

	/*inicializamos tilemap*/
	timap = SE_tilemap_init(tiset,9,32,32,20,15);

	/*cargamos el mapa en memoria*/
	SE_tilemap_maptile_load(timap,"map.txt");


}





int main(int argc,char* args[])
{


	int quit = 0;


	/*inicializamos pantalla (640 x 480 x 32 bits de color)*/
	SE_screen_init(640,480,32);

	/*seteamos el framerate a 60 cuadros*/
	SE_timer_setframerate(60);

	/*cargamos las cosas necesarias*/
	cargarcosas();




	while(quit == 0)
	{
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0,0,0,0);

			/*dibujamos el tilemap en la posicion x=0,y=0,z=0*/
			SE_tilemap_draw(timap,0,0,0);		


			/*flipeamos todo el cuadro*/
			SE_screen_flip();

			/*controlamos el framerate con esta funcion*/
			SE_timer_waitframerate();
			
			/*trocito de codigo de SDL que usamos para detectar si se cierra la ventana*/	
			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{
					/*si el evento es salir, ponemos quit a 1 y liberamos el puntero de tilemap,tileset e imagen (en ese orden)*/
					quit = 1;
					SE_tilemap_clean(timap);
					SE_tileset_clean(tiset);
					SE_image_clean(image);
				}
			

			}


			

			
				

			
		
	}

return 0;







}
