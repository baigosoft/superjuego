#include <stdio.h>
#include <stdlib.h>
#include "super.h"





//SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *image;
SE_image *image2;
SE_image *image3;

SE_input_joystick *joystick;
SE_input_state *state;

int priority=0;


void cargarcosas()
{

	/*cargamos la imagen en la estructura definida*/
	image = SE_image_load("prueba.png");
	image2 = SE_image_load("prueba.png");
	image3 = SE_image_load("prueba.png");


}





int main(int argc,char* args[])
{

	/*variable para salir*/
	int quit = 0;


	/*inicializamos la pantalla con ancho,alto y cantidad de colores*/
	SE_screen_init(640,480,32);

	/*inicializamos el sistema de Input*/
	SE_input_init();
	printf("hay %d joysticks disponibles\n",SE_input_enum());
	joystick = SE_input_open(0);


	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();


	while(quit == 0)
	{
		
		/*limpiamos la pantalla con un color*/
		SE_screen_clear(0,0,0,0);
	
		/*dibujamos la imagen con todos los parametros*/	

		if(priority==0)
		{	
			SE_image_full_draw(image,100,100,0,256,256,1,1,0,0,0,1,0,0,1);
			SE_image_full_draw(image2,120,120,0,256,256,1,1,0,0,0,0,1,0,1);
			SE_image_full_draw(image3,140,140,0,256,256,1,1,0,0,0,0,0,1,1);
		}
		else if(priority==1)
		{
			SE_image_full_draw(image2,120,120,0,256,256,1,1,0,0,0,0,1,0,1);
			SE_image_full_draw(image,100,100,0,256,256,1,1,0,0,0,1,0,0,1);
			SE_image_full_draw(image3,140,140,0,256,256,1,1,0,0,0,0,0,1,1);
		}
		else if(priority==2)
		{	
			SE_image_full_draw(image2,120,120,0,256,256,1,1,0,0,0,0,1,0,1);
			SE_image_full_draw(image3,140,140,0,256,256,1,1,0,0,0,0,0,1,1);
			SE_image_full_draw(image,100,100,0,256,256,1,1,0,0,0,1,0,0,1);
		}
		/*flipeamos todo el cuadro*/
		SE_screen_flip();
	
		state=SE_input_poll(&joystick);
		printf("%d\n",state->buttons);
			if(state){	
        			

					if(state->buttons & JOY_RIGHT){  /* Handle Joystick Motion */
	
					}else if(state->buttons & JOY_LEFT){  /* Handle Joystick Motion */

					} //rotinc=0.0f;
					if(state->buttons & JOY_UP)  /* Handle Joystick Motion */
					{
						priority++;
						if(priority>2) priority=0;
						
					}
					else if(state->buttons & JOY_DOWN) /* Handle Joystick Motion */
					{
						priority--;
						if(priority<0) priority=2;
					}
					if(state->buttons & JOY_BUTTON0)  /* Handle Joystick Motion */
					{
						priority=1;
					}
					if(state->buttons & JOY_BUTTON1) /* Handle Joystick Motion */
					{
						priority=2;
					}
					if(state->buttons & SE_QUIT) /* Handle Joystick Motion */
							quit=1;
				


			}
			
					
	}

/*cerramos todo lo referido al Engine*/
	SE_input_close();
	SE_screen_close();

return 0;







}
