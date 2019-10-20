#include "player.h"


JF_player *JF_player_init()
{

	player *pl;
	pl = (player*)malloc(sizeof(player));
	pl->p_pos = 0;
	pl->p_num = 0;
	pl->p_ini_x = 0;
	pl->p_ini_y = 0;
	pl->p_box_w = 0;
	pl->p_box_h = 0;
	pl->p_height = 0;
	pl->p_status = 0;

	return pl;	

}


void JF_player_edit(JF_player *pl,int position,int number,int ini_x,int ini_y,int box_w,int box_y,int height,int status)
{

	pl->p_pos = position;
	pl->p_num = number;
	pl->p_ini_x = ini_x;
	pl->p_ini_y = ini_y;
	pl->p_box_w = box_w;
	pl->p_box_h = box_y;
	pl->p_height = height;
	pl->p_status = status;

}


void JF_player_status(JF_player *pl,int status)
{

	pl->player_status = status;

}

void JF_player_clean(JF_player *pl)
{

	free(pl);

}

