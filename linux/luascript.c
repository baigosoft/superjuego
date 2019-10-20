#include "luascript.h"

static int l_SE_screen_fullscreen(lua_State *L);

static int l_SE_screen_init(lua_State *L);

static int l_SE_screen_enable2d(lua_State *L);

static int l_SE_screen_disable2d(lua_State *L);

static int l_SE_screen_clear(lua_State *L);

static int l_SE_screen_flip(lua_State *L);

static int l_SE_screen_rotate(lua_State *L);

static int l_SE_screen_scale(lua_State *L);

static int l_SE_screen_resettransform(lua_State *L);



static int l_SE_image_load(lua_State *L);

static int l_SE_image_dimentions(lua_State *L);

static int l_SE_image_segment_draw_fx(lua_State *L);

static int l_SE_image_segment_draw_wh(lua_State *L);

static int l_SE_image_segment_draw(lua_State *L);

static int l_SE_image_draw_fx(lua_State *L);

static int l_SE_image_draw_wh(lua_State *L);

static int l_SE_image_draw(lua_State *L);

static int l_SE_image_segment_draw_transf(lua_State *L);

static int l_SE_image_draw_transf(lua_State *L);

static int l_SE_image_clean(lua_State *L);



static int l_SE_ani_init(lua_State *L);

static int l_SE_ani_width(lua_State *L);

static int l_SE_ani_height(lua_State *L);

static int l_SE_ani_frame_delay_set(lua_State *L);

static int l_SE_ani_addframe_segment(lua_State *L);

static int l_SE_ani_addframe(lua_State *L);

static int l_SE_ani_create_from_img(lua_State *L);

static int l_SE_ani_clean(lua_State *L);



static int l_SE_animator_init(lua_State *L);

static int l_SE_animator_status(lua_State *L);

static int l_SE_animator_start(lua_State *L);

static int l_SE_animator_stop(lua_State *L);

static int l_SE_animator_initend_set(lua_State *L);

static int l_SE_animator_reset(lua_State *L);

static int l_SE_animator_delaypercent(lua_State *L);

static int l_SE_animator_draw_fx(lua_State *L);

static int l_SE_animator_draw_wh(lua_State *L);

static int l_SE_animator_draw(lua_State *L);

static int l_SE_animator_draw_transf(lua_State *L);

static int l_SE_animator_clean(lua_State *L);



static int l_SE_sprite_init(lua_State *L);

static int l_SE_sprite_img_segment_add(lua_State *L);

static int l_SE_sprite_img_add(lua_State *L);

static int l_SE_sprite_ani_add(lua_State *L);

static int l_SE_sprite_width(lua_State *L);

static int l_SE_sprite_height(lua_State *L);

static int l_SE_sprite_offset_set(lua_State *L);

static int l_SE_sprite_box_init(lua_State *L);

static int l_SE_sprite_box_set(lua_State *L);

static int l_SE_sprite_collision_single(lua_State *L);

static int l_SE_sprite_collision_box(lua_State *L);

static int l_SE_sprite_collision(lua_State *L);

//static int l_SE_sprite_collision_pf_single(lua_State *L);

//static int l_SE_sprite_collision_pf_current(lua_State *L);

//static int l_SE_sprite_collision_pf(lua_State *L);

static int l_SE_sprite_clean(lua_State *L);

static int l_SE_sprite_draw_fx(lua_State *L);

static int l_SE_sprite_draw_wh(lua_State *L);

static int l_SE_sprite_draw(lua_State *L);

static int l_SE_sprite_draw_transf(lua_State *L);



static int l_SE_tile_img_add(lua_State *L);

static int l_SE_tile_ani_add(lua_State *L);

static int l_SE_tile_type(lua_State *L);

static int l_SE_tile_draw(lua_State *L);



static int l_SE_tileset_init(lua_State *L);

static int l_SE_tileset_img_segment_add(lua_State *L);

static int l_SE_tileset_create_from_img(lua_State *L);

static int l_SE_tileset_img_add(lua_State *L);

static int l_SE_tileset_ani_add(lua_State *L);

static int l_SE_tileset_draw(lua_State *L);

static int l_SE_tileset_clean(lua_State *L);



static int l_SE_tilemap_init(lua_State *L);

static int l_SE_tilemap_clean(lua_State *L);

static int l_SE_tilemap_tileset_set(lua_State *L);

static int l_SE_tilemap_data_load(lua_State *L);

static int l_SE_tilemap_maptile_load(lua_State *L);

static int l_SE_tilemap_maptile_bin_load(lua_State *L);

static int l_SE_tilemap_mapcoll_load(lua_State *L);

static int l_SE_tilemap_mapcoll_bin_load(lua_State *L);

static int l_SE_tilemap_draw(lua_State *L);

static int l_SE_tilemap_collision(lua_State *L);



static int l_SE_box_init(lua_State *L);

static int l_SE_box_position_set(lua_State *L);

static int l_SE_box_dimentions_set(lua_State *L);

static int l_SE_box_get(lua_State *L);



static int l_SE_transf_init(lua_State *L);

static int l_SE_transf_position_set(lua_State *L);

static int l_SE_transf_dimentions_set(lua_State *L);

static int l_SE_transf_zoom_set(lua_State *L);

static int l_SE_transf_rotation_set(lua_State *L);

static int l_SE_transf_rgb_set(lua_State *L);

static int l_SE_transf_alpha_set(lua_State *L);

static int l_SE_transf_get(lua_State *L);




static int l_SE_coll_check_position(lua_State *L);

static int l_SE_coll_check(lua_State *L);



static int l_SE_font_create(lua_State *L);

static int l_SE_font_space_set(lua_State *L);

static int l_SE_font_space(lua_State *L);

static int l_SE_font_letterspacing_set(lua_State *L);

static int l_SE_font_letterspacing(lua_State *L);

static int l_SE_font_lineheight_set(lua_State *L);

static int l_SE_font_lineheight(lua_State *L);

static int l_SE_font_draw_fx(lua_State *L);

static int l_SE_font_draw(lua_State *L);

static int l_SE_font_draw_transf(lua_State *L);

static int l_SE_font_clean(lua_State *L);



static int l_SE_prim_drawpoint(lua_State *L);

static int l_SE_prim_drawline(lua_State *L);

static int l_SE_prim_drawrectangle(lua_State *L);

static int l_SE_prim_drawcircle(lua_State *L);



static int l_SE_utils_powerof2(lua_State *L);

static int l_SE_utils_log(lua_State *L);

static int l_SE_utils_logvertices(lua_State *L);

static int l_SE_utils_logvertices_init(lua_State *L);

static int l_SE_utils_vertices(lua_State *L);



static int l_SE_timer_gettime(lua_State *L);

static int l_SE_timer_reset(lua_State *L);

static int l_SE_timer_current(lua_State *L);

static int l_SE_timer_setframerate(lua_State *L);

static int l_SE_timer_waitframerate(lua_State *L);

static int l_SE_timer_start(lua_State *L);

static int l_SE_timer_check(lua_State *L);



static int l_SE_input_state_init(lua_State *L);

static int l_SE_input_mapping_init(lua_State *L);

static int l_SE_input_joystick_init(lua_State *L);

static int l_SE_input_open(lua_State *L);

static int l_SE_input_enum(lua_State *L);

static int l_SE_input_poll(lua_State *L);

static int l_SE_input_button(lua_State *L);

static int l_SE_input_init(lua_State *L);

static int l_SE_input_close(lua_State *L);



static int l_SE_audio_init(lua_State *L);

static int l_SE_audio_close(lua_State *L);

static int l_SE_audio_enablesound(lua_State *L);

static int l_SE_audio_disablesound(lua_State *L);

static int l_SE_audio_enablemusic(lua_State *L);

static int l_SE_audio_disablemusic(lua_State *L);

static int l_SE_audio_loadmusic(lua_State *L);

static int l_SE_audio_playmusic(lua_State *L);

static int l_SE_audio_stopmusic(lua_State *L);

static int l_SE_audio_setmusicvolume(lua_State *L);

static int l_SE_audio_isplayingmusic(lua_State *L);

static int l_SE_audio_loadsound(lua_State *L);

static int l_SE_audio_playsound(lua_State *L);

static int l_SE_audio_setsoundvolume(lua_State *L);



void SE_lua_init(char *pathfile)
{

	//lua_State *L = luaL_newstate();

	lua_State *L = lua_open();

	luaL_openlibs(L);

/*	lua_pushcfunction(L,l_SE_screen_init);
	lua_setglobal(L,"se_screen_init");*/
	
	//RENDER
	lua_register(L,"SE_screen_fullscreen",l_SE_screen_fullscreen);
	lua_register(L,"SE_screen_init",l_SE_screen_init);
	lua_register(L,"SE_screen_enable2d",l_SE_screen_enable2d);
	lua_register(L,"SE_screen_disable2d",l_SE_screen_disable2d);
	lua_register(L,"SE_screen_clear",l_SE_screen_clear);
	lua_register(L,"SE_screen_flip",l_SE_screen_flip);
	lua_register(L,"SE_screen_rotate",l_SE_screen_rotate);
	lua_register(L,"SE_screen_scale",l_SE_screen_scale);
	lua_register(L,"SE_screen_resettransform",l_SE_screen_resettransform);

	//IMAGE
	lua_register(L,"SE_image_load",l_SE_image_load);
	lua_register(L,"SE_image_dimentions",l_SE_image_dimentions);
	lua_register(L,"SE_image_segment_draw_fx",l_SE_image_segment_draw_fx);
	lua_register(L,"SE_image_segment_draw_wh",l_SE_image_segment_draw_wh);
	lua_register(L,"SE_image_segment_draw",l_SE_image_segment_draw);
	lua_register(L,"SE_image_draw_fx",l_SE_image_draw_fx);
	lua_register(L,"SE_image_draw_wh",l_SE_image_draw_wh);
	lua_register(L,"SE_image_draw",l_SE_image_draw);
	lua_register(L,"SE_image_segment_draw_transf",l_SE_image_segment_draw_transf);
	lua_register(L,"SE_image_draw_transf",l_SE_image_draw_transf);
	lua_register(L,"SE_image_clean",l_SE_image_clean);

	//ANIMATION
	lua_register(L,"SE_ani_init",l_SE_ani_init);
	lua_register(L,"SE_ani_width",l_SE_ani_width);
	lua_register(L,"SE_ani_height",l_SE_ani_height);
	lua_register(L,"SE_ani_frame_delay_set",l_SE_ani_frame_delay_set);
	lua_register(L,"SE_ani_addframe_segment",l_SE_ani_addframe_segment);
	lua_register(L,"SE_ani_addframe",l_SE_ani_addframe);
	lua_register(L,"SE_ani_create_from_img",l_SE_ani_create_from_img);
	lua_register(L,"SE_ani_clean",l_SE_ani_clean);

	//ANIMATOR
	lua_register(L,"SE_animator_init",l_SE_animator_init);
	lua_register(L,"SE_animator_status",l_SE_animator_status);
	lua_register(L,"SE_animator_start",l_SE_animator_start);
	lua_register(L,"SE_animator_stop",l_SE_animator_stop);
	lua_register(L,"SE_animator_initend_set",l_SE_animator_initend_set);
	lua_register(L,"SE_animator_reset",l_SE_animator_reset);
	lua_register(L,"SE_animator_delaypercent",l_SE_animator_delaypercent);
	lua_register(L,"SE_animator_draw_fx",l_SE_animator_draw_fx);
	lua_register(L,"SE_animator_draw_wh",l_SE_animator_draw_wh);
	lua_register(L,"SE_animator_draw",l_SE_animator_draw);
	lua_register(L,"SE_animator_draw_transf",l_SE_animator_draw_transf);
	lua_register(L,"SE_animator_clean",l_SE_animator_clean);

	//SPRITE
	lua_register(L,"SE_sprite_init",l_SE_sprite_init);
	lua_register(L,"SE_sprite_img_segment_add",l_SE_sprite_img_segment_add);
	lua_register(L,"SE_sprite_img_add",l_SE_sprite_img_add);
	lua_register(L,"SE_sprite_ani_add",l_SE_sprite_ani_add);
	lua_register(L,"SE_sprite_width",l_SE_sprite_width);
	lua_register(L,"SE_sprite_height",l_SE_sprite_height);
	lua_register(L,"SE_sprite_offset_set",l_SE_sprite_offset_set);
	lua_register(L,"SE_sprite_box_init",l_SE_sprite_box_init);
	lua_register(L,"SE_sprite_box_set",l_SE_sprite_box_set);
	lua_register(L,"SE_sprite_collision_single",l_SE_sprite_collision_single);
	lua_register(L,"SE_sprite_collision",l_SE_sprite_collision);
	lua_register(L,"SE_sprite_collision_box",l_SE_sprite_collision_box);
	//lua_register(L,"SE_sprite_collision_pf_single",l_SE_sprite_collision_pf_single);
	//lua_register(L,"SE_sprite_collision_pf_current",l_SE_sprite_collision_pf_current);
	//lua_register(L,"SE_sprite_collision_pf",l_SE_sprite_collision_pf);
	lua_register(L,"SE_sprite_clean",l_SE_sprite_clean);
	lua_register(L,"SE_sprite_draw_fx",l_SE_sprite_draw_fx);
	lua_register(L,"SE_sprite_draw_wh",l_SE_sprite_draw_wh);
	lua_register(L,"SE_sprite_draw",l_SE_sprite_draw);
	lua_register(L,"SE_sprite_draw_transf",l_SE_sprite_draw_transf);

	//TILE
	//lua_register(L,"SE_tile_img_add",l_SE_tile_img_add);
	//lua_register(L,"SE_tile_ani_add",l_SE_tile_ani_add);
	//lua_register(L,"SE_tile_type",l_SE_tile_type);
	//lua_register(L,"SE_tile_draw",l_SE_tile_draw);

	//TILESET
	lua_register(L,"SE_tileset_init",l_SE_tileset_init);
	lua_register(L,"SE_tileset_img_segment_add",l_SE_tileset_img_segment_add);
	lua_register(L,"SE_tileset_create_from_img",l_SE_tileset_create_from_img);
	lua_register(L,"SE_tileset_img_add",l_SE_tileset_img_add);
	lua_register(L,"SE_tileset_ani_add",l_SE_tileset_ani_add);
	//lua_register(L,"SE_tileset_draw",l_SE_tileset_draw);
	lua_register(L,"SE_tileset_clean",l_SE_tileset_clean);

	//TILEMAP
	lua_register(L,"SE_tilemap_init",l_SE_tilemap_init);
	lua_register(L,"SE_tilemap_clean",l_SE_tilemap_clean);
	lua_register(L,"SE_tilemap_tileset_set",l_SE_tilemap_tileset_set);
	lua_register(L,"SE_tilemap_data_load",l_SE_tilemap_data_load);
	lua_register(L,"SE_tilemap_maptile_load",l_SE_tilemap_maptile_load);
	lua_register(L,"SE_tilemap_maptile_bin_load",l_SE_tilemap_maptile_bin_load);
	lua_register(L,"SE_tilemap_mapcoll_load",l_SE_tilemap_mapcoll_load);
	lua_register(L,"SE_tilemap_mapcoll_bin_load",l_SE_tilemap_mapcoll_bin_load);
	lua_register(L,"SE_tilemap_draw",l_SE_tilemap_draw);
	lua_register(L,"SE_tilemap_collision",l_SE_tilemap_collision);	

	//BOX
	lua_register(L,"SE_box_init",l_SE_box_init);
	lua_register(L,"SE_box_position_set",l_SE_box_position_set);
	lua_register(L,"SE_box_dimentions_set",l_SE_box_dimentions_set);
	lua_register(L,"SE_box_get",l_SE_box_get);

	//TRANSFORMATION
	lua_register(L,"SE_transf_init",l_SE_transf_init);
	lua_register(L,"SE_transf_position_set",l_SE_transf_position_set);
	lua_register(L,"SE_transf_dimentions_set",l_SE_transf_dimentions_set);
	lua_register(L,"SE_transf_zoom_set",l_SE_transf_zoom_set);
	lua_register(L,"SE_transf_rotation_set",l_SE_transf_rotation_set);
	lua_register(L,"SE_transf_rgb_set",l_SE_transf_rgb_set);
	lua_register(L,"SE_transf_alpha_set",l_SE_transf_alpha_set);
	lua_register(L,"SE_transf_get",l_SE_transf_get);

	//COLLISION
	lua_register(L,"SE_coll_check_position",l_SE_coll_check_position);
	lua_register(L,"SE_coll_check",l_SE_coll_check);

	//FONT
	lua_register(L,"SE_font_create",l_SE_font_create);
	lua_register(L,"SE_font_space_set",l_SE_font_space_set);
	lua_register(L,"SE_font_space",l_SE_font_space);
	lua_register(L,"SE_font_letterspacing_set",l_SE_font_letterspacing_set);
	lua_register(L,"SE_font_letterspacing",l_SE_font_letterspacing);
	lua_register(L,"SE_font_lineheight_set",l_SE_font_lineheight_set);
	lua_register(L,"SE_font_lineheight",l_SE_font_lineheight);
	lua_register(L,"SE_font_draw_fx",l_SE_font_draw_fx);
	lua_register(L,"SE_font_draw",l_SE_font_draw);
	lua_register(L,"SE_font_draw_transf",l_SE_font_draw_transf);
	lua_register(L,"SE_font_clean",l_SE_font_clean);

	//PRIMITIVES
	lua_register(L,"SE_prim_drawpoint",l_SE_prim_drawpoint);
	lua_register(L,"SE_prim_drawline",l_SE_prim_drawline);
	lua_register(L,"SE_prim_drawrectangle",l_SE_prim_drawrectangle);
	lua_register(L,"SE_prim_drawcircle",l_SE_prim_drawcircle);

	//UTILS
	lua_register(L,"SE_utils_powerof2",l_SE_utils_powerof2);
	lua_register(L,"SE_utils_log",l_SE_utils_log);
	lua_register(L,"SE_utils_logvertices",l_SE_utils_logvertices);
	lua_register(L,"SE_utils_logvertices_init",l_SE_utils_logvertices_init);
	lua_register(L,"SE_utils_vertices",l_SE_utils_vertices);

	//TIMER
	lua_register(L,"SE_timer_gettime",l_SE_timer_gettime);
	lua_register(L,"SE_timer_reset",l_SE_timer_reset);
	lua_register(L,"SE_timer_current",l_SE_timer_current);
	lua_register(L,"SE_timer_setframerate",l_SE_timer_setframerate);
	lua_register(L,"SE_timer_waitframerate",l_SE_timer_waitframerate);
	lua_register(L,"SE_timer_start",l_SE_timer_start);
	lua_register(L,"SE_timer_check",l_SE_timer_check);

	//INPUT
	lua_register(L,"SE_input_state_init",l_SE_input_state_init);
	lua_register(L,"SE_input_mapping_init",l_SE_input_mapping_init);
	lua_register(L,"SE_input_joystick_init",l_SE_input_joystick_init);
	lua_register(L,"SE_input_open",l_SE_input_open);
	lua_register(L,"SE_input_enum",l_SE_input_enum);
	lua_register(L,"SE_input_poll",l_SE_input_poll);
	lua_register(L,"SE_input_init",l_SE_input_init);
	lua_register(L,"SE_input_button",l_SE_input_button);
	lua_register(L,"SE_input_close",l_SE_input_close);

	//AUDIO
	lua_register(L,"SE_audio_init",l_SE_audio_init);
	lua_register(L,"SE_audio_close",l_SE_audio_close);
	lua_register(L,"SE_audio_enablesound",l_SE_audio_enablesound);
	lua_register(L,"SE_audio_disablesound",l_SE_audio_disablesound);
	lua_register(L,"SE_audio_enablemusic",l_SE_audio_enablemusic);
	lua_register(L,"SE_audio_disablemusic",l_SE_audio_disablemusic);
	lua_register(L,"SE_audio_loadmusic",l_SE_audio_loadmusic);
	lua_register(L,"SE_audio_playmusic",l_SE_audio_playmusic);
	lua_register(L,"SE_audio_stopmusic",l_SE_audio_stopmusic);
	lua_register(L,"SE_audio_setmusicvolume",l_SE_audio_setmusicvolume);
	lua_register(L,"SE_audio_isplayingmusic",l_SE_audio_isplayingmusic);
	lua_register(L,"SE_audio_loadsound",l_SE_audio_loadsound);
	lua_register(L,"SE_audio_playsound",l_SE_audio_playsound);
	lua_register(L,"SE_audio_setsoundvolume",l_SE_audio_setsoundvolume);



	luaL_dofile(L, pathfile);

	lua_close(L);


}

static int l_SE_screen_fullscreen(lua_State *L)
{
	
	int fs = lua_tonumber(L, 1);

	SE_screen_fullscreen(fs);

	lua_pushnil(L);

	return 0;

}

static int l_SE_screen_init(lua_State *L)
{

	/*int width = luaL_checknumber(L, 1);
	int height = luaL_checknumber(L, 1);
	int bpp = luaL_checknumber(L, 1);*/

	int width = lua_tonumber(L, 1);
	int height = lua_tonumber(L, 2);
	int bpp = lua_tonumber(L, 3);


	int screen = SE_screen_init(width,height,bpp);

	lua_pushnumber(L,screen);


	return 1;

}

static int l_SE_screen_enable2d(lua_State *L)
{

	SE_screen_enable2d();	

	lua_pushnil(L);
		
	return 0;

}

static int l_SE_screen_disable2d(lua_State *L)
{

	SE_screen_disable2d();	

	lua_pushnil(L);
		
	return 0;

}

static int l_SE_screen_clear(lua_State *L)
{

	float r = lua_tonumber(L, 1);
	float g = lua_tonumber(L, 2);
	float b = lua_tonumber(L, 3);
	float a = lua_tonumber(L, 4);

	SE_screen_clear(r,g,b,a);

	lua_pushnil(L);

	return 0;

}

static int l_SE_screen_flip(lua_State *L)
{

	SE_screen_flip();

	lua_pushnil(L);

	return 0;

}

static int l_SE_screen_rotate(lua_State *L)
{

	float rotx = lua_tonumber(L, 1);
	float roty = lua_tonumber(L, 2);
	float rotz = lua_tonumber(L, 3);
	float pointx = lua_tonumber(L, 4);
	float pointy = lua_tonumber(L, 5);
	float pointz = lua_tonumber(L, 6);

	SE_screen_rotate(rotx,roty,rotz,pointx,pointy,pointz);

	lua_pushnil(L);

	return 0;

}

static int l_SE_screen_scale(lua_State *L)
{

	float zoomx = lua_tonumber(L, 1);
	float zoomy = lua_tonumber(L, 2);
	float zoomz = lua_tonumber(L, 3);

	SE_screen_scale(zoomx,zoomy,zoomz);

	lua_pushnil(L);

	return 0;

}

static int l_SE_screen_resettransform(lua_State *L)
{

	SE_screen_resettransform();

	lua_pushnil(L);

	return 0;

}

/*IMAGE*/

static int l_SE_image_load(lua_State *L)
{

	const char *filename = luaL_checkstring(L, 1);
	
	SE_image *temp_image; 

	temp_image = SE_image_load(filename);

	lua_pushlightuserdata(L,(void*)temp_image);

	return 1;
		
}

static int l_SE_image_dimentions(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	lua_pushnumber(L,temp_image->width);
	lua_pushnumber(L,temp_image->height);
	
	return 2;

}

static int l_SE_image_segment_draw_fx(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float xtex = lua_tonumber(L,2);
	float ytex = lua_tonumber(L,3);
	float wtex = lua_tonumber(L,4);
	float htex = lua_tonumber(L,5);

	float posx = lua_tonumber(L,6);
	float posy = lua_tonumber(L,7);
	float posz = lua_tonumber(L,8);

	float width_image = lua_tonumber(L,9);
	float height_image = lua_tonumber(L,10);

	float zoomx = lua_tonumber(L,11);
	float zoomy = lua_tonumber(L,12);
						   
	float rotx = lua_tonumber(L,13);
	float roty = lua_tonumber(L,14);
	float rotz = lua_tonumber(L,15);
						   
	float r = lua_tonumber(L,16);
	float g = lua_tonumber(L,17);
	float b = lua_tonumber(L,18);
	float alpha = lua_tonumber(L,19);

	SE_image_segment_draw_fx(temp_image,xtex,ytex,wtex,htex,posx,posy,posz,width_image,height_image,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_segment_draw_wh(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float xtex = lua_tonumber(L,2);
	float ytex = lua_tonumber(L,3);
	float wtex = lua_tonumber(L,4);
	float htex = lua_tonumber(L,5);

	float posx = lua_tonumber(L,6);
	float posy = lua_tonumber(L,7);
	float posz = lua_tonumber(L,8);

	float width_image = lua_tonumber(L,9);
	float height_image = lua_tonumber(L,10);
	
	SE_image_segment_draw_wh(temp_image,xtex,ytex,wtex,htex,posx,posy,posz,width_image,height_image);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_segment_draw(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float xtex = lua_tonumber(L,2);
	float ytex = lua_tonumber(L,3);
	float wtex = lua_tonumber(L,4);
	float htex = lua_tonumber(L,5);

	float posx = lua_tonumber(L,6);
	float posy = lua_tonumber(L,7);
	float posz = lua_tonumber(L,8);
	
	SE_image_segment_draw(temp_image,xtex,ytex,wtex,htex,posx,posy,posz);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_draw_fx(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);

	float width_image = lua_tonumber(L,5);
	float height_image = lua_tonumber(L,6);

	float zoomx = lua_tonumber(L,7);
	float zoomy = lua_tonumber(L,8);
						   
	float rotx = lua_tonumber(L,9);
	float roty = lua_tonumber(L,10);
	float rotz = lua_tonumber(L,11);
						   
	float r = lua_tonumber(L,12);
	float g = lua_tonumber(L,13);
	float b = lua_tonumber(L,14);
	float alpha = lua_tonumber(L,15);

	SE_image_draw_fx(temp_image,posx,posy,posz,width_image,height_image,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_draw_wh(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);

	float width_image = lua_tonumber(L,5);
	float height_image = lua_tonumber(L,6);	

	SE_image_draw_wh(temp_image,posx,posy,posz,width_image,height_image);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_draw(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);

	SE_image_draw(temp_image,posx,posy,posz);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_image_segment_draw_transf(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	SE_transf *tr; 	

	tr = (SE_transf*)lua_touserdata(L,2);

	float xtex = lua_tonumber(L,3);
	float ytex = lua_tonumber(L,4);
	float wtex = lua_tonumber(L,5);
	float htex = lua_tonumber(L,6);

	SE_image_segment_draw_transf(temp_image,tr,xtex,ytex,wtex,htex);

	lua_pushnil(L);	

	return 0;

}


static int l_SE_image_draw_transf(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	SE_transf *tr; 	

	tr = (SE_transf*)lua_touserdata(L,2);

	SE_image_draw_transf(temp_image,tr);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_image_clean(lua_State *L)
{

	SE_image *temp_image = (SE_image*)lua_touserdata(L,1);

	SE_image_clean(temp_image);

	lua_pushnil(L);	

	return 0;


}

/*ANIMATION*/

static int l_SE_ani_init(lua_State *L)
{

	float width = lua_tonumber(L,1);
	float height = lua_tonumber(L,2);
	int numframes = lua_tonumber(L,3);

	SE_ani *ani; 

	ani = SE_ani_init(width,height,numframes);

	lua_pushlightuserdata(L,(void*)ani);

	return 1;
		
}

static int l_SE_ani_width(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	lua_pushnumber(L,ani->width);
	
	return 1;

}

static int l_SE_ani_height(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	lua_pushnumber(L,ani->height);
	
	return 1;

}


static int l_SE_ani_frame_delay_set(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	int frame_number = lua_tonumber(L,2);
	int delay = lua_tonumber(L,3);

	SE_ani_frame_delay_set(ani,frame_number,delay);
	
	return 0;

}

static int l_SE_ani_addframe_segment(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int frame_number = lua_tonumber(L,3);
	int delay = lua_tonumber(L,4);

	float xtex = lua_tonumber(L,5);
	float ytex = lua_tonumber(L,6);
	float wtex = lua_tonumber(L,7);
	float htex = lua_tonumber(L,8);

	SE_ani_addframe_segment(ani,img,frame_number,delay,xtex,ytex,wtex,htex);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_ani_addframe(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int frame_number = lua_tonumber(L,3);
	int delay = lua_tonumber(L,4);

	SE_ani_addframe(ani,img,frame_number,delay);

	lua_pushnil(L);	

	return 0;


}


static int l_SE_ani_create_from_img(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int numimagex = lua_tonumber(L,3);

	int numimagey = lua_tonumber(L,4);

	int delay = lua_tonumber(L,5);

	SE_ani_create_from_img(ani,img,numimagex,numimagey,delay);

	lua_pushnil(L);	

	return 0;


}

static int l_SE_ani_clean(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_ani_clean(ani);

	lua_pushnil(L);	

	return 0;	

}

/*ANIMATOR*/

static int l_SE_animator_init(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_animator *ator = SE_animator_init(ani);

	lua_pushlightuserdata(L,(void*)ator);

	return 1;
		
}

static int l_SE_animator_status(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);
	
 	int status = SE_animator_status(ator);

	lua_pushnumber(L,status);	

	return 1;

}

static int l_SE_animator_start(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);
	
 	SE_animator_start(ator);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_stop(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);
	
 	SE_animator_stop(ator);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_initend_set(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	int initframe = lua_tonumber(L,2);
	int endframe = lua_tonumber(L,3);
	
	SE_animator_initend_set(ator,initframe,endframe);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_reset(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);
	
 	SE_animator_reset(ator);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_delaypercent(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	float delayperc = lua_tonumber(L,2);
	
	SE_animator_delaypercent(ator,delayperc);

	lua_pushnil(L);	

	return 0;

}


static int l_SE_animator_draw_fx(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	float width = lua_tonumber(L,5);
	float height = lua_tonumber(L,6);
	float zoomx = lua_tonumber(L,7);
	float zoomy = lua_tonumber(L,8);
	float rotx = lua_tonumber(L,9);
	float roty = lua_tonumber(L,10);
	float rotz = lua_tonumber(L,11);
	float r = lua_tonumber(L,12);
	float g = lua_tonumber(L,13);
	float b = lua_tonumber(L,14);
	float alpha = lua_tonumber(L,15);
 
	SE_animator_draw_fx(ator,posx,posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_draw_wh(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	float width = lua_tonumber(L,5);
	float height = lua_tonumber(L,6);	
 
	SE_animator_draw_wh(ator,posx,posy,posz,width,height);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_draw(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);

	SE_animator_draw(ator,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_draw_transf(lua_State *L)
{

	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	SE_transf *tr; 	

	tr = (SE_transf*)lua_touserdata(L,2);

	SE_animator_draw_transf(ator,tr);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_animator_clean(lua_State *L)
{
	
	SE_animator *ator = (SE_animator*)lua_touserdata(L,1);

	SE_animator_clean(ator);

	lua_pushnil(L);	

	return 0;	

}

/*SPRITE*/

/*static int l_SE_sprite_init(lua_State *L)
{

	SE_ani *ani = (SE_ani*)lua_touserdata(L,1);

	SE_sprite *spr = SE_sprite_init(ani);

	lua_pushlightuserdata(L,(void*)spr);

	return 1;
		
}*/

static int l_SE_sprite_init(lua_State *L)
{

	int type = lua_tonumber(L,1);

	SE_sprite *spr = SE_sprite_init(type);
	
	lua_pushlightuserdata(L,(void*)spr);

	return 1;
		
}

static int l_SE_sprite_img_segment_add(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);	

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	float xtex = lua_tonumber(L,3);
	float ytex = lua_tonumber(L,4);
	float wtex = lua_tonumber(L,5);
	float htex = lua_tonumber(L,6);

	SE_sprite_img_segment_add(spr,img,xtex,ytex,wtex,htex);

	lua_pushnil(L);	
	
	return 0;

}


static int l_SE_sprite_img_add(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);	

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	SE_sprite_img_add(spr,img);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_sprite_ani_add(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);	

	SE_ani *ani = (SE_ani*)lua_touserdata(L,2);

	SE_sprite_ani_add(spr,ani);

	lua_pushnil(L);	
	
	return 0;

}


static int l_SE_sprite_width(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	int width = SE_sprite_width(spr);

	lua_pushnumber(L,width);
	
	return 1;

}

static int l_SE_sprite_height(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	int height = SE_sprite_height(spr);

	lua_pushnumber(L,height);
	
	return 1;

}

static int l_SE_sprite_offset_set(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	float offsetx = lua_tonumber(L,2);
	float offsety = lua_tonumber(L,3);
	
	SE_sprite_offset_set(spr,offsetx,offsety);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_sprite_box_init(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	int numboxes = lua_tonumber(L,2);

	SE_sprite_box_init(spr,numboxes);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_sprite_box_set(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	int box_number = lua_tonumber(L,2);

	float offsetx = lua_tonumber(L,3);
	float offsety = lua_tonumber(L,4);
	float width_box = lua_tonumber(L,5);
	float height_box = lua_tonumber(L,6);
	
	SE_sprite_box_set(spr,box_number,offsetx,offsety,width_box,height_box);

	lua_pushnil(L);	
	
	return 0;

}



static int l_SE_sprite_collision_single(lua_State *L)
{

	SE_sprite *spr1 = (SE_sprite*)lua_touserdata(L,1);

	int numbox1 = lua_tonumber(L,2);

	SE_sprite *spr2 = (SE_sprite*)lua_touserdata(L,3);

	int numbox2 = lua_tonumber(L,4);

	float posx1 = lua_tonumber(L,5);
	float posy1 = lua_tonumber(L,6);

	float posx2 = lua_tonumber(L,7);
	float posy2 = lua_tonumber(L,8);
	
	int value = SE_sprite_collision_single(spr1,numbox1,spr2,numbox2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);	
	
	return 1;

}

static int l_SE_sprite_collision_box(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	SE_box *box = (SE_box*)lua_touserdata(L,2);

	float posx_spr = lua_tonumber(L,3);
	float posy_spr = lua_tonumber(L,4);

	float posx_box = lua_tonumber(L,5);
	float posy_box = lua_tonumber(L,6);
	
	int value = SE_sprite_collision_box(spr,box,posx_spr,posy_spr,posx_box,posy_box);

	lua_pushnumber(L,value);	
	
	return 1;

}

static int l_SE_sprite_collision(lua_State *L)
{

	SE_sprite *spr1 = (SE_sprite*)lua_touserdata(L,1);

	SE_sprite *spr2 = (SE_sprite*)lua_touserdata(L,2);

	float posx1 = lua_tonumber(L,3);
	float posy1 = lua_tonumber(L,4);

	float posx2 = lua_tonumber(L,5);
	float posy2 = lua_tonumber(L,6);
	
	int value = SE_sprite_collision(spr1,spr2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);	
	
	return 1;

}

/*static int l_SE_sprite_collision_pf_single(lua_State *L)
{

	SE_sprite *spr1 = (SE_sprite*)lua_touserdata(L,1);

	int frame_number1 = lua_tonumber(L,2);	
	int numbox1 = lua_tonumber(L,3);

	SE_sprite *spr2 = (SE_sprite*)lua_touserdata(L,4);

	int frame_number2 = lua_tonumber(L,5);	
	int numbox2 = lua_tonumber(L,6);	

	float posx1 = lua_tonumber(L,7);
	float posy1 = lua_tonumber(L,8);

	float posx2 = lua_tonumber(L,9);
	float posy2 = lua_tonumber(L,10);
	
	int value = SE_sprite_collision_pf_single(spr1,frame_number1,numbox1,spr2,frame_number2,numbox2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);	
	
	return 1;

}

static int l_SE_sprite_collision_pf_current(lua_State *L)
{

	SE_sprite *spr1 = (SE_sprite*)lua_touserdata(L,1);

	int numbox1 = lua_tonumber(L,2);

	SE_sprite *spr2 = (SE_sprite*)lua_touserdata(L,3);

	int numbox2 = lua_tonumber(L,4);	

	float posx1 = lua_tonumber(L,5);
	float posy1 = lua_tonumber(L,6);

	float posx2 = lua_tonumber(L,7);
	float posy2 = lua_tonumber(L,8);
	
	int value = SE_sprite_collision_pf_current(spr1,numbox1,spr2,numbox2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);	
	
	return 1;

}

static int l_SE_sprite_collision_pf(lua_State *L)
{

	SE_sprite *spr1 = (SE_sprite*)lua_touserdata(L,1);
	SE_sprite *spr2 = (SE_sprite*)lua_touserdata(L,2);
	
	float posx1 = lua_tonumber(L,3);
	float posy1 = lua_tonumber(L,4);

	float posx2 = lua_tonumber(L,5);
	float posy2 = lua_tonumber(L,6);
	
	int value = SE_sprite_collision_pf(spr1,spr2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);	
	
	return 1;

}*/

static int l_SE_sprite_clean(lua_State *L)
{
	
	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	SE_sprite_clean(spr);

	lua_pushnil(L);	

	return 0;	

}

static int l_SE_sprite_draw_fx(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	float width = lua_tonumber(L,5);
	float height = lua_tonumber(L,6);
	float zoomx = lua_tonumber(L,7);
	float zoomy = lua_tonumber(L,8);
	float rotx = lua_tonumber(L,9);
	float roty = lua_tonumber(L,10);
	float rotz = lua_tonumber(L,11);
	float r = lua_tonumber(L,12);
	float g = lua_tonumber(L,13);
	float b = lua_tonumber(L,14);
	float alpha = lua_tonumber(L,15);

	SE_sprite_draw_fx(spr,posx,posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_sprite_draw_wh(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	float width = lua_tonumber(L,5);
	float height = lua_tonumber(L,6);
	

	SE_sprite_draw_wh(spr,posx,posy,posz,width,height);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_sprite_draw(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);

	SE_sprite_draw(spr,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_sprite_draw_transf(lua_State *L)
{

	SE_sprite *spr = (SE_sprite*)lua_touserdata(L,1);

	SE_transf *tr; 	

	tr = (SE_transf*)lua_touserdata(L,2);

	SE_sprite_draw_transf(spr,tr);

	lua_pushnil(L);	

	return 0;

}

/*TILE*/


/*static int l_SE_tile_img_add(lua_State *L)
{

	SE_tile *tl = (SE_tile*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	float xtex = lua_tonumber(L,3);
	float ytex = lua_tonumber(L,4);

	float wtex = lua_tonumber(L,5);
	float htex = lua_tonumber(L,6);

	SE_tile_img_add(tl,img,xtex,ytex,wtex,htex);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_tile_ani_add(lua_State *L)
{

	SE_tile *tl = (SE_tile*)lua_touserdata(L,1);

	SE_ani *ani = (SE_ani*)lua_touserdata(L,2);
	
	SE_tile_ani_add(tl,ani);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_tile_type(lua_State *L)
{

	SE_tile *tl = (SE_tile*)lua_touserdata(L,1);
		
	int value = SE_tile_type(tl);

	lua_pushnumber(L,value);	
	
	return 1;

}

static int l_SE_tile_draw(lua_State *L)
{

	SE_tile *tl = (SE_tile*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	
	SE_tile_draw(tl,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}*/

/*TILESET*/

static int l_SE_tileset_init(lua_State *L)
{

	int numtileset = lua_tonumber(L,1);
	float width_tile = lua_tonumber(L,2);
	float height_tile = lua_tonumber(L,3);

	SE_tileset *ts = SE_tileset_init(numtileset,width_tile,height_tile);

	lua_pushlightuserdata(L,(void*)ts);

	return 1;
		
}

static int l_SE_tileset_img_segment_add(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int num_tile = lua_tonumber(L,3);

	float xtex = lua_tonumber(L,4);
	float ytex = lua_tonumber(L,5);

	SE_tileset_img_segment_add(ts,img,num_tile,xtex,ytex);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_tileset_create_from_img(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int numimagex = lua_tonumber(L,3);

	int numimagey = lua_tonumber(L,4);

	SE_tileset_create_from_img(ts,img,numimagex,numimagey);

	lua_pushnil(L);	

	return 0;

}


static int l_SE_tileset_img_add(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	SE_image *img = (SE_image*)lua_touserdata(L,2);

	int num_tile = lua_tonumber(L,3);

	SE_tileset_img_add(ts,img,num_tile);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_tileset_ani_add(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	SE_ani *ani = (SE_ani*)lua_touserdata(L,2);

	int num_tile = lua_tonumber(L,3);

	SE_tileset_ani_add(ts,ani,num_tile);

	lua_pushnil(L);	

	return 0;

}

/*static int l_SE_tileset_draw(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	int num_tile = lua_tonumber(L,3);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	
	SE_tileset_draw(ts,num_tile,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}*/

static int l_SE_tileset_clean(lua_State *L)
{
	
	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	SE_tileset_clean(ts);

	lua_pushnil(L);	

	return 0;	

}

/*TILEMAP*/

static int l_SE_tilemap_init(lua_State *L)
{

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,1);

	int numtileset = lua_tonumber(L,2);
	float width_tile = lua_tonumber(L,3);
	float height_tile = lua_tonumber(L,4);
	int numtilex = lua_tonumber(L,5);
	int numtiley = lua_tonumber(L,6);


	SE_tilemap *tm = SE_tilemap_init(ts,numtileset,width_tile,height_tile,numtilex,numtiley);

	lua_pushlightuserdata(L,(void*)tm);

	return 1;
		
}

static int l_SE_tilemap_clean(lua_State *L)
{
	
	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	SE_tilemap_clean(tm);

	lua_pushnil(L);	

	return 0;	

}

static int l_SE_tilemap_tileset_set(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	SE_tileset *ts = (SE_tileset*)lua_touserdata(L,2);
	
	SE_tilemap_tileset_set(tm,ts);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_data_load(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	const char *path = luaL_checkstring(L,2);
	
	SE_tilemap_data_load(tm,path);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_maptile_load(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	const char *path = luaL_checkstring(L,2);
	
	SE_tilemap_maptile_load(tm,path);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_maptile_bin_load(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	const char *path = luaL_checkstring(L,2);
	
	SE_tilemap_maptile_bin_load(tm,path);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_mapcoll_load(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	const char *path = luaL_checkstring(L,2);
	
	SE_tilemap_mapcoll_load(tm,path);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_mapcoll_bin_load(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	const char *path = luaL_checkstring(L,2);
	
	SE_tilemap_mapcoll_bin_load(tm,path);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_tilemap_draw(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	float posx = lua_tonumber(L,2);
	float posy = lua_tonumber(L,3);
	float posz = lua_tonumber(L,4);
	
	SE_tilemap_draw(tm,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_tilemap_collision(lua_State *L)
{

	SE_tilemap *tm = (SE_tilemap*)lua_touserdata(L,1);

	float tm_posx = lua_tonumber(L,2);
	float tm_posy = lua_tonumber(L,3);

	SE_box *box = (SE_box*)lua_touserdata(L,4);

	float box_posx = lua_tonumber(L,5);
	float box_posy = lua_tonumber(L,6);
		
	int value = SE_tilemap_collision(tm,tm_posx,tm_posy,box,box_posx,box_posy);

	lua_pushnumber(L,value);
	
	return 1;
		
}


/*BOX*/

static int l_SE_box_init(lua_State *L)
{

	SE_box *box;

	float x = lua_tonumber(L,1);
	float y = lua_tonumber(L,2);
	float w = lua_tonumber(L,3);
	float h = lua_tonumber(L,4);

	box = (SE_box*)lua_newuserdata(L,sizeof(SE_box));

	*box = SE_box_init(x,y,w,h);

	return 1;

}

static int l_SE_box_position_set(lua_State *L)
{

	SE_box *box;
	
	box = (SE_box*)lua_touserdata(L,1);
	float x = lua_tonumber(L,2);
	float y = lua_tonumber(L,3);

	SE_box_position_set(box,x,y);

	return 0;
	
}

static int l_SE_box_dimentions_set(lua_State *L)
{

	SE_box *box;
	
	box = (SE_box*)lua_touserdata(L,1);
	float w = lua_tonumber(L,2);
	float h = lua_tonumber(L,3);

	SE_box_dimentions_set(box,w,h);

	return 0;

}

static int l_SE_box_get(lua_State *L)
{

	SE_box *box;
	
	box = (SE_box*)lua_touserdata(L,1);

	lua_pushnumber(L,box->x);
	lua_pushnumber(L,box->y);
	lua_pushnumber(L,box->w);
	lua_pushnumber(L,box->h);
	
	return 4;

}


/*TRANSFORM*/

static int l_SE_transf_init(lua_State *L)
{

	SE_transf *tr;

	tr = (SE_transf*)lua_newuserdata(L,sizeof(SE_transf));

	*tr = SE_transf_init();

	return 1;

}

static int l_SE_transf_position_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float x = lua_tonumber(L,2);
	float y = lua_tonumber(L,3);
	float z = lua_tonumber(L,4);

	SE_transf_position_set(tr,x,y,z);

	return 0;

}

static int l_SE_transf_dimentions_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float w = lua_tonumber(L,2);
	float h = lua_tonumber(L,3);


	SE_transf_dimentions_set(tr,w,h);

	return 0;



}

static int l_SE_transf_zoom_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float zoomx = lua_tonumber(L,2);
	float zoomy = lua_tonumber(L,3);


	SE_transf_zoom_set(tr,zoomx,zoomy);

	return 0;

}

static int l_SE_transf_rotation_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float rotx = lua_tonumber(L,2);
	float roty = lua_tonumber(L,3);
	float rotz = lua_tonumber(L,4);

	SE_transf_rotation_set(tr,rotx,roty,rotz);

	return 0;




}


static int l_SE_transf_rgb_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float r = lua_tonumber(L,2);
	float g = lua_tonumber(L,3);
	float b = lua_tonumber(L,4);

	SE_transf_rgb_set(tr,r,g,b);

	return 0;




}

static int l_SE_transf_alpha_set(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);
	float alpha = lua_tonumber(L,2);

	SE_transf_alpha_set(tr,alpha);

	return 0;

}

static int l_SE_transf_get(lua_State *L)
{

	SE_transf *tr;
	
	tr = (SE_transf*)lua_touserdata(L,1);

	lua_pushnumber(L,tr->x);
	lua_pushnumber(L,tr->y);
	lua_pushnumber(L,tr->z);
	lua_pushnumber(L,tr->width);
	lua_pushnumber(L,tr->height);
	lua_pushnumber(L,tr->zoomx);
	lua_pushnumber(L,tr->zoomy);
	lua_pushnumber(L,tr->rotx);
	lua_pushnumber(L,tr->roty);
	lua_pushnumber(L,tr->rotz);
	lua_pushnumber(L,tr->r);
	lua_pushnumber(L,tr->g);
	lua_pushnumber(L,tr->b);
	lua_pushnumber(L,tr->alpha);
	
	return 14;

}

/*COLLISION*/

static int l_SE_coll_check_position(lua_State *L)
{

	SE_box *box1 = (SE_box*)lua_touserdata(L,1);
	SE_box *box2 = (SE_box*)lua_touserdata(L,2);

	float posx1 = lua_tonumber(L,3);
	float posy1 = lua_tonumber(L,4);
	float posx2 = lua_tonumber(L,5);
	float posy2 = lua_tonumber(L,6);

	int value = SE_coll_check_position(box1,box2,posx1,posy1,posx2,posy2);

	lua_pushnumber(L,value);
	
	return 1;

}

static int l_SE_coll_check(lua_State *L)
{

	SE_box *box1 = (SE_box*)lua_touserdata(L,1);
	SE_box *box2 = (SE_box*)lua_touserdata(L,2);

	int value = SE_coll_check(box1,box2);

	lua_pushnumber(L,value);
	
	return 1;

}

/*FONT*/

static int l_SE_font_create(lua_State *L)
{

	SE_image *img = (SE_image*)lua_touserdata(L,1);
	int columns = lua_tonumber(L,2);
	int rows = lua_tonumber(L,3);
	int fontw = lua_tonumber(L,4);
	int fonth = lua_tonumber(L,5);

	SE_font *font = SE_font_create(img,columns,rows,fontw,fonth);

	lua_pushlightuserdata(L,(void*)font);

	return 1;

}

static int l_SE_font_space_set(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = lua_tonumber(L,2);

	SE_font_space_set(fnt,value);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_font_space(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = SE_font_space(fnt);

	lua_pushnumber(L,value);
	
	return 1;

}

static int l_SE_font_letterspacing_set(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = lua_tonumber(L,2);

	SE_font_letterspacing_set(fnt,value);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_font_letterspacing(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = SE_font_letterspacing(fnt);

	lua_pushnumber(L,value);
	
	return 1;

}

static int l_SE_font_lineheight_set(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = lua_tonumber(L,2);

	SE_font_lineheight_set(fnt,value);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_font_lineheight(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	int value = SE_font_lineheight(fnt);

	lua_pushnumber(L,value);
	
	return 1;

}

static int l_SE_font_draw_fx(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	const char *text = luaL_checkstring(L,2);

	float posx = lua_tonumber(L,3);
	float posy = lua_tonumber(L,4);
	float posz = lua_tonumber(L,5);
	float width = lua_tonumber(L,6);
	float height = lua_tonumber(L,7);
	float zoomx = lua_tonumber(L,8);
	float zoomy = lua_tonumber(L,9);
	float rotx = lua_tonumber(L,10);
	float roty = lua_tonumber(L,11);
	float rotz = lua_tonumber(L,12);
	float r = lua_tonumber(L,13);
	float g = lua_tonumber(L,14);
	float b = lua_tonumber(L,15);
	float alpha = lua_tonumber(L,16);

	SE_font_draw_fx(fnt,text,posx,posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_font_draw(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	const char *text = luaL_checkstring(L,2);

	float posx = lua_tonumber(L,3);
	float posy = lua_tonumber(L,4);
	float posz = lua_tonumber(L,5);

	SE_font_draw(fnt,text,posx,posy,posz);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_font_draw_transf(lua_State *L)
{

	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	SE_transf *tr; 	

	tr = (SE_transf*)lua_touserdata(L,2);

	const char *text = luaL_checkstring(L,3);

	SE_font_draw_transf(fnt,tr,text);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_font_clean(lua_State *L)
{
	
	SE_font *fnt = (SE_font*)lua_touserdata(L,1);

	SE_font_clean(fnt);

	lua_pushnil(L);	

	return 0;	

}

/*PRIMITIVES*/

static int l_SE_prim_drawpoint(lua_State *L)
{

	float x = lua_tonumber(L,1);
	float y = lua_tonumber(L,2);
	float z = lua_tonumber(L,3);
	float red = lua_tonumber(L,4);
	float green = lua_tonumber(L,5);
	float blue = lua_tonumber(L,6);
	float alpha = lua_tonumber(L,7);

	SE_prim_drawpoint(x,y,z,red,green,blue,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_prim_drawline(lua_State *L)
{

	float x1 = lua_tonumber(L,1);
	float y1 = lua_tonumber(L,2);
	float x2 = lua_tonumber(L,3);
	float y2 = lua_tonumber(L,4);
	float z = lua_tonumber(L,5);
	float red = lua_tonumber(L,6);
	float green = lua_tonumber(L,7);
	float blue = lua_tonumber(L,8);
	float alpha = lua_tonumber(L,9);

	SE_prim_drawline(x1,y1,x2,y2,z,red,green,blue,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_prim_drawrectangle(lua_State *L)
{

	float x = lua_tonumber(L,1);
	float y = lua_tonumber(L,2);	
	float z = lua_tonumber(L,3);
	float width = lua_tonumber(L,4);
	float height = lua_tonumber(L,5);
	int fill = lua_tonumber(L,6);
	float red = lua_tonumber(L,7);
	float green = lua_tonumber(L,8);
	float blue = lua_tonumber(L,9);
	float alpha = lua_tonumber(L,10);

	SE_prim_drawrectangle(x,y,z,width,height,fill,red,green,blue,alpha);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_prim_drawcircle(lua_State *L)
{

	float x = lua_tonumber(L,1);
	float y = lua_tonumber(L,2);	
	float z = lua_tonumber(L,3);
	float radius = lua_tonumber(L,4);
	float sections = lua_tonumber(L,5);
	int fill = lua_tonumber(L,6);
	float red = lua_tonumber(L,7);
	float green = lua_tonumber(L,8);
	float blue = lua_tonumber(L,9);
	float alpha = lua_tonumber(L,10);

	SE_prim_drawcircle(x,y,z,radius,sections,fill,red,green,blue,alpha);

	lua_pushnil(L);	

	return 0;

}

/*UTILS*/

static int l_SE_utils_powerof2(lua_State *L)
{

	int number = lua_tonumber(L,1);

	int value = SE_utils_powerof2(number); 

	lua_pushnumber(L,value);
	
	return 1;

}

static int l_SE_utils_log(lua_State *L)
{

	const char *message = luaL_checkstring(L,1);	

	SE_utils_log(message);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_utils_logvertices(lua_State *L)
{

	int verts = lua_tonumber(L,1);

	SE_utils_logvertices(verts);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_utils_logvertices_init(lua_State *L)
{

	SE_utils_logvertices_init();

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_utils_vertices(lua_State *L)
{

	int value = SE_utils_vertices();

	lua_pushnumber(L,value);
	
	return 1;

}

/*TIMER*/

static int l_SE_timer_gettime(lua_State *L)
{

	int ttms = (int)SE_timer_gettime();

	lua_pushnumber(L,ttms);

	return 1;

}

static int l_SE_timer_reset(lua_State *L)
{

	SE_timer_reset();

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_timer_current(lua_State *L)
{

	int ttms = (int)SE_timer_current();

	lua_pushnumber(L,ttms);

	return 1;

}

static int l_SE_timer_setframerate(lua_State *L)
{

	int framespersecond = lua_tonumber(L,1);

	SE_timer_setframerate(framespersecond);

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_timer_waitframerate(lua_State *L)
{

	SE_timer_waitframerate();

	lua_pushnil(L);	
	
	return 0;

}

static int l_SE_timer_start(lua_State *L)
{

	int time_end = lua_tonumber(L,1);

	SE_timer *timer = SE_timer_start(time_end);

	lua_pushlightuserdata(L,(void*)timer);

	return 1;

}

static int l_SE_timer_check(lua_State *L)
{

	SE_timer *timer = (SE_timer*)lua_touserdata(L,1);

	int value = SE_timer_check(timer);

	lua_pushnumber(L,value);

	return 1;

}

/*INPUT*/

static int l_SE_input_state_init(lua_State *L)
{

	SE_input_state *state;

	lua_pushlightuserdata(L,(void*)state);

	return 1;

}

static int l_SE_input_mapping_init(lua_State *L)
{

	SE_input_mapping *map;

	lua_pushlightuserdata(L,(void*)map);

	return 1;

}

static int l_SE_input_joystick_init(lua_State *L)
{

	SE_input_joystick *joy;

	lua_pushlightuserdata(L,(void*)joy);

	return 1;

}

static int l_SE_input_open(lua_State *L)
{

	int joyid = lua_tonumber(L,1);

	SE_input_joystick *joy = SE_input_open(joyid);

	lua_pushlightuserdata(L,(void*)joy);

	return 1;

}

static int l_SE_input_enum(lua_State *L)
{

	int value = SE_input_enum();

	lua_pushnumber(L,value);

	return 1;

}

static int l_SE_input_poll(lua_State *L)
{

	SE_input_joystick *joy = (SE_input_joystick*)lua_touserdata(L,1);

	SE_input_state *state = SE_input_poll(&joy);

	lua_pushlightuserdata(L,(void*)state);

	return 1;

}



static int l_SE_input_init(lua_State *L)
{

	int value = SE_input_init();

	lua_pushnumber(L,value);

	return 1;

}

static int l_SE_input_button(lua_State *L)
{

	SE_input_state *state = (SE_input_state*)lua_touserdata(L,1);
	const char *button = luaL_checkstring(L,2);

	int value = 0;

		if(strcmp(button,"JOY_UP") == 0)
		{
			if(state->buttons & JOY_UP)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_DOWN") == 0)
		{
			if(state->buttons & JOY_DOWN)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_LEFT") == 0)
		{
			if(state->buttons & JOY_LEFT)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_RIGHT") == 0)
		{
			if(state->buttons & JOY_RIGHT)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON0") == 0)
		{
			if(state->buttons & JOY_BUTTON0)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON1") == 0)
		{
			if(state->buttons & JOY_BUTTON1)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON2") == 0)
		{
			if(state->buttons & JOY_BUTTON2)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON3") == 0)
		{
			if(state->buttons & JOY_BUTTON3)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON4") == 0)
		{
			if(state->buttons & JOY_BUTTON4)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON5") == 0)
		{
			if(state->buttons & JOY_BUTTON5)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON6") == 0)
		{
			if(state->buttons & JOY_BUTTON6)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON7") == 0)
		{
			if(state->buttons & JOY_BUTTON7)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON8") == 0)
		{
			if(state->buttons & JOY_BUTTON8)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"JOY_BUTTON9") == 0)
		{
			if(state->buttons & JOY_BUTTON9)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"SE_QUIT") == 0)
		{
			if(state->buttons & SE_QUIT)
			{
				value = 1;
			}else{
				value = 0;
			}
		}

		if(strcmp(button,"SE_FULLSCREEN") == 0)
		{
			if(state->buttons & SE_FULLSCREEN)
			{
				value = 1;
			}else{
				value = 0;
			}
		} 	
	
	
	//printf("%s",strcmp(button,"quit"));

	lua_pushnumber(L,value);

	return 1;

}

static int l_SE_input_close(lua_State *L)
{

	int value = SE_input_close();

	lua_pushnumber(L,value);

	return 1;

}

/*AUDIO*/

static int l_SE_audio_init(lua_State *L)
{

	int rate = lua_tonumber(L,1);
	int bits = lua_tonumber(L,2);
	int stereo = lua_tonumber(L,3);
	
	SE_audio_init(rate,bits,stereo);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_close(lua_State *L)
{

	SE_audio_close();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_enablesound(lua_State *L)
{

	SE_audio_enablesound();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_disablesound(lua_State *L)
{

	SE_audio_disablesound();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_enablemusic(lua_State *L)
{

	SE_audio_enablemusic();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_disablemusic(lua_State *L)
{

	SE_audio_disablemusic();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_loadmusic(lua_State *L)
{

	const char *filename = luaL_checkstring(L,1);

	SE_music *music = SE_audio_loadmusic(filename);

	lua_pushlightuserdata(L,(void*)music);

	return 1;

}

static int l_SE_audio_playmusic(lua_State *L)
{

	SE_music *musicid = (SE_music*)lua_touserdata(L,1);	

	SE_audio_playmusic(musicid);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_stopmusic(lua_State *L)
{

	SE_audio_stopmusic();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_setmusicvolume(lua_State *L)
{

	int volume = lua_tonumber(L,1);

	SE_audio_setmusicvolume(volume);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_isplayingmusic(lua_State *L)
{

	SE_audio_isplayingmusic();

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_loadsound(lua_State *L)
{
	
	const char *filename = luaL_checkstring(L,1);

	SE_sound *sound = SE_audio_loadsound(filename);

	lua_pushlightuserdata(L,(void*)sound);

	return 1;

}

static int l_SE_audio_playsound(lua_State *L)
{

	SE_sound *soundid = (SE_sound*)lua_touserdata(L,1);	

	SE_audio_playsound(soundid);

	lua_pushnil(L);	

	return 0;

}

static int l_SE_audio_setsoundvolume(lua_State *L)
{

	int volume = lua_tonumber(L,1);

	SE_audio_setsoundvolume(volume);

	lua_pushnil(L);	

	return 0;

}

