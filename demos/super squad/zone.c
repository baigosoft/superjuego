#include "zone.h"

Uint8 *keys_zone;

SE_image *mapzone;
SE_image *tilebgzone;

SE_image *fzoneimg;

SE_font *fontzone;

SE_tilemap *bgzone;

int selected_zone;
int tick_zone;
float alpha_zone_title;
float alpha_zone_text;
float rot_zone;

float alphazone;
int exitzone;

void init_var_zone()
{

selected_zone = 0;
tick_zone = 0;
alpha_zone_title = 0;
alpha_zone_text = 0;
rot_zone = 0;

alphazone = 0;
exitzone = 0;

}







void load_images_zone()
{


	/*cargamos imagenes*/
	mapzone = SE_image_load("assets/images/mapzone.png");
	tilebgzone = SE_image_load("assets/images/tilebgzone.png");
	fzoneimg = SE_image_load("assets/images/font256.png");


	
	/*creamos tilemap de fondo*/
	bgzone = SE_tilemap_init(32,32,20,15);
	SE_tilemap_addimage(bgzone,tilebgzone);
	SE_tilemap_loadmapimage(bgzone,"assets/tilemaps/mapimagezone.txt");

	/*creamos fuente*/
	fontzone = SE_font_create(fzoneimg,16,16,16,16);
		

	


}

void clean_images_zone()
{

	SE_image_clean(mapzone);
	SE_image_clean(tilebgzone);
	SE_image_clean(fzoneimg);
	
}







void screenzone()
{
SE_input_joystick *joystick;
SE_input_state *state;

	/*dibujamos tilemap de fondo*/
	SE_tilemap_draw(bgzone,0,0,0);


	/*dibujamos el mapa*/
	SE_image_segment_draw(mapzone,0,0,469,358,89,95,0,1,1,0,0,0,1,1,1,1);

	/*dibujamos los segmentos*/





#ifdef DREAMCAST
	state=SE_input_poll(&joystick);
	if(state){	
        			
	
	if(state->buttons & JOY_RIGHT){ 
#else
	
	//keys_zone=SDL_GetKeyState(NULL);
	
	if(keys_zone[SDLK_RIGHT])
	{
#endif
		tick_zone++;
		if(tick_zone == 10) 
		{	
			selected_zone++;
			tick_zone = 0;
		}

	}
#ifdef DREAMCAST
	if(state->buttons & JOY_LEFT){ 
#else
	if(keys_zone[SDLK_LEFT])
	{
#endif
		tick_zone++;
		if(tick_zone == 10) 
		{	
			selected_zone--;
			tick_zone = 0;
		}
	}

	
	

	if(selected_zone < 0) selected_zone = 4;
	if(selected_zone > 4) selected_zone = 0;

	switch(selected_zone)
	{
		case 0:

			SE_image_segment_draw(mapzone,480,0,257,153,104,96,0,1,1,0,0,0,1,1,1,1);/*zona 0*/
			SE_image_segment_draw(mapzone,750,350,67,128,190,50,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"EL IMPENETRABLE (LA CORNISA S.A.)",70,440,0,1,1,1,0,0,0,0,0,1);
			break;
		case 1:

			SE_image_segment_draw(mapzone,750,0,199,221,253,170,0,1,1,0,0,0,1,1,1,1);/*zona 1*/
			SE_image_segment_draw(mapzone,750,350,67,128,290,173,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"AVIA TERAI (LA COLCOMBERT CORP.)",70,440,0,1,1,1,0,0,0,0,0,1);
			break;
		case 2:

			SE_image_segment_draw(mapzone,480,200,42,66,384,263,0,1,1,0,0,0,1,1,1,1);/*zona 2*/
			SE_image_segment_draw(mapzone,750,350,67,128,370,180,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"MACHAGAI - BOSQUE PERDIDO",70,440,0,1,1,1,0,0,0,0,0,1);
			break;		
		case 3:

			SE_image_segment_draw(mapzone,480,270,139,157,414,219,0,1,1,0,0,0,1,1,1,1);/*zona 3*/
			SE_image_segment_draw(mapzone,750,350,67,128,445,180,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"TIROL/LA ESCONDIDA (INDUTAN S.A.)",70,440,0,1,1,1,0,0,0,0,0,1);
			break;	
		case 4:
			SE_image_segment_draw(mapzone,750,270,202,67,284,350,0,1,1,0,0,0,1,1,1,1);/*zona 4*/
			SE_image_segment_draw(mapzone,750,350,67,128,320,275,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"VILLA ANGELA (MONSONTO CORP.)",70,440,0,1,1,1,0,0,0,0,0,1);
			break;
		default:	

			SE_image_segment_draw(mapzone,480,0,257,153,104,96,0,1,1,0,0,0,1,1,1,1);/*zona 0*/
			SE_image_segment_draw(mapzone,750,350,67,128,190,50,0,1,1,0,rot_zone,0,1,1,1,1);/*flecha*/
			SE_font_draw(fontzone,"EL IMPENETRABLE (LA CORNISA S.A.)",70,440,0,1,1,1,0,0,0,0,0,1);
			break;
	}

	
	rot_zone++;
	if(rot_zone > 360)rot_zone = 0;
	
	/*titulo*/
	SE_image_segment_draw(mapzone,0,480,545,30,20,20,0,1,1,0,0,0,1,1,1,alpha_zone_title);
	if(alpha_zone_title < 1)
	{
		alpha_zone_title += 0.01;

	}

	SE_drawrectangle(0,0,0,640,480,1,0,0,0,alphazone);
#ifdef DREAMCAST
	if(state->buttons & JOY_BUTTON0){ 
#else
	if(keys_zone[SDLK_z])
	{
#endif
		exitzone = 1;
	}

#ifdef DREAMCAST
	}
#endif

	if(exitzone == 1)
	{
		alphazone += 0.01;
	}


}

