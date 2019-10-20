#include <stdio.h>
#include <stdlib.h>
#include "super.h"


SE_movie *pelicula;




void cargarcosas()
{

	

}





int main(int argc,char* args[])
{

	/*variable para salir*/
	int quit = 0;


	/*inicializamos la pantalla con ancho,alto y cantidad de colores*/
	SE_screen_init(640,480,32);
	
	SE_movie_init();

	pelicula = SE_movie_load("cabrio.mpeg");

	//SE_movie_play(pelicula);


	

return 0;







}
