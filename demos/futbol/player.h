#ifndef PLAYER_H_
#define PLAYER_H_


typedef struct
{

	int player_number;
	int player_ini_x,int player_ini_y;
	int player_x,player_y;
	int player_area_width,player_area_height;
	int player_height;	
	int player_status;


}player;


player *player_init();
void player_edit(player *pl,int player_number,int player_ini_x,int player_ini_y,int player_area_width,int player_area_height,int player_height);
void player_x(player *pl,int pos_field_x);
void player_y(player *pl,int pos_field_y);
void player_status(player *pl,int status);
void player_clean(player *pl);













#endif
