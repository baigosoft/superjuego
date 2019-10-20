#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

/*source del juego*/
#include "game.h"


Uint32 frametime;



int main(int argc,char* args[])
{

	quit = 0;

	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(640,480,16);


	loadfiles();

	board *tablero;
	tablero = init_board(10,20,16,16);

	int aux = 0;

	SE_input_init();

	printf("hay %d joysticks disponibles\n",SE_input_enum());
	joystick = SE_input_open(0);

	while(quit == 0)
	{
			ResetTimeBase();
	
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0.4,0.2,0.8,0);

			/*piece_set_position(tablero,-2,16);

			piece_set_current(tablero,2);
		
			insert_piece(tablero);

			draw_board(tablero);

			draw_piece(tablero);*/

			draw_scene(tablero);
			
			/*flipamos el cuadro*/
			SE_screen_flip();

			do{
				frametime=CurrentTime();	
			} while (frametime<17);


	}

return 0;







}
