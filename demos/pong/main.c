#include <stdio.h>
#include <stdlib.h>
#include "super.h"



SE_input_state *state;
SE_input_joystick *joystick;

/*creamos la estructura para almacenar las imágenes*/
SE_image *p1_image;
SE_image *p2_image;
SE_image *ball_image;

SE_image *ff;
SE_font *fuentep1;
SE_font *fuentep2;

char marcador[5];

int ballxvel,ballyvel;

SE_box p1, p2, ball; /*rectangulos de colisión*/

 /*puntajes*/
int p1_score, p2_score;
char marcador1[2];
char marcador2[2];


int paddle_speed=5; /*velocidad del paddle al moverlo*/

int estado=0; /*estado del juego: 0 si se esta jugando, 1 si p1 gano el punto, 2 si p2 gano el punto*/



void cargarRecursos()
{

	/*cargamos la imágenes en las estructuras definidas anteriormente*/
	p1_image = SE_image_load("resources/left_pallete.png");
	p2_image = SE_image_load("resources/left_pallete.png");
	ball_image = SE_image_load("resources/ball.png");

	ff = SE_image_load("resources/font512.png");
	fuentep1 = SE_font_create(ff,16,16,32,32);
	fuentep2 = SE_font_create(ff,16,16,32,32);
//	SE_font_settings(fuente,20);

}

int intersectrect(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
	if (x1 > x2 + width2)
		return 0;
	if (y1 > y2 + height2)
		return 0;
	if (y2 > y1 + height1)
		return 0;
	if (x2 > x1 + width1)
		return 0;

	return 1;
}

void posicionarCosas()
{
	/*posicionamos los jugadores y la bola*/
	p1.x = 100;
	p2.x = 540;
	p1.y = 240;
	p2.y = 240;

	p1.w = 8;
	p1.h = 32;
	p2.w = 8;
	p2.h = 32;

	ball.x = 100;
	ball.y = 100;
	ball.w = 8;
	ball.h = 8;

	ballxvel = 2;
	ballyvel = 3;
}


/*retorna 1 si gana el p1, 2 si gana el p2*/
int chequearColisiones()
{

/*chequear rebote contra paredes*/
if((ball.y+ball.h>=480)||(ball.y-ball.h<=0))
{
	ballyvel=-ballyvel;
}

if(SE_coll_check(&p1, &ball)==1)
{
	ballxvel=-ballxvel;
//	printf("col p1\n");
}

if(SE_coll_check(&p2, &ball)==1)
{
	ballxvel=-ballxvel;
//	printf("col p2\n");
}

/*chequear si algun jugador gano el punto*/
if(ball.x+ball.w>=640)
{
//	printf("punto jugador 1\n");
	p1_score+=1;
	posicionarCosas();
}

/*chequear si algun jugador gano el punto*/
if(ball.x-ball.w<=0)
{
//	printf("punto jugador 2\n");
	p2_score+=1;
	posicionarCosas();
}

return 0;
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

	/*seteamos el framerate a 60 cuadros*/
	SE_timer_setframerate(60);

	/*llamamos a la funcion para cargar los recursos*/
	cargarRecursos();

	/*posicionamiento inicial de los objetos*/
	posicionarCosas();

	while(quit == 0)
	{
		
		/*limpiamos la pantalla con un color*/
		SE_screen_clear(0,0,0,0);
	
		if(state=SE_input_poll(&joystick)){	
        			

					if(state->buttons & JOY_UP)  /* Paddle hacia arriba */
					{
						if(p1.y-paddle_speed>=0)
						{
						p1.y=p1.y-paddle_speed;
						p2.y=p2.y-paddle_speed;
						}
						//printf("UP!\n");
					}
					else if(state->buttons & JOY_DOWN) /* Paddle hacia abajo */
					{
						if(p1.y+p1.h+paddle_speed<=480)
						{
						p1.y=p1.y+paddle_speed;
						p2.y=p2.y+paddle_speed;
						}
						//printf("DOWN!\n");
					}
					if(state->buttons & SE_QUIT) /* Evento para salir */
					{
						quit=1;
						//printf("QUIT!\n");
					}
				


		}

		ball.x=ball.x+ballxvel;
		ball.y=ball.y+ballyvel;

		estado=chequearColisiones();

		if(estado == 1) /*gano p1*/
		{

		}
		else if(estado == 2) /*gano p2*/
		{

		}else /*el juego sigue*/
		{

		}

		sprintf(marcador1,"%d",p1_score);
		sprintf(marcador2,"%d",p2_score);

		/*dibujamos la imagen con todos los parametros*/		
		SE_image_draw_fx(p1_image,p1.x,p1.y,0,p1.w,p1.h,1,1,0,0,0,1,1,1,1);
		SE_image_draw_fx(p2_image,p2.x,p2.y,0,p2.w,p2.h,1,1,0,0,0,1,1,1,1);
		SE_image_draw_fx(ball_image,ball.x,ball.y,0,ball.w,ball.h,1,1,0,0,0,1,1,1,1);

		SE_font_draw(fuentep1,marcador1,320-64,0,0);
		SE_font_draw(fuentep2,marcador2,320+32,0,0);
	
		/*flipeamos todo el cuadro*/
		SE_screen_flip();

		/*controlamos el framerate con esta funcion*/
		SE_timer_waitframerate();
		
	}



/*limpiamos la memoria antes de salir*/
SE_image_clean(p1_image);
SE_image_clean(p2_image);
SE_image_clean(ball_image);

SE_input_close();
//SE_screen_close();


return 0;







}
