#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "super.h"

/*atributos de pantalla*/
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define BPP 32

/*atributos de personaje*/
#define PLAYER_W 32
#define PLAYER_H 32

/*atributos de tilemap*/
#define TILE_W 32
#define TILEMAP_W 40
#define TILEMAP_H 40
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 1280

/*camara*/
#define IZQ 0
#define DER 1
#define ARR 2
#define ABA 3

/*estado del juego*/
#define DETENIDO 0
#define TITULO 1
#define SELECCION 2
#define EXPLORAR 3
#define CONVERSAR 4
#define MINIJUEGO 5
#define MINIJUEGO2 6

/*estados de player*/
#define PARADO_ABAJO 0
#define CAMINAR_ABAJO 1
#define PARADO_ARRIBA 2
#define CAMINAR_ARRIBA 3
#define PARADO_IZQ 4
#define CAMINAR_IZQ 5
#define PARADO_DER 6
#define CAMINAR_DER 7
//#define CONVERSAR 8

/*personajes*/
#define PABLICIANO 0
#define MARTITA 1

/*npc*/
#define ESTELITA 10
#define MERCEDITA 11
#define RAMONITA 12
#define SUSANITA 13
#define MONCHITO 14
#define DIEGUITO 15
#define CARLITOS 16
#define INDIO_01 17
#define INDIO_02 18



int quit;

Uint8 *keys;

//SDL_Event event;

SE_input_state *state;
SE_input_joystick *joystick;

int game_state = DETENIDO;/*estado del juego DETENIDO/INICIADO*/

/*fuente*/
SE_image *gamefont_img;
SE_font *gamefont;

/*imagen personaje 1*/
SE_image *img_char01;

/*animacion personaje 1*/
SE_ani *ani_char01;

/*sprite personaje 1*/
SE_sprite *spr_char01;

/*imagen personaje 2*/
SE_image *img_char02;

/*animacion personaje 2*/
SE_ani *ani_char02;

/*sprite personaje 1*/
SE_sprite *spr_char02;


/*creamos la imagen para los tiles*/
SE_image *tiles;

/*creamos estructura para tileset del mapa 1*/
SE_tileset *tileset01;

/*creamos estructura para tilemap 1*/
SE_tilemap *mapa01;

/*area que se dibuja de tilemap*/
SE_box area_tile;

/*estructura de camara*/
SE_box camara;

int estado_anterior = 0;

int camara_estado_x = IZQ;
int camara_estado_y = ARR;

int temp_pos = 0;

typedef struct
{

	int logro_id;/*id del logro*/
	const char *logro_descrip;/*descripcion del logro*/
	int conseguido;/*puede ser 0 = no, 1 = si*/

}logro;

logro *logros;

typedef struct
{

	float posx,posy,posz;
	int velx,vely;
	int personaje;/*PABLICIANO o MARTITA*/
	int puntaje;
	int vidas;
	int estado;
	logro lista_logros[20];

}character;

/*creamos personaje*/
character *player;

typedef struct
{

	int id;
	const char *nombre;
	const char *dialogo;
	int minijuego;

}struct_npc;

int npc = 0;

/*PANTALLA TITULO*/


/*PANTALLA SELECCION*/
int sel = 0;
SE_image *imgretrato01;
SE_image *imgretrato02;
SE_image *imgpuntero;

/*MINIJUEGO 1*/
int ciclos = 0;
int selopcion = 0;
int hecho = 0;
int x,y;
SE_image *imgminijuego01;
SE_image *imgminijuego02;
SE_image *imgflecha;
SE_image *imgokfail;

/*FUNCIONES*/
int controlar_colision();
void controlar_conversar();
void conversar();
int drawplayer();
void draw_seleccion();


void iniciarplayer()
{

	player = (character*)malloc(sizeof(character));	
	player->posx = 0;
	player->posy = 0;
	player->posz = 0;
	player->velx = 6;
	player->vely = 6;
	player->personaje = PABLICIANO;
	player->puntaje = 0;	
	player->vidas = 3;
	player->estado = PARADO_ABAJO;
	estado_anterior = PARADO_ABAJO;

	if(player->personaje == PABLICIANO)
	{
		SE_animator_initend_set(spr_char01->ator,0,0);/*animación de PARADO_ABAJO*/
	}else if(player->personaje == MARTITA){
		SE_animator_initend_set(spr_char02->ator,0,0);/*animación de PARADO_ABAJO*/
	}
	
	camara.x = 0;
	camara.y = 0;
}

void cleanplayer()
{

	free(player);

}

void cargar_logros()
{

	logros = (logro*)malloc(10*sizeof(logro));

	logros[0].logro_id = 0;
	logros[0].logro_descrip = "Empezaste la aventura";
	logros[0].conseguido = 0;






}

int controlar_logros()
{




}


int inputplayer()
{

	switch(game_state)
	{

		case TITULO:

			if(state=SE_input_poll(&joystick))
			{
        	
				if((state->buttons & JOY_UP)||(state->buttons & JOY_DOWN)||(state->buttons & JOY_LEFT)||(state->buttons & JOY_RIGHT))
				{
					
					game_state = SELECCION;
	
				}

				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}

			}

			break;


		case SELECCION:

			if(state=SE_input_poll(&joystick))
			{
        
				if(state->buttons & JOY_LEFT)  
				{

					sel = 0;

				}else if(state->buttons & JOY_RIGHT){

					sel = 1;

				}
	
				if(state->buttons & JOY_BUTTON0)
				{
					
					player->personaje = sel;
					game_state = EXPLORAR;
					
				}

				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}

			}

			break;

		case EXPLORAR:/*el jugador se mueve por el mapa*/

			estado_anterior = player->estado;

			if(state=SE_input_poll(&joystick))
			{
        
				if(state->buttons & JOY_UP)  
				{

					player->estado = CAMINAR_ARRIBA;
					player->posy -= player->vely;
						
					if(controlar_colision() > 0)
					{
						controlar_conversar();
					}

				}else if(state->buttons & JOY_DOWN){

					player->estado = CAMINAR_ABAJO;
					player->posy += player->vely;

					if(controlar_colision() > 0)
					{
						controlar_conversar();
					}					

				}else if(state->buttons & JOY_LEFT){
	
					player->estado = CAMINAR_IZQ;
					player->posx -= player->velx;

					if(controlar_colision() > 0)
					{
						controlar_conversar();
					}					

				}else if(state->buttons & JOY_RIGHT){

					player->estado = CAMINAR_DER;
					player->posx += player->velx;

					if(controlar_colision() > 0)
					{
						controlar_conversar();
					}					

				}else{

					player->estado = PARADO_ABAJO;	

				}		
		
				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}
				
			}

			if(player->posx < 0)player->posx = 0;
			if(player->posy < 0)player->posy = 0;
			if(player->posx > SCREEN_WIDTH - PLAYER_W)player->posx = SCREEN_WIDTH - PLAYER_W;
			if(player->posy > SCREEN_HEIGHT - PLAYER_H)player->posy = SCREEN_HEIGHT - PLAYER_H;

			break;

		case CONVERSAR:
		
			if(state=SE_input_poll(&joystick))
			{
			
				if(state->buttons & JOY_BUTTON0)
				{
					
					if(npc == INDIO_01)
					{	

						game_state = MINIJUEGO;
					
					}else if(npc == ESTELITA){

						game_state = MINIJUEGO2;

					}else{
					
						game_state = EXPLORAR;

					}
				}
	
				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}

			}
			break;

		case MINIJUEGO:

			if(state=SE_input_poll(&joystick))
			{
				
				if(hecho == 0)
				{	

					if(state->buttons & JOY_LEFT)
					{
	
						selopcion=0;
										
					}else if(state->buttons & JOY_RIGHT){

						selopcion=1;					
					}				
			
					if(ciclos > 10)					
					{	
						if(state->buttons & JOY_BUTTON0)
						{
				
							hecho = 1;
							ciclos=0;
						}
					}else{
						ciclos++;
					}
						
				}

				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}

			}

			break;

		case MINIJUEGO2:

			if(state=SE_input_poll(&joystick))
			{
				
				if(hecho == 0)
				{	

					if(ciclos > 10)											
					{

						if(state->buttons & JOY_UP)
						{
		
								selopcion--;
								ciclos = 0;
								//break;							
										
						}else if(state->buttons & JOY_DOWN){

							
								selopcion++;
								ciclos = 0;
								//break;
											
						}				
				
						if(selopcion < 0)selopcion=0;
						if(selopcion > 2)selopcion=2;						

						
						if(state->buttons & JOY_BUTTON0)
						{
						
							hecho = 1;
							ciclos=0;
							break;
		
						}

					}else{

						ciclos++;

					}
					
						
				}

				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}

			}

			break;


		default:
	
			if(state=SE_input_poll(&joystick))
			{
				if(state->buttons & SE_QUIT) 
				{
					quit=1;
				}
			}
			break;

	}

	

}


int controlar_colision()
{

	int colision = 0;	
	
	if(player->personaje == PABLICIANO)
	{
		colision = SE_tilemap_collision(mapa01,camara.x,camara.y,spr_char01->box,player->posx,player->posy);
	}else if(player->personaje == MARTITA){
		colision = SE_tilemap_collision(mapa01,camara.x,camara.y,spr_char02->box,player->posx,player->posy);
	}

	if(colision > 0)
	{
		switch(player->estado)
		{

			case CAMINAR_ARRIBA:
			
				player->posy += player->vely;

				break;

			case CAMINAR_ABAJO:
			
				player->posy -= player->vely;

				break;

			case CAMINAR_IZQ:

				player->posx += player->velx;
			
				break;

			case CAMINAR_DER:

				player->posx -= player->velx;
			
				break;

		}

	}
		
	return colision;

}


void controlar_conversar()
{

	if((game_state == EXPLORAR) && (mapa01->tile_collision > 1))
	{

		game_state = CONVERSAR;
		npc = mapa01->tile_collision;

	}

}

void conversar()
{


	if(game_state == CONVERSAR)
	{
	
		const char *mensaje;

		switch(npc)
		{

			case ESTELITA:

				mensaje = "ESTELITA\n   SERA QUE PODES CONTESTAR\n   BIEN ESTA PREGUNTA?";			
	
				break;

			case MERCEDITA:

				mensaje = "NO HAY PAN DURO";			

				break;

			case RAMONITA:

				mensaje = "PERO QUE CALOR\nQUE HACE ";			

				break;

			case SUSANITA:

				mensaje = "ESTA PLAZA\nNO TIENE JUEGOS";			

				break;

			case MONCHITO:

				mensaje = "LA MEJOR ROBOCOP\nFUE LA 1";			

				break;

			case DIEGUITO:

				mensaje = "CUAL PELICULA\nDE LORENZO LAMAS\nTE GUSTA?";			

				break;
	
			case CARLITOS:

				mensaje = "AASENASEHASHEASELASHLAKCLK";			

				break;

			case INDIO_01:

				mensaje = "INDIO PATI:\n   PREPARADO PARA JUGAR,\n   AMIGX?\n   TENES QUE FIJARTE\n   CUAL IMAGEN ES CORRECTA";			

				break;

			case INDIO_02:

				mensaje = "SOY EL INDIO\nPANCHERO";			
				break;

		}

		SE_font_draw_fx(gamefont,mensaje,5,SCREEN_HEIGHT/2,0,32,32,1,1,0,0,0,1,1,1,1); 
	
	}


}




int drawplayer()
{

	if(estado_anterior != player->estado)
	{

		switch(player->estado)
		{	
		
			case PARADO_ABAJO:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,0,0);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,0,0);		
				}
				break;
	
			case CAMINAR_ABAJO:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,1,2);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,1,2);		
				}
				break;
		
			case PARADO_ARRIBA:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,3,3);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,3,3);		
				}
				break;

			case CAMINAR_ARRIBA:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,4,5);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,4,5);		
				}
				break;

			case PARADO_IZQ:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,6,6);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,6,6);		
				}
				break;

			case CAMINAR_IZQ:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,7,8);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,7,8);		
				}
				break;			

			case PARADO_DER:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,9,9);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,9,9);		
				}
				break;

			case CAMINAR_DER:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,10,11);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,10,11);		
				}
				break;		

			default:
				if(player->personaje == PABLICIANO)	
				{	
					SE_animator_initend_set(spr_char01->ator,0,0);
				}else if(player->personaje == MARTITA){
					SE_animator_initend_set(spr_char02->ator,0,0);		
				}
				break;

		}

	}

	if(player->personaje == PABLICIANO)	
	{	
		SE_sprite_draw(spr_char01,player->posx,player->posy,player->posz);
	}else if(player->personaje == MARTITA){
		SE_sprite_draw(spr_char02,player->posx,player->posy,player->posz);
	}




}

void cargarcosas()
{

	/*personaje 1*/
	img_char01 = SE_image_load("datos/character1.png");

	ani_char01 = SE_ani_init(PLAYER_W,PLAYER_H,13);

	SE_ani_create_from_img(ani_char01,img_char01,13,1,6);

	spr_char01 = SE_sprite_init(ani_char01);

	SE_sprite_box_init(spr_char01,1);

	SE_sprite_box_set(spr_char01,0,0,0,PLAYER_W,PLAYER_H);

	/*personaje 2*/

	img_char02 = SE_image_load("datos/character2.png");

	ani_char02 = SE_ani_init(PLAYER_W,PLAYER_H,13);

	SE_ani_create_from_img(ani_char02,img_char02,13,1,5);

	spr_char02 = SE_sprite_init(ani_char02);

	SE_sprite_box_init(spr_char02,1);

	SE_sprite_box_set(spr_char02,0,0,0,PLAYER_W,PLAYER_H);

	/*tilemap*/

	tiles = SE_image_load("datos/tiles.png");

	tileset01 = SE_tileset_init(30,TILE_W,TILE_W);
	
	SE_tileset_create_from_img(tileset01,tiles,6,5);

	mapa01 = SE_tilemap_init(tileset01,20,TILE_W,TILE_W,40,40);
	
	SE_tilemap_maptile_load(mapa01,"datos/tilemap.txt");

	SE_tilemap_mapcoll_load(mapa01,"datos/tilemap_coll.txt");

	area_tile = SE_box_init(0,0,27,17);

	/*imagenes seleccion*/
	imgretrato01 = SE_image_load("datos/retrato01.png");
	imgretrato02 = SE_image_load("datos/retrato02.png");
	imgpuntero = SE_image_load("datos/fondosel.png");


	/*imagenes minijuego*/
	imgminijuego01 = SE_image_load("datos/minijuego01-01.png");
	imgminijuego02 = SE_image_load("datos/minijuego01-02.png");
	imgflecha = SE_image_load("datos/flecha.png");
	imgokfail = SE_image_load("datos/okfail.png");


	/*fuente*/
	gamefont_img = SE_image_load("datos/font512.png");
	gamefont = SE_font_create(gamefont_img,16,16,32,32);
	SE_font_space_set(gamefont,20);
	SE_font_letterspacing_set(gamefont,0);

	


	/*camara*/

	camara.w = SCREEN_WIDTH;
	camara.h = SCREEN_HEIGHT;

}

void setcamara()
{

	
	if((player->posx > SCREEN_WIDTH/2) && (camara.x > (SCREEN_WIDTH - LEVEL_WIDTH))) 	
	{
		camara.x -= player->velx;
		player->posx -= player->velx;
		//player->posx = SCREEN_WIDTH/2;	
	}

	if((player->posx < SCREEN_WIDTH/2) && (camara.x < 0))	
	{
		camara.x += player->velx;
		player->posx += player->velx;
		//player->posx = SCREEN_WIDTH/2;

	}

	if((player->posy > SCREEN_HEIGHT/2) && (camara.y > (SCREEN_HEIGHT - LEVEL_HEIGHT))) 	
	{
		camara.y -= player->vely;
		player->posy -= player->vely;
		//player->posy = SCREEN_HEIGHT/2;
	}

	if((player->posy < SCREEN_HEIGHT/2) && (camara.y < 0))	
	{
		camara.y += player->vely;
		player->posy += player->vely;
		//player->posy = SCREEN_HEIGHT/2;
	}

	if(camara.x > 0)
	{
		camara.x = 0;
	}

	if(camara.x < (SCREEN_WIDTH - LEVEL_WIDTH))
	{
		camara.x = SCREEN_WIDTH - LEVEL_WIDTH;
	}

	if(camara.y > 0)
	{
		camara.y = 0;
	}

	if(camara.y < (SCREEN_HEIGHT - LEVEL_HEIGHT))
	{
		camara.y = SCREEN_HEIGHT - LEVEL_HEIGHT;
	}

}


void draw_titulo()
{

	SE_screen_clear(0,0,1,0);

	SE_image_segment_draw_fx(tiles,0,201,256,55,10,140,0,256,55,3,3,0,0,0,1,1,1,1);

	SE_font_draw(gamefont,"PRESIONA BOTON, PUE",120,380,0);




}

void draw_seleccion()
{

	SE_screen_clear(1,0,0,0);

	if(sel == 0)
	{
			SE_image_draw(imgpuntero,94,110,0);		
	}else{
			SE_image_draw(imgpuntero,450,110,0);		
	}

	SE_image_draw(imgretrato01,94,110,0);

	SE_image_draw(imgretrato02,450,110,0);

	SE_font_draw(gamefont,"SELECCIONA PERSONAJE, CHE!",20,30,0);

	SE_font_draw(gamefont,"PABLICIANO",75,390,0);

	SE_font_draw(gamefont,"MARTITA",470,390,0);												




}

void minijuego01()
{

		SE_screen_clear(1,0.7,0.7,0);

		SE_font_space_set(gamefont,20);

		SE_font_letterspacing_set(gamefont,0);

		SE_font_draw(gamefont,"CUAL ES LA IMAGEN REAL,\nCHE?",40,10,0);

		SE_image_draw(imgminijuego01,130,80,0);

		SE_image_draw(imgminijuego02,430,80,0);

	if(player->personaje == PABLICIANO)
	{

		if(selopcion == 0)
		{

			//SE_image_draw(imgflecha,220,350,0);
			SE_image_segment_draw_fx(img_char01,0,0,32,32,220,350,0,256,256,3,3,0,0,0,1,1,1,1);		

		}else{

			//SE_image_draw(imgflecha,520,350,0);
			SE_image_segment_draw_fx(img_char01,0,0,32,32,520,350,0,256,256,3,3,0,0,0,1,1,1,1);				

		}

	}else if(player->personaje == MARTITA){

		if(selopcion == 0)
		{

			//SE_image_draw(imgflecha,220,350,0);
			SE_image_segment_draw_fx(img_char02,0,0,32,32,220,350,0,256,256,3,3,0,0,0,1,1,1,1);		

		}else{

			//SE_image_draw(imgflecha,520,350,0);
			SE_image_segment_draw_fx(img_char02,0,0,32,32,520,350,0,256,256,3,3,0,0,0,1,1,1,1);				

		}

	}


		if(hecho == 1)
		{

			if(selopcion == 0)			
			{



				SE_image_segment_draw_fx(imgokfail,0,0,256,256,130,80,0,256,256,1,1,0,0,0,1,1,1,1);

					if(ciclos > 100)					
					{	
						ciclos = 0;
						game_state = EXPLORAR;
						selopcion = 0;
						hecho = 0;
						SE_font_space_set(gamefont,20);
						SE_font_letterspacing_set(gamefont,0);
						return;

					}else{
						
						SE_font_space_set(gamefont,40);
						SE_font_letterspacing_set(gamefont,15);
						SE_font_draw_fx(gamefont,"GANASTE FANTASMA",20,200,0,32,32,3,3,0,0,0,0,1,0,1);
						ciclos++; 
					 
					}
									


				

			}else{
				
				SE_image_segment_draw_fx(imgokfail,256,0,256,256,430,80,0,256,256,1,1,0,0,0,1,1,1,1);

					if(ciclos > 100)					
					{	
						ciclos = 0;
						game_state = EXPLORAR;
						selopcion = 0;	
						hecho = 0;
						SE_font_space_set(gamefont,20);
						SE_font_letterspacing_set(gamefont,0);
						return;

					}else{
						SE_font_space_set(gamefont,40);
						SE_font_letterspacing_set(gamefont,15);
						SE_font_draw_fx(gamefont,"PERDISTE SALAME",20,200,0,32,32,3,3,0,0,0,1,0,0,1); 
						ciclos++;
					}



				
				
			}
		
			
		


		}
		

}

void minijuego02()
{

	SE_screen_clear(0.7,0.7,1,0);

	SE_font_space_set(gamefont,20);

	SE_font_letterspacing_set(gamefont,0);

	SE_font_draw(gamefont,"CUANDO RESISTENCIA\nFUE DECLARADA CAPITAL\nNACIONAL DE LAS\nESCULTURAS?",20,10,0);

	SE_font_draw(gamefont,"1988",200,300,0);

	SE_font_draw(gamefont,"2006",200,350,0);

	SE_font_draw(gamefont,"1994",200,400,0);

	if(player->personaje == PABLICIANO)
	{

		if(selopcion == 0)
		{

			SE_image_segment_draw_fx(img_char01,0,0,32,32,120,300,0,256,256,1,1,0,0,0,1,1,1,1);		

		}else if(selopcion == 1){

			SE_image_segment_draw_fx(img_char01,0,0,32,32,120,350,0,256,256,1,1,0,0,0,1,1,1,1);				

		}else if(selopcion == 2){

			SE_image_segment_draw_fx(img_char01,0,0,32,32,120,400,0,256,256,1,1,0,0,0,1,1,1,1);				

		}

	}else if(player->personaje == MARTITA){

		if(selopcion == 0)
		{

			SE_image_segment_draw_fx(img_char02,0,0,32,32,120,300,0,256,256,1,1,0,0,0,1,1,1,1);		

		}else if(selopcion == 1){

			SE_image_segment_draw_fx(img_char02,0,0,32,32,120,350,0,256,256,1,1,0,0,0,1,1,1,1);				

		}else if(selopcion == 2){

			SE_image_segment_draw_fx(img_char02,0,0,32,32,120,400,0,256,256,1,1,0,0,0,1,1,1,1);					

		} 

	}
 	 	 	 	
	
		if(hecho == 1)
		{

			if(selopcion == 1)			
			{



				SE_image_segment_draw_fx(imgokfail,0,0,256,256,130,80,0,256,256,1,1,0,0,0,1,1,1,1);

					if(ciclos > 100)					
					{	
						ciclos = 0;
						game_state = EXPLORAR;
						selopcion = 0;
						hecho = 0;
						SE_font_space_set(gamefont,20);
						SE_font_letterspacing_set(gamefont,0);
						return;

					}else{
						
						SE_font_space_set(gamefont,40);
						SE_font_letterspacing_set(gamefont,15);
						SE_font_draw_fx(gamefont,"GANASTE FANTASMA",20,200,0,32,32,3,3,0,0,0,0,1,0,1);
						ciclos++; 
					 
					}
									


				

			}else{
				
				SE_image_segment_draw_fx(imgokfail,256,0,256,256,430,80,0,256,256,1,1,0,0,0,1,1,1,1);

					if(ciclos > 100)					
					{	
						ciclos = 0;
						game_state = EXPLORAR;
						selopcion = 0;	
						hecho = 0;
						SE_font_space_set(gamefont,20);
						SE_font_letterspacing_set(gamefont,0);
						return;

					}else{
						SE_font_space_set(gamefont,40);
						SE_font_letterspacing_set(gamefont,15);
						SE_font_draw_fx(gamefont,"PERDISTE SALAME",20,200,0,32,32,3,3,0,0,0,1,0,0,1); 
						ciclos++;
					}



				
				
			}

		}


}


void drawscene()
{

	switch(game_state)
	{
		
		case TITULO:
	
			draw_titulo();

			break;	

		case SELECCION:
		
			draw_seleccion();			
	
			break;

		case EXPLORAR:		

			SE_tilemap_draw(mapa01,camara.x,camara.y,0);

			drawplayer();

			break;

		case CONVERSAR:

			SE_tilemap_draw(mapa01,camara.x,camara.y,0);

			drawplayer();
			
			conversar();

			break;

		case MINIJUEGO:
	
			minijuego01();

			break;

		case MINIJUEGO2:
	
			minijuego02();

			break;

		default:
			break;

	}

}




int main(int argc,char* args[])
{



	/*variable para salir*/
	quit = 0;

	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(SCREEN_WIDTH,SCREEN_HEIGHT,BPP);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();

	cargar_logros();

	//SE_animator_initend_set(spr_char01->ator,1,2);

	iniciarplayer();

	/*seteamos el framerate a 60 cuadros*/
	SE_timer_setframerate(30);

	/*inicializamos el sistema de Input*/
	SE_input_init();
	printf("hay %d joysticks disponibles\n",SE_input_enum());
	joystick = SE_input_open(0);

	//printf("%s",logros[0].logro_descrip);

	game_state = TITULO;
	
	while(quit == 0)
	{
		
			/*limpiamos la pantalla con un color*/
			//SE_screen_clear(0,0,0,0);



			//SE_tilemap_draw(mapa01,0,0,0);



			//SE_image_draw(img_char01,0,0,0);





			//moveplayer();

			setcamara();

			inputplayer();

			//SE_tilemap_area_draw(mapa01,camara.x,camara.y,0,&area_tile);			


			
			drawscene();


			//draw_seleccion();


			/*flipeamos todo el cuadro*/
			SE_screen_flip();
			
			

			/*controlamos el framerate con esta funcion*/
			SE_timer_waitframerate();
			
			
			/*while( SDL_PollEvent( &event ) )
	        {
			
				if( event.type == SDL_QUIT )
				{

					quit = 1;
					cleanplayer();

				}
			

			}*/
			
		
	}
	
	cleanplayer();


	return 0;


}
