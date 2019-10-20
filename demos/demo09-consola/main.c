#include "super.h"




//SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
//SE_image *ff;
//SE_font *fuente;
//char buffer[1024];

SE_input_joystick *joystick;
SE_input_state *state;

#ifdef DREAMCAST
extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);
#endif



int main(int argc,char* args[])
{

int quit = 0;

SE_screen_init(640,480,16);
SE_console_init();

SE_input_init();
printf("hay %d joysticks disponibles\n",SE_input_enum());
joystick = SE_input_open(0);



SE_console_show();

	while(quit == 0)
	{

			SE_console_draw();


			
			state=SE_input_poll(&joystick);

				if(state->buttons & SE_QUIT) /* Handle Joystick Motion */
							quit=1;


			/*flipeamos todo el cuadro*/
			SE_screen_flip();
		
	}

return 0;

}
