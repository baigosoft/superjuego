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
#define EXPLORAR 2
#define CONVERSAR 3
#define MINIJUEGO 4

/*estados de player*/
#define PARADO_ABAJO 0
#define CAMINAR_ABAJO 1
#define PARADO_ARRIBA 2
#define CAMINAR_ARRIBA 3
#define PARADO_IZQ 4
#define CAMINAR_IZQ 5
#define PARADO_DER 6
#define CAMINAR_DER 7
#define CONVERSAR 8

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

int npc = 0;

int controlar_colision();
void conversar();
int drawplayer();


void iniciarplayer(int personaje)
{

	player = (character*)malloc(sizeof(character));	
	player->posx = 0;
	player->posy = 0;
	player->posz = 0;
	player->velx = 2;
	player->vely = 2;
	player->personaje = personaje;
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




int inputplayer()
{

	switch(game_state)
	{

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

						player->posy += player->vely;
		
						if(mapa01->tile_collision > 1)
						{
							player->estado = CONVERSAR;
							npc = mapa01->tile_collision;
						}
			

					}


				}else if(state->buttons & JOY_DOWN){

					player->estado = CAMINAR_ABAJO;
					player->posy += player->vely;

					if(controlar_colision() > 0)
					{

						player->posy -= player->vely;	

						if(mapa01->tile_collision > 1)
						{
							player->estado = CONVERSAR;
							npc = mapa01->tile_collision;
						}		

					}					

				}else if(state->buttons & JOY_LEFT){
	
					player->estado = CAMINAR_IZQ;
					player->posx -= player->velx;

					if(controlar_colision() > 0)
					{

						player->posx += player->velx;

						if(mapa01->tile_collision > 1)
						{
							player->estado = CONVERSAR;
							npc = mapa01->tile_collision;
						}


					}					

				}else if(state->buttons & JOY_RIGHT){

					player->estado = CAMINAR_DER;
					player->posx += player->velx;

					if(controlar_colision() > 0)
					{

						player->posx -= player->velx;

						if(mapa01->tile_collision > 1)
						{
							player->estado = CONVERSAR;
							npc = mapa01->tile_collision;
						}

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

void conversar()
{


	if((game_state == EXPLORAR) && (mapa01->tile_collision > 1))
	{

		game_state = CONVERSAR;
		npc = mapa01->tile_collision;

	}


	if(game_state == CONVERSAR)
	{
	
		const char *mensaje;

		switch(npc)
		{

			case ESTELITA:

				mensaje = "ueps";			
	
				break;

			case MERCEDITA:

				mensaje = "hasta la victoria\nsiempre";			

				break;

			case RAMONITA:

				mensaje = "alo alo";			

				break;

			case SUSANITA:

				mensaje = "alca alcarajo";			

				break;

			case MONCHITO:

				mensaje = "B B B sos de la B";			

				break;

			case DIEGUITO:

				mensaje = "la pelota no se mancha";			

				break;
	
			case CARLITOS:

				mensaje = "hola que tal";			

				break;

			case INDIO_01:

				mensaje = "sobrio no te puedo ni\nhablar";			

				break;

			case INDIO_02:

				mensaje = "violencia es mentir";			
				break;

		}

		SE_font_draw(gamefont,mensaje,SCREEN_HEIGHT/4,SCREEN_HEIGHT/2,0);
	
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
	img_char01 = SE_image_load("character1.png");

	ani_char01 = SE_ani_init(PLAYER_W,PLAYER_H,13);

	SE_ani_create_from_img(ani_char01,img_char01,13,1,15);

	spr_char01 = SE_sprite_init(ani_char01);

	SE_sprite_box_init(spr_char01,1);

	SE_sprite_box_set(spr_char01,0,0,0,PLAYER_W,PLAYER_H);

	/*personaje 2*/

	img_char02 = SE_image_load("character2.png");

	ani_char02 = SE_ani_init(PLAYER_W,PLAYER_H,13);

	SE_ani_create_from_img(ani_char02,img_char02,13,1,15);

	spr_char02 = SE_sprite_init(ani_char02);

	SE_sprite_box_init(spr_char02,1);

	SE_sprite_box_set(spr_char02,0,0,0,PLAYER_W,PLAYER_H);

	/*tilemap*/

	tiles = SE_image_load("tiles.png");

	tileset01 = SE_tileset_init(30,TILE_W,TILE_W);
	
	SE_tileset_create_from_img(tileset01,tiles,6,5);

	mapa01 = SE_tilemap_init(tileset01,20,TILE_W,TILE_W,40,40);
	
	SE_tilemap_maptile_load(mapa01,"tilemap.txt");

	SE_tilemap_mapcoll_load(mapa01,"tilemap_coll.txt");

	area_tile = SE_box_init(0,0,27,17);

	/*fuente*/
	gamefont_img = SE_image_load("font512.png");
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

void drawscene()
{

		SE_tilemap_draw(mapa01,camara.x,camara.y,0);

		drawplayer();

		conversar();

		//SE_font_draw(gamefont,"mueran putos",SCREEN_HEIGHT/4,SCREEN_HEIGHT/2,0);



}

int main(int argc,char* args[])
{



	/*variable para salir*/
	quit = 0;

	/*inicializamos la pantalla con la resolucion y la cantidad de colores*/
	SE_screen_init(SCREEN_WIDTH,SCREEN_HEIGHT,BPP);

	/*llamamos a la funcion cargarcosas()*/
	cargarcosas();

	//SE_animator_initend_set(spr_char01->ator,1,2);

	iniciarplayer(PABLICIANO);

	/*inicializamos el sistema de Input*/
	SE_input_init();
	printf("hay %d joysticks disponibles\n",SE_input_enum());
	joystick = SE_input_open(0);

	game_state = EXPLORAR;
	
	while(quit == 0)
	{
		
			/*limpiamos la pantalla con un color*/
			SE_screen_clear(0,0,0,0);



			//SE_tilemap_draw(mapa01,0,0,0);



			//SE_image_draw(img_char01,0,0,0);





			//moveplayer();

			setcamara();

			inputplayer();

			//SE_tilemap_area_draw(mapa01,camara.x,camara.y,0,&area_tile);			


			
			drawscene();





			/*flipeamos todo el cuadro*/
			SE_screen_flip();
			
			

			
			
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
