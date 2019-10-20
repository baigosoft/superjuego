#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "super.h"




#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define JUEGO_PARADO 0
#define JUEGO_INICIADO 1
#define JUEGO_LISTO 2


#define DETENIDO 0
#define NORMAL 1
#define SALTAR 2
#define CHOCADO 3
#define MUERTO 4

int quit;
int estado;

int intro_ciclos;
int intro_estado;

int xfondo,yfondo;

int contletra,contpos;

SDL_Event event;

/*creamos la estructura para almacenar la imagen*/
SE_image *imagenes;


/*creamos la estructura para la animacion del personaje*/
SE_ani *pajaro_ani;

/*creamos la estructura para el sprite del personaje*/
SE_sprite *spajaro;

/*tubo 1*/
SE_ani *tubo1_ani;


/*tubo 2*/
SE_ani *tubo2_ani;

/*fuente*/
SE_image *imgfuente;
SE_font *fuente;

typedef struct
{

	char nombre[3];
	int puntaje;
	
}record;

typedef struct
{

	record *reclista; 
	int numrecords;

}hiscore;


typedef struct
{

	SE_sprite *stubo1;
	SE_sprite *stubo2;
	float posx,posy,posz;

}tubo; 

typedef struct
{

	tubo **arraytubo;
	float separacionx;
	float velx;
	float espacioy;
	int numtubos;
	float w_tubo,h_tubo;


}tubos;


typedef struct
{

	SE_sprite *spajaro;
	float posx,posy,posz;
	float width,height;
	float gravedad;
	int estado;
	int puntuacion;
	int ciclos;
	float rotacion;
	char nombre[3];

}jugador;


tubos *t;
jugador *jug;


hiscore *top10;

void iniciarhiscore(int numrecords)
{

	top10 = (hiscore*)malloc(sizeof(hiscore));
	top10->numrecords = numrecords;
	top10->reclista = (record*)malloc(numrecords*sizeof(record)); 

	strcpy(top10->reclista[0].nombre,"aaa");
	top10->reclista[0].puntaje = 11;
	strcpy(top10->reclista[1].nombre,"bbb");
	top10->reclista[1].puntaje = 10;
	strcpy(top10->reclista[2].nombre,"ccc");
	top10->reclista[2].puntaje = 9;
	strcpy(top10->reclista[3].nombre,"ddd");
	top10->reclista[3].puntaje = 8;
	strcpy(top10->reclista[4].nombre,"eee");
	top10->reclista[4].puntaje = 7;
	strcpy(top10->reclista[5].nombre,"fff");
	top10->reclista[5].puntaje = 6;
	strcpy(top10->reclista[6].nombre,"ggg");
	top10->reclista[6].puntaje = 5;
	strcpy(top10->reclista[7].nombre,"hhh");
	top10->reclista[7].puntaje = 4;
	strcpy(top10->reclista[8].nombre,"iii");
	top10->reclista[8].puntaje = 3;
	strcpy(top10->reclista[9].nombre,"jjj");
	top10->reclista[9].puntaje = 2;

}

void insertarrecord(char nombre[3],int puntaje)
{

	int i;

	int flag = 0;

	int numrecords = top10->numrecords;	

	record *rectmp;

	rectmp = (record*)malloc(numrecords*sizeof(record));

	for(i=0;i<numrecords;i++)
	{

		strcpy(rectmp[i].nombre,top10->reclista[i].nombre);
		rectmp[i].puntaje = top10->reclista[i].puntaje;
		
	}
	
	for(i=0;i<numrecords;i++)
	{
		if(flag == 1)
		{

			strcpy(top10->reclista[i].nombre,rectmp[i-1].nombre);
			top10->reclista[9].puntaje = rectmp[i-1].puntaje; 

		}else if(puntaje >= (rectmp[i].puntaje)){

			strcpy(top10->reclista[i].nombre,nombre);
			top10->reclista[i].puntaje = puntaje;
			flag = 1;	

		}

	}

	free(rectmp);
	
	
}

int compararpuntos()
{
	
	int i;
	
	for(i=0;i<(top10->numrecords);i++)
	{
		
		if((jug->puntuacion) >=  (top10->reclista[i].puntaje))
		{

			return 1;

		}

	}
	
	return 0;

}

int insertariniciales()
{
	
	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{

			case SDL_KEYDOWN:
	
				switch( event.key.keysym.sym )
				{
					case SDLK_UP:	
						jug->nombre[contpos]++;					
						if(jug->nombre[contpos] > 126)
						{					
							jug->nombre[contpos] = 33;
						}	
						break;
					case SDLK_z:
						contpos++;
						if(contpos > 2)
						{						
							return 1;
						}
						break;
					case SDLK_1:
						return 1;
						break;	
					default:
						break;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
            
			default:                
				break;			
		}
	}			
	return 0;

}

void dibujarhighscore(float posx,float posy,float posz,int espaciox,int espacioy)
{

	int i;

	char puntaje[100];
	int numrecords = top10->numrecords;	


	for(i=0;i<numrecords;i++)
	{
		sprintf(puntaje,"%d",top10->reclista[i].puntaje);
		SE_font_draw_fx(fuente,top10->reclista[i].nombre,posx,posy + i*espacioy,0,32,32,1,1,0,0,0,0,0,1,1);
		SE_font_draw_fx(fuente,puntaje,posx + espaciox,posy + i*espacioy,0,32,32,1,1,0,0,0,1,0,0,1);
	}


}





void iniciartubos(float separacionx,float velocidadx,float espacioy,int numtubos,float w_tubo,float h_tubo)
{

	float pos = SCREEN_WIDTH;
	int i;
	t = (tubos*)malloc(sizeof(tubos));

	t->numtubos = numtubos;
	t->separacionx = separacionx;
	t->espacioy = espacioy;
	t->velx = velocidadx;
	t->w_tubo = w_tubo;
	t->h_tubo = h_tubo;
		
	t->arraytubo = (tubo**)malloc(numtubos*sizeof(tubo*));
	
	for(i=0;i<numtubos;i++)
	{

		t->arraytubo[i] = (tubo*)malloc(sizeof(tubo));
		if(i>0)
		{	
			pos = w_tubo + pos + separacionx;
		}else{
			pos = SCREEN_WIDTH;
		}
		t->arraytubo[i]->posx = pos;
		t->arraytubo[i]->posy = -512 + rand() % 200;
		t->arraytubo[i]->posz = 0;

	}
	
}


void movertubos()
{

	int i;
	int numtubos = t->numtubos;
	float w_tubo = t->w_tubo;
	float separacionx = t->separacionx;

	if(estado == JUEGO_LISTO)
	{
		for(i=0;i<numtubos;i++)
		{
	

			if((t->arraytubo[i]->posx) < (-(w_tubo + separacionx)))
			{ 
				t->arraytubo[i]->posx = SCREEN_WIDTH + w_tubo + separacionx;
				t->arraytubo[i]->posy = -512 + rand() % 200;					
			}else{
				t->arraytubo[i]->posx -= t->velx;
			}
		}	
	}	

}

void dibujartubos()
{

	int i;
	float posx,posy,posy_2,posz;
	float w_tubo = t->w_tubo;
	float h_tubo = t->h_tubo;
	float espacioy = t->espacioy;
	int numtubos = t->numtubos;
	posy_2 = 0;

	for(i=0;i<numtubos;i++)
	{

		posx = t->arraytubo[i]->posx;
		posy = t->arraytubo[i]->posy;
		posy_2 = posy + h_tubo + espacioy;
		posz = t->arraytubo[i]->posz;
		SE_sprite_draw_wh(t->arraytubo[i]->stubo1,posx,posy,posz,w_tubo,h_tubo);
		SE_sprite_draw_wh(t->arraytubo[i]->stubo2,posx,posy_2,posz,w_tubo,h_tubo);

		if((jug->posx) == (posx + w_tubo))
		{
			
			jug->puntuacion++;
			
		}

	}	

}

void limpiartubos()
{

	

}

void iniciarjugador(float posx,float posy,float posz,float gravedad)
{

	jug = (jugador*)malloc(sizeof(jugador));
	jug->posx = posx;
	jug->posy = posy;
	jug->posz = posz;
	jug->width = 64;
	jug->height = 64;
	jug->gravedad = gravedad;
	jug->estado = 1;
	jug->ciclos = 0;
	jug->puntuacion = 0;
	jug->rotacion = 0;
	strcpy(jug->nombre,"AAA");

	
}


void cargarimagenes()
{

	imagenes = SE_image_load("imagenes.png");
	imgfuente = SE_image_load("font512.png");

}

void cargarfuente()
{

	fuente = SE_font_create(imgfuente,16,16,32,32);
	SE_font_letterspacing_set(fuente,20);

}

void dibujarpuntuacion()
{

	char buffer[20];
	sprintf(buffer,"%d",jug->puntuacion);
	SE_font_draw_fx(fuente,buffer,280,10,0,32,32,2,2,0,0,0,1,1,1,1);

}

void cargartubos()
{

	int i;
	int numtubos = t->numtubos;

	/*tubo1_ani = SE_ani_init(128,305,1);
	SE_ani_addframe_segment(tubo1_ani,imagenes,30,128,0,106,512);

	tubo2_ani = SE_ani_init(128,305,1);
	SE_ani_addframe_segment(tubo2_ani,imagenes,30,234,0,106,512);*/

	for(i=0;i<numtubos;i++)
	{

		//t->arraytubo[i]->stubo1 = SE_sprite_init(tubo1_ani);
		//t->arraytubo[i]->stubo2 = SE_sprite_init(tubo2_ani);
		t->arraytubo[i]->stubo1 = SE_sprite_init(IMG);
		t->arraytubo[i]->stubo2 = SE_sprite_init(IMG);
		SE_sprite_img_segment_add(t->arraytubo[i]->stubo1,imagenes,128,0,106,512);
		SE_sprite_img_segment_add(t->arraytubo[i]->stubo2,imagenes,234,0,106,512);
		SE_sprite_box_init(t->arraytubo[i]->stubo1,2);
		SE_sprite_box_init(t->arraytubo[i]->stubo2,2);
		SE_sprite_box_set(t->arraytubo[i]->stubo1,0,20,0,70,512);
		SE_sprite_box_set(t->arraytubo[i]->stubo1,1,0,450,106,62);
		SE_sprite_box_set(t->arraytubo[i]->stubo2,0,0,0,106,62);
		SE_sprite_box_set(t->arraytubo[i]->stubo2,0,20,0,70,512);
		
	}	

}


void cargarjugador()
{

	pajaro_ani = SE_ani_init(64,64,2);
	SE_ani_addframe_segment(pajaro_ani,imagenes,0,20,0,0,64,64);	
	SE_ani_addframe_segment(pajaro_ani,imagenes,1,20,64,0,64,64);	

	//jug->spajaro = SE_sprite_init(pajaro_ani);
	jug->spajaro = SE_sprite_init(ANI);
	SE_sprite_ani_add(jug->spajaro,pajaro_ani);
	SE_sprite_box_init(jug->spajaro,1);				
	SE_sprite_box_set(jug->spajaro,0,11,13,44,37);
		
}

void jugadorestado(int estado)
{

	jug->estado = estado;

}

int controlarcolision()
{

	int i;
	float posx,posy,posy_2,posz;
	float w_tubo = t->w_tubo;
	float h_tubo = t->h_tubo;
	float espacioy = t->espacioy;
	int numtubos = t->numtubos;
	int res1 = 0;
    int res2 = 0;
	int n_tubo = 0;
	int cont = 0;
	
	for(i=0;i<numtubos;i++)
	{

		posx = t->arraytubo[i]->posx;
		posy = t->arraytubo[i]->posy;
		posy_2 = posy + h_tubo + espacioy;
		posz = t->arraytubo[i]->posz;

		res1 = SE_sprite_collision(jug->spajaro,t->arraytubo[i]->stubo1,jug->posx,jug->posy,posx,posy);
		res2 = SE_sprite_collision(jug->spajaro,t->arraytubo[i]->stubo2,jug->posx,jug->posy,posx,posy_2);


		if((res1 > 0)||(res2 > 0))
		{	
			return 1;
		}	
		
		
		
	}

	return 0;

}

void moverjugador()
{


	switch(jug->estado)
	{
		case DETENIDO:		
				jug->posy = 200 + 6*sin(0.1*(jug->ciclos));
				if(jug->ciclos < 1000)
				{
					jug->ciclos++;
				}else{
					jug->ciclos = 0;
				}
			break;
		case NORMAL:
		
				jug->posy += (jug->gravedad)*(jug->ciclos);

				jug->rotacion += 0.3*jug->ciclos;

				if(jug->rotacion > 90)
				{
					jug->rotacion = 90;
				}
		
				if(jug->posy < SCREEN_HEIGHT)
				{
					jug->ciclos++;
				}else{
					jug->ciclos = 0;
					jugadorestado(MUERTO);
				}				

			break;
		case SALTAR:

				jug->rotacion -= 0.5*jug->ciclos;

				if(jug->rotacion < -30)
				{
					jug->rotacion = -30;
				}

				if(jug->ciclos < 22)
				{	
					jug->posy -= 0.3*(jug->ciclos);
					yfondo += 0.09*(jug->ciclos);
					jug->ciclos++;
				}else{
					jug->ciclos = 0;
					yfondo = 350;
					jugadorestado(NORMAL);
				}

			break;

		case CHOCADO:
			estado = JUEGO_PARADO;
			
			break;
		case MUERTO:
			estado = JUEGO_PARADO;				
		
			break;

	}



}

void dibujarjugador()
{

	SE_sprite_draw_fx(jug->spajaro,jug->posx,jug->posy,jug->posz,64,64,1,1,0,0,jug->rotacion,1,1,1,1);


}

void limpiarjugador()
{



}

void dibujarfondo()
{

	int i;
	SE_image_segment_draw_fx(imagenes,365,193,147,119,100,100,0,147,119,1,1,0,0,0,1,1,1,1);/*nube 1*/
	SE_image_segment_draw_fx(imagenes,365,193,147,119,400,200,0,147,119,1,1,0,0,0,1,1,1,1);/*nube 2*/

	if(estado != JUEGO_PARADO)
	{	
		xfondo--;
	}

	for(i=0;i<6;i++)
	{
		SE_image_segment_draw_fx(imagenes,383,350,128,161,xfondo + i*128,yfondo,0,128,161,1,1,0,0,0,1,1,1,1);/*edificio*/
	}

	if(xfondo < -128)xfondo = 0;

}

void dibujarlogo()
{

	SE_image_segment_draw_fx(imagenes,346,64,166,121,160,110,0,166,121,2,2,0,0,0,0,0.4,1,1);
	SE_font_draw(fuente,"2017 ARCADENEA",100,400,0);	

}

void draw_scene()
{
	
	switch(estado)
	{
		case JUEGO_INICIADO:

			jugadorestado(DETENIDO);

			if(intro_ciclos > 300)
			{

				intro_ciclos = 0;
				intro_estado++;
				if(intro_estado > 2)intro_estado = 0;

			}else{

				intro_ciclos++;

			}

			

			while( SDL_PollEvent( &event ) )
			{
				switch( event.type )
				{

					case SDL_KEYDOWN:
	
						switch( event.key.keysym.sym )
						{
							case SDLK_UP:

								estado = JUEGO_LISTO;
								jugadorestado(NORMAL);
								jug->ciclos = 0;
								intro_ciclos = 0;
								break;
										
							default:
								break;
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
            
					default:                
						break;			
				}
			}		

			break;
	
		case JUEGO_LISTO:
					


			while( SDL_PollEvent( &event ) )
			{
				switch( event.type )
				{

					case SDL_KEYDOWN:
	
						switch( event.key.keysym.sym )
						{
							case SDLK_UP:

								jugadorestado(SALTAR);
							
							default:
								break;
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
            
					default:                
						break;			
				}
			}
		
			if(controlarcolision()>0)
			{

				estado = JUEGO_PARADO;
					
			}
			
			
			break;
	
			
		case JUEGO_PARADO:

			SE_font_draw(fuente,"GAME OVER",200,220,0);	

			if(compararpuntos() == 1)
			{

				if(insertariniciales() == 1)
				{
					insertarrecord(jug->nombre,jug->puntuacion);
					estado = JUEGO_INICIADO;
				}	
				SE_font_draw(fuente,jug->nombre,200,200,0);
			}
			break;			
		
			
			
		default:
			
			break;
	
		
	}		



	moverjugador();
	movertubos();
	dibujarfondo();
	dibujartubos();
	dibujarjugador();


	if(estado == JUEGO_LISTO)
	{
		dibujarpuntuacion();
	}

	if((estado == JUEGO_INICIADO)&&(intro_estado == 0))
	{
		SE_image_segment_draw_fx(imagenes,400,0,112,59,250,180,0,166,121,1,1,0,0,0,1,1,1,1);
	}


	if((estado == JUEGO_INICIADO)&&(intro_estado == 1))
	{
		dibujarlogo();
	}

	if((estado == JUEGO_INICIADO)&&(intro_estado == 2))
	{
		SE_font_draw(fuente,"TOP 10",250,30,0);	
		dibujarhighscore(230,80,0,150,50);	
	}

}

int main(int argc,char* args[])
{

	Uint8 *keys;

	/*inicializamos la variable para salir*/
	quit = 0;
	
	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(SCREEN_WIDTH,SCREEN_HEIGHT,16);

/*void iniciartubos(float separacionx,float velocidadx,float espacioy,int numtubos,float w_tubo,float h_tubo)*/

	iniciarhiscore(10);
	iniciartubos(200,3,200,4,106,512);
	iniciarjugador(200,400,0,0.3);

	cargarimagenes();
	cargartubos();
	cargarjugador();
	cargarfuente();

	xfondo = 0;
	yfondo = 350;

	intro_estado = 0;
	intro_ciclos = 0;

	contpos = 0;

	estado = JUEGO_INICIADO;

	while(quit == 0)
	{
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0.7,0.7,1,1);
			
			/*dibujamos sprite con todos los parametros disponibles*/


			draw_scene();
					

			/*flipamos el cuadro*/
			SE_screen_flip();


			
			SDL_Delay(17);
	
	}

return 0;







}
