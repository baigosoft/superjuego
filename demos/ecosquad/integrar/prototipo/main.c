#include <stdio.h>
#include <stdlib.h>
#include "super.h"
#include "char.h"
#include "enemy.h"
#include "title.h"
#include "menu.h"
#include "zone.h"



SDL_Event event;
Uint8 *keys;

/*contador del despachador pantallas o como se llame*/
int cont_screen;
int tick_screen;/*para que tenga un retardo al presionar el boton*/

int posx,posy,movy;
float alpha=1.0f;
float zoom=1.0f;
float zoominc=0.0f;
float alphainc=0.0f;
int jump=0;

int tiempo=0;
//float posinicial;

char_t *personaje;

/*creamos la estructura para almacenar la imagen*/
SE_image *back;
SE_image *tile00;
SE_image *tile01;
SE_image *tile02;


SE_tilemap *timap;

/*imagen minita*/
SE_image *minita;

/*animacion de la minita*/
SE_ani *m_stand;
SE_ani *m_run;
SE_ani *m_shoot;
SE_ani *m_jump;

/*sprite de la minita*/
SE_sprite *ms_stand;/*stand*/
SE_sprite *ms_run;/*run*/
SE_sprite *ms_shoot;/*shoot*/
SE_sprite *ms_jump;/*jump*/

/*personaje minita*/
SE_character *ch_minita;	

SE_image *disp01_01;
SE_image *disp01_02;
SE_image *disp01_03;

SE_ani *adisp01;


SE_sprite *sdisp01;

/*cara de jessica*/
SE_image *face_jess; 

/*disparo personaje rafaga*/
SE_image *disp02_01;
SE_image *disp02_02;

SE_ani *adisp02;

SE_sprite *sdisp02;

struct disparo 
{
	int x,y;
	int activa;/*bala activa o no*/
	int sentido;/*sentido de la bala 0 izquierda 1 derecha*/
}bala[8];

int tickdisparo=0;/*contador para que las balas salgan espaciadas*/


/*enemigo*/
SE_sprite *spr_enemy[6];
SE_ani *ani_enemy;
SE_image *im_enemy;
SE_image *im_enemy2;
enemy_t *enemigo[6];

/*vidas del personaje*/
SE_image *life;
int cont_life;

/*you win*/
SE_image *youwin;
void muevepersonaje();
int check_collisions(int posx, int posy);


void cargardisparoplayer()
{

	/*cargamos imagen disparo succion*/
	disp01_01 = SE_image_load("disp01_01.png");
	disp01_02 = SE_image_load("disp01_02.png");
	disp01_03 = SE_image_load("disp01_03.png");

	/*cargamos animacion disparo succion*/
	adisp01 = SE_ani_init();
	SE_ani_addframe(adisp01,disp01_01,10);
	SE_ani_addframe(adisp01,disp01_02,10);	
	SE_ani_addframe(adisp01,disp01_03,10);		

	/*cargamos sprite disparo succion*/
	sdisp01 = SE_sprite_init(adisp01);
	SE_sprite_addbox(sdisp01,0,0,64,64);

	/*cargamos imagen disparo rafaga*/
	disp02_01 = SE_image_load("disp02_01.png");
	disp02_02 = SE_image_load("disp02_02.png");


	/*cargamos animacion disparo rafaga*/
	adisp02 = SE_ani_init();
	SE_ani_addframe(adisp02,disp02_01,10);
	SE_ani_addframe(adisp02,disp02_02,10);	

	/*cargamos sprite disparo rafaga*/
	sdisp02 = SE_sprite_init(adisp02);
	SE_sprite_addbox(sdisp02,0,0,16,16);

}

void inicializarbalas()
{
	int i;
	for(i=0;i < 8;i++)
	{
		bala[i].x = 0;
		bala[i].y = 0;
		bala[i].activa = 0;
		bala[i].sentido = 0;

	}
	
}

void moverbalas()/*mueve las balas por la pantalla*/
{

	int i;	
	
		for(i=0;i < 8;i++)
		{
			if(bala[i].activa != 0)
			{
				if(bala[i].sentido == 0)
				{	
					bala[i].x -= 5;
				}else{
					bala[i].x += 5;
				}
				SE_sprite_draw(sdisp02,bala[i].x,bala[i].y,0);
			
			}
			if((bala[i].x > 640) || (bala[i].x < 0))
			{

				bala[i].activa = 0;
		
			}
	
		}
}


void cargarsprites()
{
	personaje=create_character();

	/*cargamos cara y vida*/
	face_jess = SE_image_load("face_jess.png");
	life = SE_image_load("life.png");

	/*cargar you win*/
	youwin = SE_image_load("youwin.png");

	/*cargamos la imagen en la estructura definida*/
	back = SE_image_load("fondo.png");
	tile00 = SE_image_load("tile00.png");
	tile01 = SE_image_load("tile01.png");
	tile02 = SE_image_load("tile02.png");


	/*iniciamos tilemap*/
	timap = SE_tilemap_init(32,32,20,15);

	/*agregamos imagenes al tilemap*/
	SE_tilemap_addimage(timap,tile00);
	SE_tilemap_addimage(timap,tile01);
	SE_tilemap_addimage(timap,tile02);


	/*cargamos mapa*/
	SE_tilemap_loadmapimage(timap,"mapimage.txt");
	SE_tilemap_loadmapcoll(timap,"mapcollision.txt");

	/*cargamos imagenes minita*/
	minita = SE_image_load("minita.png");

	/*animacion de la  minita*/
	m_stand = SE_ani_init();
	SE_ani_addframe_segment(m_stand,minita,10,0,0,128,128);
	SE_ani_addframe_segment(m_stand,minita,10,128,0,128,128);

	m_run = SE_ani_init();
	SE_ani_addframe_segment(m_run,minita,10,0,0,128,128);
	SE_ani_addframe_segment(m_run,minita,10,0,128,128,128);

	m_shoot = SE_ani_init();
	SE_ani_addframe_segment(m_shoot,minita,30,0,0,128,128);
	SE_ani_addframe_segment(m_shoot,minita,30,128,128,128,128);

	m_jump = SE_ani_init();
	SE_ani_addframe_segment(m_jump,minita,30,0,128,128,128);

	/*iniciar sprites minita*/
	ms_stand = SE_sprite_init(m_stand);/*animacion parado*/
	SE_sprite_addbox(ms_stand,38,18,58,110);

	ms_run = SE_sprite_init(m_run);/*animacion correr*/
	SE_sprite_addbox(ms_run,38,18,58,110);

	ms_shoot = SE_sprite_init(m_shoot);/*animacion disparo*/
	SE_sprite_addbox(ms_shoot,38,18,58,110);

	ms_jump = SE_sprite_init(m_jump);/*animacion salto*/
	SE_sprite_addbox(ms_jump,38,18,58,110);

	/*iniciar personaje*/
	//ch_minita = SE_character_init();
	personaje->character = SE_character_init();

	SE_character_addsprite(personaje->character,ms_stand);
	SE_character_addsprite(personaje->character,ms_run);
	SE_character_addsprite(personaje->character,ms_shoot);
	SE_character_addsprite(personaje->character,ms_jump);

//	SE_character_currentsprite(ch_minita,0); 

	SE_character_currentsprite(personaje->character,0); 
	personaje->character->spr[0]->box->x+=3;


}

void cargarenemigos()
{


	im_enemy = SE_image_load("carpincho01.png");
	im_enemy2 = SE_image_load("carpincho02.png");
	ani_enemy = SE_ani_init();
	SE_ani_addframe_segment(ani_enemy,im_enemy,10,0,0,64,64);
	SE_ani_addframe_segment(ani_enemy,im_enemy2,10,0,0,64,64);

//	enemigo=(enemy_t **)malloc(sizeof(enemy_t *)*6);

	for(int i=0;i<6;i++){
//		printf("%d\n",i);
		spr_enemy[i] = SE_sprite_init(ani_enemy);
		SE_sprite_addbox(spr_enemy[i],0,0,64,64);
		enemigo[i]=create_enemy();
		enemigo[i]->character = SE_character_init();
		SE_character_addsprite(enemigo[i]->character,spr_enemy[i]);
		SE_character_currentsprite(enemigo[i]->character,0); 

	} 
 

	enemigo[0]->posx=50;
	enemigo[0]->posy=0;
	enemigo[0]->character->spr[0]->box->x=50;

	enemigo[1]->posx=50;
	enemigo[1]->posy=200;
	enemigo[1]->character->spr[0]->box->x=50;
	enemigo[1]->character->spr[0]->box->y=200;

	enemigo[2]->posx=50;
	enemigo[2]->posy=350;
	enemigo[2]->character->spr[0]->box->x=50;
	enemigo[2]->character->spr[0]->box->y=350;

	enemigo[3]->posx=500;
	enemigo[3]->posy=0;
	enemigo[3]->character->spr[0]->box->x=500;

	enemigo[4]->posx=500;
	enemigo[4]->posy=200;
	enemigo[4]->character->spr[0]->box->x=500;
	enemigo[4]->character->spr[0]->box->y=200;

	enemigo[5]->posx=500;
	enemigo[5]->posy=350;
	enemigo[5]->character->spr[0]->box->x=500;
	enemigo[5]->character->spr[0]->box->y=350;
//	enemigo->posy=100;

//	enemigo->character->spr[0]->box->y=100;


}



void muevepersonaje()
{
float incremento;
int rotate=0;


		keys=SDL_GetKeyState(NULL);		
		if(keys[SDLK_RIGHT])
		{  /* Handle Joystick Motion */
			rotate=1;
			SE_character_currentsprite(personaje->character,1);

		}else if(keys[SDLK_LEFT]){  /* Handle Joystick Motion */
			rotate=-1;
			SE_character_currentsprite(personaje->character,1);

		}

		if(keys[SDLK_UP]){  /* Handle Joystick Motion */
			jump=1;
			SE_character_currentsprite(personaje->character,3);
		}else if(keys[SDLK_DOWN]){ /* Handle Joystick Motion */

		}

		if(keys[SDLK_x])
		{
			
			if(personaje->lookingright==1)
			{			
				SE_sprite_draw(sdisp01,personaje->posx + 100,personaje->posy + 50,0);
			}else{
				SE_sprite_draw_effects(sdisp01,personaje->posx - 35,personaje->posy + 50,0,1,1,0,180,0,1,1,1,1);
			}
		}

		int i;

		if(keys[SDLK_z])
		{
			tickdisparo++;	
			if(tickdisparo == 10)
			{
				for(i=0;i < 8;i++)
				{
					if(bala[i].activa == 0)
					{
						bala[i].activa = 1;
						if(personaje->lookingright == 0)
						{	
							bala[i].sentido = 0;				
							bala[i].x = personaje->posx;
							bala[i].y = personaje->posy + 75;
							break;

						}else{
							bala[i].sentido = 1;
							bala[i].x = personaje->posx + 100;
							bala[i].y = personaje->posy + 75;
							break;

						}	
					}
	
				}
				tickdisparo = 0;	
			}
			
		}
		

		if(keys[SDLK_f]){

			SE_screen_fullscreen(1);

		}

	if(move_character(personaje,timap, jump, rotate)==0)jump=0;

	SE_character_draw_effects(personaje->character,personaje->posx,personaje->posy,0,1,1,0,personaje->rot,0,1,1,1,1);
	SE_drawrectangle(personaje->character->spr[0]->box->x,personaje->character->spr[0]->box->y,0,personaje->character->spr[0]->box->w,personaje->character->spr[0]->box->h,0,1,0,0,1);


	for(int i=0;i<6;i++){
		SE_character_draw_effects(enemigo[i]->character,enemigo[i]->posx,enemigo[i]->posy,0,1,1,0,enemigo[i]->rot,0,1,1,1,1);
		SE_drawrectangle(enemigo[i]->character->spr[0]->box->x,enemigo[i]->character->spr[0]->box->y,0,enemigo[i]->character->spr[0]->box->w,enemigo[i]->character->spr[0]->box->h,0,0.5,0.5,0,1);

	}

}



int main(int argc,char* args[])
{

	int quit = 0;

	cont_screen = 0;

	tick_screen = 0;

	//SE_initgraphics();
	SE_screen_init(640,480,16);
	SE_timer_setframerate(60);
	/*cargarsprites();
	cargarenemigos();
	cargardisparoplayer();
	inicializarbalas();*/

	/*inicializar title*/
	init_var_title();
	load_images_title();

	while(quit == 0)
	{

		switch(cont_screen)
		{
			case 0:
				screentitle();
				keys=SDL_GetKeyState(NULL);
	
		
				if(keys[SDLK_z])
				{
									
					exittitle = 1;
									
				}
				if(exittitle == 1)
				{
					if(tick_screen == 100)
					{					
						cont_screen = 1;
						init_var_menu();
						load_images_menu();
						tick_screen = 0;
					}
					tick_screen++;
				}	
				break;

			case 1:
				screenmenu();
				if(exitmenu == 1)
				{
					if(tick_screen == 100)						
					{
						cont_screen = 2;
						tick_screen = 0;
						init_var_zone();
						load_images_zone();
						
					}
					tick_screen++;
				}
			
							
				break;	
			case 2:
					
					screenzone();
					if(exitzone == 1)
					{
						if(tick_screen == 100)
						{					
							cont_screen = 3;
							tick_screen = 0;		
							cargarsprites();
							cargarenemigos();
							cargardisparoplayer();
							inicializarbalas();

						}
						tick_screen++;	
					}	
				break;
			case 3:			
				SE_screen_clear(0,0,0,0);
				
				SE_image_draw(back,0,0,0);
				SE_tilemap_draw(timap,0,0,0);
				SE_tilemap_drawbox(timap,0,0);
				muevepersonaje();
				moverbalas();

				for(int i=0;i<1;i++){
					update_enemy_position(enemigo[i],timap);
				}
			
				SE_image_full_draw(face_jess,10,410,0,1,1,0,0,0,1,1,1,0.9);
				SE_image_full_draw(life,80,410,0,1,1,0,0,0,1,1,1,0.7);
				SE_image_draw(youwin,0,0,0);
				break;
		}
			
			/*trocito de codigo de SDL que usamos para detectar si se cierra la ventana*/	
			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{

					SE_character_clean(personaje->character);
					quit = 1;
				}
			

			}

		/*flipeamos todo el cuadro*/
		SE_screen_flip();
		SE_timer_waitframerate();
			
	
	}

	return 0;


}
