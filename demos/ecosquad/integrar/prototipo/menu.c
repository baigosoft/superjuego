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


bgmenu = SE_image_load("bgmenu.png");
arrowl = SE_image_load("arrowl.png");
arrowr = SE_image_load("arrowr.png");
j_portr = SE_image_load("j_portr.png");
k_portr = SE_image_load("k_portr.png");
p1  = SE_image_load("p1.png");

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

	SE_image_draw(bgmenu,0,0,0);
	SE_image_full_draw(j_portr,40,80,0,jzoom,jzoom,0,jroty,0,1,1,1,jalpha);
	SE_image_full_draw(k_portr,330,80,0,kzoom,kzoom,0,kroty,0,1,1,1,kalpha);
	SE_image_full_draw(arrowl,10,220,0,1,1,0,0,0,1,1,1,contalpha);
	SE_image_full_draw(arrowr,570,220,0,1,1,0,0,0,1,1,1,contalpha);

	contalpha = contalpha + dalpha;

	if(contalpha >= 1)dalpha = -0.001;
	if(contalpha <= 0)dalpha = +0.001;

	SE_image_draw(p1,p1x,p1y,0);

	keys_menu=SDL_GetKeyState(NULL);
	if(selected == 0)
	{
		if(keys_menu[SDLK_RIGHT])
		{
			player1_sel = 1;
			p1x = kx;
			kalpha = 1;
			jalpha = 0.8;

		}
		if(keys_menu[SDLK_LEFT]){

			player1_sel = 0;
			p1x = jx; 
			jalpha = 1;
			kalpha = 0.8;

		}
		if(keys_menu[SDLK_z]){
			selected = 1;
		}	
	}
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

