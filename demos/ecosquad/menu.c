#include "menu.h"

Uint8 *keys_menu;

SE_image *bgmenu;
SE_image *arrowl;
SE_image *arrowr;
SE_image *j_portr;
SE_image *k_portr;
SE_image *p1;

int player1_sel;

int const jx = 57;
int const kx = 345;
int p1x;
int const p1y = 100;

float contzoom;
float contalpha;
float dalpha;

float alphamenu;

int selected;

int exitmenu;



float jzoom,kzoom;
float jalpha,kalpha;

float jroty,kroty;


void init_var_menu()
{

	p1x = jx;

	contzoom = 1;
	contalpha = 0;
	dalpha = 0.001;
	player1_sel = 0;
	selected = 0;

	jzoom = 1;
	jalpha = 1;

	kzoom = 1;
	kalpha = 0.8;
	
	jroty = 0;
	kroty = 0;

	alphamenu = 0;

}

void load_images_menu()
{


bgmenu = SE_image_load("assets/images/bgmenu.png");

arrowl = SE_image_load("assets/images/arrowl.png");
arrowr = SE_image_load("assets/images/arrowr.png");
j_portr = SE_image_load("assets/images/j_portr.png");
k_portr = SE_image_load("assets/images/k_portr.png");
p1  = SE_image_load("assets/images/p1.png");

SE_image_size(bgmenu,640,480);
SE_image_size(arrowl,50,57);
SE_image_size(arrowr,50,57);
SE_image_size(j_portr,273,362);
SE_image_size(k_portr,273,362);
SE_image_size(p1,68,52);

}

void clean_images_menu()
{

	SE_image_clean(bgmenu);
	SE_image_clean(arrowl);
	SE_image_clean(arrowr);
	SE_image_clean(j_portr);
	SE_image_clean(k_portr);
	SE_image_clean(p1);



}







void screenmenu()
{

SE_input_joystick *joystick;
SE_input_state *state;

	SE_image_draw(bgmenu,0,0,0);
	SE_image_full_draw(j_portr,40,80,0,jzoom,jzoom,0,jroty,0,1,1,1,jalpha);
	SE_image_full_draw(k_portr,330,80,0,kzoom,kzoom,0,kroty,0,1,1,1,kalpha);
	SE_image_full_draw(arrowl,10,220,0,1,1,0,0,0,1,1,1,contalpha);
	SE_image_full_draw(arrowr,570,220,0,1,1,0,0,0,1,1,1,contalpha);

	contalpha = contalpha + dalpha;

	if(contalpha >= 1)dalpha = -0.001;
	if(contalpha <= 0)dalpha = +0.001;

	SE_image_draw(p1,p1x,p1y,0);

	if(selected == 0)
	{
#ifdef DREAMCAST
	state=SE_input_poll(&joystick);
	if(state){	
        			
	
	if(state->buttons & JOY_RIGHT){ 
#else
	//keys_menu=SDL_GetKeyState(NULL);

		if(keys_menu[SDLK_RIGHT])
		{
#endif
			player1_sel = 1;
			p1x = kx;
			kalpha = 1;
			jalpha = 0.8;

		}
#ifdef DREAMCAST

	if(state->buttons & JOY_LEFT){ 
#else
		if(keys_menu[SDLK_LEFT]){
#endif

			player1_sel = 0;
			p1x = jx; 
			jalpha = 1;
			kalpha = 0.8;

		}
#ifdef DREAMCAST

	if(state->buttons & JOY_BUTTON0){ 
#else
		if(keys_menu[SDLK_z]){
#endif
			selected = 1;
		}	
	}
#ifdef DREAMCAST
	}
#endif
	if((selected == 1)&&(player1_sel == 0))
	{
		jzoom = 1;

		jroty+=20;
		exitmenu = 1;

	}
	if((selected == 1)&&(player1_sel == 1))
	{
		kzoom = 1;

		kroty+=20;
		exitmenu = 1;

	}

	SE_drawrectangle(0,0,0,640,480,1,1,1,1,alphamenu);

	if(exitmenu == 1)
	{
		alphamenu += 0.01;
	}


}

