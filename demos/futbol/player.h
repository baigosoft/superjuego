#ifndef PLAYER_H_
#define PLAYER_H_


typedef struct
{

	char name[150];
	int p_pos;/*player team's position.0=gk,1=cd,2=cd,3=ld,4=rd,5=cm,6=cm,7=lm,8=rm,9=la,10=ra*/
	int p_num;/*player team's number*/
	int p_ini_x,int p_ini_y;/*player initial position in field*/
	int p_x,p_y;/*current position in field*/
	int p_box_width,p_box_height;/*player's box of motion in field*/
	int player_height;/*player's height*/	
	int player_status;/*player's current status */


}JF_player;


JF_player *JF_player_init();
void JF_player_edit(JF_player *pl,char *name,int position,int number,int ini_x,int ini_y,int box_w,int box_y,int height,int status);
void JF_player_status(JF_player *pl,int status);
void JF_player_clean(JF_player *pl);













#endif
