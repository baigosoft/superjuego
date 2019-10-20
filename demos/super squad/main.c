#include <stdio.h>
#include <stdlib.h>
#include "super.h"
#include "char.h"
#include "enemy.h"
#include "title.h"
#include "menu.h"
#include "zone.h"

#define MAX_ENEMIES 6


#ifdef DREAMCAST

#else
SDL_Event event;
Uint8 *keys;

#endif
//int posx,posy,movy;
float alpha=1.0f;
float zoom=1.0f;
float zoominc=0.0f;
float alphainc=0.0f;
int jump=0;
int cont_screen = 0;
int tick_screen = 0;

int debug_boxes=0;

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
SE_character *ch_minita;	//ch_minita = SE_character_init();

SE_image *disp01_01;
SE_image *disp01_02;
SE_image *disp01_03;

SE_ani *adisp01;


SE_sprite *sdisp01;

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
	SE_box box;
}bala[8];

int tickdisparo=0;/*contador para que las balas salgan espaciadas*/
int tickaspiradora=0;

/*enemigo*/
SE_sprite *spr_enemy[MAX_ENEMIES];
SE_ani *ani_enemy;
SE_image *im_enemy;
SE_image *im_enemy2;
enemy_t *enemigo[MAX_ENEMIES];

/*vidas del personaje*/
SE_image *life;
int cont_life;

/*you winlose*/
SE_image *youwin;
SE_image *youlose;

/*cara de jessica*/
SE_image *face_jess; 

/*sonidos*/
SE_sound *sfx_death;
SE_sound *sfx_shoot;
SE_sound *sfx_suck;
SE_sound *sfx_hit;
SE_sound *sfx_win;

SE_input_joystick *joystick;
SE_input_state *state;

void muevepersonaje();
int check_collisions();


#ifdef DREAMCAST
extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);
#endif

void cargardisparoplayer()
{

	/*cargamos imagen disparo succion*/
	disp01_01 = SE_image_load("assets/images/disp01_01.png");
	disp01_02 = SE_image_load("assets/images/disp01_02.png");
	disp01_03 = SE_image_load("assets/images/disp01_03.png");

	/*cargamos animacion disparo succion*/
	adisp01 = SE_ani_init();
	SE_ani_addframe(adisp01,disp01_01,10);
	SE_ani_addframe(adisp01,disp01_02,10);	
	SE_ani_addframe(adisp01,disp01_03,10);		

	/*cargamos sprite disparo succion*/
	sdisp01 = SE_sprite_init(adisp01);
	SE_sprite_addbox(sdisp01,0,0,64,64);

	/*cargamos imagen disparo rafaga*/
	disp02_01 = SE_image_load("assets/images/disp02_01.png");
	disp02_02 = SE_image_load("assets/images/disp02_02.png");


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
//		bala[i].box = (SE_box)malloc(sizeof(SE_box));
		bala[i].box.relx = 0;
		bala[i].box.rely = 0;
		bala[i].box.x = 0;
		bala[i].box.y = 0;
		bala[i].box.w = 16;
		bala[i].box.h = 16;

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
					bala[i].x -= 10;
					bala[i].box.x -= 10;
				}else{
					bala[i].x += 10;
					bala[i].box.x += 10;
				}
				SE_sprite_draw(sdisp02,bala[i].x,bala[i].y,0);
				if(debug_boxes)SE_drawrectangle(bala[i].box.x,bala[i].box.y,0,bala[i].box.w,bala[i].box.h,0,1,0,0,1);
			
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
	face_jess = SE_image_load("assets/images/face_jess.png");
	life = SE_image_load("assets/images/life.png");

	/*cargar you winlose*/
	youwin = SE_image_load("assets/images/youwin.png");
	youlose = SE_image_load("assets/images/youlose.png");

	/*cargamos la imagen en la estructura definida*/
	back = SE_image_load("assets/images/fondo.png");
	tile00 = SE_image_load("assets/images/tile00.png");
	tile01 = SE_image_load("assets/images/tile01.png");
	tile02 = SE_image_load("assets/images/tile02.png");

	SE_image_size(back,640,480);
	SE_image_size(youwin,640,480);
	SE_image_size(youlose,640,480);


	/*iniciamos tilemap*/
	timap = SE_tilemap_init(32,32,20,15);

	/*agregamos imagenes al tilemap*/
	SE_tilemap_addimage(timap,tile00);
	SE_tilemap_addimage(timap,tile01);
	SE_tilemap_addimage(timap,tile02);


	/*cargamos mapa*/
	SE_tilemap_loadmapimage(timap,"assets/tilemaps/mapimage.txt");
	SE_tilemap_loadmapcoll(timap,"assets/tilemaps/mapcollision.txt");

	/*cargamos imagenes minita*/
	minita = SE_image_load("assets/images/minita.png");

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
	SE_sprite_addbox(ms_stand,0,0,58,110);

	ms_run = SE_sprite_init(m_run);/*animacion correr*/
	SE_sprite_addbox(ms_run,0,0,58,110);

	ms_shoot = SE_sprite_init(m_shoot);/*animacion disparo*/
	SE_sprite_addbox(ms_shoot,0,0,58,110);

	ms_jump = SE_sprite_init(m_jump);/*animacion salto*/
	SE_sprite_addbox(ms_jump,0,0,58,110);

	/*iniciar personaje*/
	//ch_minita = SE_character_init();
	personaje->character = SE_character_init();

	SE_character_addsprite(personaje->character,ms_stand);
	SE_character_addsprite(personaje->character,ms_run);
	SE_character_addsprite(personaje->character,ms_shoot);
	SE_character_addsprite(personaje->character,ms_jump);

//	SE_character_currentsprite(ch_minita,0); 

	SE_character_currentsprite(personaje->character,0); 
	personaje->character->spr[0]->box->x=personaje->posx+32;
	personaje->character->spr[0]->box->y=personaje->posy;


}

void cargarenemigos()
{


	im_enemy = SE_image_load("assets/images/carpincho01.png");
	im_enemy2 = SE_image_load("assets/images/carpincho02.png");
	ani_enemy = SE_ani_init();
	SE_ani_addframe_segment(ani_enemy,im_enemy,10,0,0,64,64);
	SE_ani_addframe_segment(ani_enemy,im_enemy2,10,0,0,64,64);

//	enemigo=(enemy_t **)malloc(sizeof(enemy_t *)*6);
	int i=0;
	for(i=0;i<MAX_ENEMIES;i++){
//		printf("%d\n",i);
		spr_enemy[i] = SE_sprite_init(ani_enemy);
		SE_sprite_addbox(spr_enemy[i],0,0,50,64);
		enemigo[i]=create_enemy();
		enemigo[i]->character = SE_character_init();
		SE_character_addsprite(enemigo[i]->character,spr_enemy[i]);
		SE_character_currentsprite(enemigo[i]->character,0); 

	} 

	enemy_set_position(enemigo[3],50,0);
	enemy_set_position(enemigo[0],50,200);
	enemy_set_position(enemigo[2],250,350);
	enemy_set_position(enemigo[1],500,350);
	enemy_set_position(enemigo[4],500,200);
	enemy_set_position(enemigo[5],500,0);
	enemigo[1]->rotate=-1;
	enemigo[4]->rotate=-1;
	enemigo[5]->rotate=-1;

}


void absorver_enemigo(enemy_t *enemy)
{
	float distancia=(personaje->posx+128)-(enemy->posx+64);

	if(enemy->killed){


		if(enemy->zoom>0){
			enemy->zoom-=0.1;
			enemy->rotz+=30;
			if(distancia>0){ /*mirando a la izquierda*/
				enemy->posx+=distancia/4;
			}else{				/*mirando a la derecha*/
				enemy->posx+=distancia/10;
			}
			
//			printf("zoom:%f\n",enemy->zoom);
		}else{
			if(!enemy->sucked){
				SE_audio_playsound(sfx_suck);
				enemy_set_position(enemy,9999,9999);
				suck_enemy(personaje);
				enemy->sucked=1;
			}
		}
	}

}

void tratar_aspiradora()
{
//			tickaspiradora++;
//			if(tickaspiradora == 10){

	if(personaje->lookingright==1)
				{			
		SE_sprite_draw(sdisp01,personaje->posx + 100,personaje->posy + 50,0);
		sdisp01->box->x = personaje->posx + 100;
		sdisp01->box->y = personaje->posy + 50,0;
	}else{
		SE_sprite_draw_effects(sdisp01,personaje->posx - 35,personaje->posy + 50,0,1,1,0,180,0,1,1,1,1);
		sdisp01->box->x = personaje->posx - 35;
		sdisp01->box->y = personaje->posy + 50,0;
	}
//			tickaspiradora=0;
//			}
}

void tratar_disparo()
{
			tickdisparo++;	
			if(tickdisparo == 7)
			{
				int i;
				for(i=0;i < 8;i++)
				{
					if(bala[i].activa == 0)
					{
						bala[i].activa = 1;
						SE_audio_playsound(sfx_shoot);
						if(personaje->lookingright == 0)
						{	
							bala[i].sentido = 0;				
							bala[i].x = personaje->posx;
							bala[i].y = personaje->posy + 75;
							bala[i].box.x = personaje->posx;
							bala[i].box.y = personaje->posy + 75;
							break;

						}else{
							bala[i].sentido = 1;
							bala[i].x = personaje->posx + 100;
							bala[i].y = personaje->posy + 75;
							bala[i].box.x = personaje->posx+100;
							bala[i].box.y = personaje->posy + 75;
							break;

						}	
					}
	
				}
				tickdisparo = 0;	
			}

}


void muevepersonaje()
{
float incremento;
int rotate=0;
sdisp01->box->x = 9999;
sdisp01->box->y = 9999;

#ifdef DREAMCAST
	state=SE_input_poll(&joystick);
	if(state){	
        			

		if(state->buttons & JOY_RIGHT){  
			rotate=1;
			SE_character_currentsprite(personaje->character,1);
		}else if(state->buttons & JOY_LEFT){
			rotate=-1;
			SE_character_currentsprite(personaje->character,1);
		}
		if(state->buttons & JOY_BUTTON2){
			jump=1;
			SE_character_currentsprite(personaje->character,3);
		}else if(state->buttons & JOY_DOWN){

		}
		if(state->buttons & JOY_BUTTON0){
			tratar_aspiradora();
		}
		if(state->buttons & JOY_BUTTON1){
			tratar_disparo();
		}
		if(state->buttons & SE_QUIT){

		}
				


	}


#else

		//keys=SDL_GetKeyState(NULL);		
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
			tratar_aspiradora();
		}else if(keys[SDLK_z])
		{
			tratar_disparo();
			
		}
		

/*		if(keys[SDLK_f])
		{

			SE_screen_fullscreen(1);

		}

		if(keys[SDLK_F5])
		{
			if(debug_boxes)debug_boxes=0;
			else debug_boxes=1;

		}*/

#endif

//	if(move_character(personaje,timap, jump, rotate)==0)jump=0;
	move_character(personaje,timap, jump, rotate);
	jump=0;


}

void drawall()
{

	SE_character_draw_effects(personaje->character,personaje->posx,personaje->posy,20,1,1,0,personaje->rot,0,1,1,1,1);
	if(debug_boxes)	SE_drawrectangle(personaje->character->spr[0]->box->x,personaje->character->spr[0]->box->y,0,personaje->character->spr[0]->box->w,personaje->character->spr[0]->box->h,0,1,0,0,1);

	int i=0;
	for(i=0;i<MAX_ENEMIES;i++){
		if(enemigo[i]->killed)
			SE_character_draw_effects(enemigo[i]->character,enemigo[i]->posx,enemigo[i]->posy,20,enemigo[i]->zoom,enemigo[i]->zoom,0,enemigo[i]->rot,enemigo[i]->rotz,0.1,0.1,0.1,1);
		else
			SE_character_draw_effects(enemigo[i]->character,enemigo[i]->posx,enemigo[i]->posy,20,enemigo[i]->zoom,enemigo[i]->zoom,0,enemigo[i]->rot,enemigo[i]->rotz,1,1,1,1);
		if(debug_boxes)SE_drawrectangle(enemigo[i]->character->spr[0]->box->x,enemigo[i]->character->spr[0]->box->y,0,enemigo[i]->character->spr[0]->box->w,enemigo[i]->character->spr[0]->box->h,0,0.5,0.5,0,1);

	}

	if(debug_boxes)SE_drawrectangle(sdisp01->box->x,sdisp01->box->y,0,sdisp01->box->w,sdisp01->box->h,0,1,0,0,1);
	SE_image_full_draw(face_jess,10,410,0,1,1,0,0,0,1,1,1,0.9);
	SE_image_full_draw(life,80,410,0,1,1,0,0,0,1,1,1,0.7);
	if(personaje->load>=MAX_ENEMIES)SE_image_draw(youwin,0,0,0);
	if(personaje->kill)SE_image_draw(youlose,0,0,0);

}


int check_collisions()
{
	int i=0;
	int j=0;
	int k=0;
	int lose=0;
	for(i=0;i<MAX_ENEMIES;i++){

		for(j=0;j<8;j++){
		
			/*colisión de una bala con un enemigo*/
			if(SE_box_check(enemigo[i]->character->spr[0]->box,&bala[j].box)){

			//	printf("ENEMY DED!\n");
				enemigo[i]->killed=1;
				if(enemigo[i]->lookingright){
					enemigo[i]->rot=0;
				}else{
					enemigo[i]->rot=-180.0f;
				}
				bala[j].activa = 0;
				bala[j].x = 9999;
				bala[j].y = 9999;
				bala[j].box.x = 9999;
				bala[j].box.y = 9999;
			}
		}
		/*colisión del personaje con un enemigo*/
		if((SE_full_box_check(personaje->character->spr[0]->box,enemigo[i]->character->spr[0]->box))&&(enemigo[i]->killed!=1)&&(personaje->kill!=1)){

		//	printf("DED!\n");
			SE_audio_stopmusic();
			SE_audio_playsound(sfx_death);
//			return 1;
//			break;
			lose=1;
		}
		/*colisión de la aspiradora con un enemigo*/
		if((SE_full_box_check(enemigo[i]->character->spr[0]->box,sdisp01->box))&&(enemigo[i]->killed==1)&&(enemigo[i]->sucked==0)){
			absorver_enemigo(enemigo[i]);
			if(personaje->load>=MAX_ENEMIES){
				SE_audio_stopmusic();
				SE_audio_playsound(sfx_win);

			}

		}else if((enemigo[i]->zoom<1)){

			enemigo[i]->release++;
			if(enemigo[i]->release>10){
				enemigo[i]->killed=0;
				enemigo[i]->zoom=1;
				enemigo[i]->release=0;
				enemigo[i]->rotz=0;

			}

		}else if((enemigo[i]->killed==1)){

			enemigo[i]->release++;
			if(enemigo[i]->release>100){
				enemigo[i]->killed=0;
				enemigo[i]->zoom=1;
				enemigo[i]->release=0;
				enemigo[i]->rotz=0;

			}

		}

		for(k=0;k<MAX_ENEMIES;k++){
			if(SE_full_box_check(enemigo[i]->character->spr[0]->box,enemigo[k]->character->spr[0]->box))
			{
			//	printf("colision de enemigos!\n");
				if(enemigo[i]->lookingright==enemigo[k]->lookingright){
					if((enemigo[i]->rotated==1)&&(enemigo[k]->rotated==1)){
					//	if(enemigo[k]->lookingright)enemigo[k]->rotate=1;
					//	else enemigo[k]->rotate=-1;
						//enemigo[k]->rotate=enemigo[k]->lookingright*-1;


					}
/*					if((enemigo[i]->lookingright==1)&&(enemigo[i]->rotated==1)){
						enemigo[i]->rotate=1;
						enemigo[k]->rotate=-1;
					}
					else{
						enemigo[i]->rotate=-1;
						enemigo[k]->rotate=1;
					}*/
				}else{
					if((enemigo[i]->rotated==1)&&(enemigo[k]->rotated==1)){
						if(!enemigo[i]->killed)enemigo[i]->rotate=-1;
						if(!enemigo[i]->killed)enemigo[k]->rotate=1;
					}
					else{
					//	enemigo[i]->rotate=enemigo[i]->rotate*-1;
					//	enemigo[k]->rotate=enemigo[k]->rotate*-1;
					}

				}

			}
		}

	}

	return lose;
}

void loadsfx()
{
	sfx_death=SE_audio_loadsound("assets/sound/death.ogg");
	sfx_shoot=SE_audio_loadsound("assets/sound/shoot.ogg");
	sfx_suck=SE_audio_loadsound("assets/sound/suck.wav");
	sfx_hit=SE_audio_loadsound("assets/sound/suck.ogg");
	sfx_win=SE_audio_loadsound("assets/sound/win.ogg");


}


int check_restart()
{

int i;
#ifdef DREAMCAST
	state=SE_input_poll(&joystick);
	if(state){	
        			

		if(state->buttons & JOY_BUTTON6){  
#else
		//keys=SDL_GetKeyState(NULL);
		if(keys[SDLK_F3])
		{
#endif
			SE_audio_stopmusic();
			init_var_title();
			init_var_menu();
			tick_screen = 0;
			exittitle = 0;
			exitzone = 0;
			exitmenu = 0;
			cont_screen = 0;
			for(i=0;i<MAX_ENEMIES;i++){
				restart_enemy(enemigo[i]);
			}
			restart_character(personaje);
			return 1;
			

		}

#ifdef DREAMCAST
	}
#endif	

}

//SDL_main(int argc, char *argv[])
int main(int argc,char* args[])
{
       // __android_log_print(ANDROID_LOG_INFO,"Ecosquad","MAIN!!!!\n");
	//printf("MAIN!!!!\n");
	SE_utils_log("MAIN!!!!\n");

	int quit = 0;
	int stop = 0;
	cont_screen = 0;
	tick_screen = 0;
	SE_music *musica_ingame;
	SE_music *musica_intro;
	SE_music *musica_select;

	//SE_initgraphics();
	SE_utils_log("iniciando pantalla\n");
	SE_screen_init(0,0,32);
	SE_utils_log("iniciada pantalla\n");
	SE_console_init();
	SE_timer_setframerate(60);

#ifdef DREAMCAST
	fs_chdir("/rd");
	SE_input_init();
	printf("hay %d joysticks disponibles\n",SE_input_enum());
	joystick = SE_input_open(0);
#endif

	SE_audio_init(44100, 16, 1);
	loadsfx();
	musica_ingame=SE_audio_loadmusic("assets/music/music.ogg");
	musica_intro=SE_audio_loadmusic("assets/music/intro.ogg");
	musica_select=SE_audio_loadmusic("assets/music/select.ogg");
	SE_audio_setmusicvolume(100);
	SE_audio_setsoundvolume(120);

	init_var_title();
	load_images_title();



	while(quit == 0)
	{
		switch(cont_screen)
		{
			case 0:
				if(!SE_audio_isplayingmusic())SE_audio_playmusic(musica_intro);
				screentitle();
#ifdef DREAMCAST
				state=SE_input_poll(&joystick);
				if(state){	
        			
	
				if(state->buttons & JOY_BUTTON0){ 
#else
				//keys=SDL_GetKeyState(NULL);
	
		
				if(keys[SDLK_z])
				{
#endif									
					exittitle = 1;
									
				}

#ifndef DREAMCAST
				if(keys[SDLK_f])
				{

					//SE_screen_fullscreen(1);
					SE_console_toggle();

				}
#endif

#ifdef DREAMCAST
				}
#endif
				if(exittitle == 1)
				{
					if(tick_screen == 100)
					{					
						cont_screen = 1;
						init_var_menu();
						clean_images_title();
						load_images_menu();
						tick_screen = 0;
						SE_audio_stopmusic();
					}
					tick_screen++;
				}	
				break;

			case 1:
				if(!SE_audio_isplayingmusic())SE_audio_playmusic(musica_select);
				screenmenu();
				if(exitmenu == 1)
				{
					if(tick_screen == 100)						
					{
						cont_screen = 2;
						tick_screen = 0;
						init_var_zone();
						clean_images_menu();
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
							clean_images_zone();
							cargarsprites();
							cargarenemigos();
							cargardisparoplayer();
							inicializarbalas();
							SE_audio_stopmusic();

						}
						tick_screen++;	
					}	
				break;
			case 3:	
			if((!SE_audio_isplayingmusic())&&(personaje->load<MAX_ENEMIES)&&(personaje->kill!=1))SE_audio_playmusic(musica_ingame);	
			SE_screen_clear(0,0,0,0);
			SE_image_draw(back,0,0,0);

			SE_tilemap_draw(timap,0,0,10);

			if(debug_boxes)SE_tilemap_drawbox(timap,0,10);

			if(!personaje->kill){
				muevepersonaje();
				moverbalas();
				int i=0;
				for(i=0;i<MAX_ENEMIES;i++){
					update_enemy_position(enemigo[i],timap);
	//				printf("enemigo %d %f %f\n",i,enemigo[i]->posx,enemigo[i]->posy);
				}
				if(check_collisions()){ //Impacto al personaje
				//	stop=1;
					kill_character(personaje);
				}
			}else{
				kill_character(personaje);


			}

			drawall();
			if(check_restart())stop=0;
			break;

		}
			/*trocito de codigo de SDL que usamos para detectar si se cierra la ventana*/	

#ifdef DREAMCAST


#else

			while( SDL_PollEvent( &event ) )
	        	{
			
				if( event.type == SDL_QUIT )
				{

					SE_character_clean(personaje->character);
					quit = 1;
				}
			

			}

#endif

		/*flipeamos todo el cuadro*/
		SE_console_draw();
		SE_screen_flip();
		SE_timer_waitframerate();
			
	
	}

	return 0;


}


