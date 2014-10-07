#include "player.h"


player *player_init()
{

	player *pl;
	pl = (player*)malloc(sizeof(player));
	pl->player_number = 0;
	pl->player_ini_x = 0;
	pl->player_ini_y = 0;
	pl->player_area_width = 0;
	pl->player_area_height = 0;
	pl->player_height = 0;
	pl->player_status = 0;

	return pl;	

}

void player_edit(player *pl,int player_number,int player_ini_x,int player_ini_y,int player_area_width,int player_area_height,int player_height)
{	

	pl->player_number = player_number;
	pl->player_ini_x = player_ini_x;
	pl->player_ini_y = player_ini_y;
	pl->player_x = player_ini_x;
	pl->player_y = player_ini_y;
	pl->player_area_width = player_area_width;
	pl->player_area_height = player_area_height;
	pl->player_height = player_height;
	pl->player_status = 0;

}

void player_x(player *pl,int pos_field_x)
{

	pl->player_x = pos_field_x;

}

void player_y(player *pl,int pos_field_y)
{

	pl->player_y = pos_field_y;

}

void player_status(player *pl,int status)
{

	pl->player_status = status;

}

void player_clean(player *pl)
{

	free(pl);

}

