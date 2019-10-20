#include <stdio.h>
#include <stdlib.h>
#include "super.h"
#include "ball.h"
#include "player.h"
#include "formation.h"
#include "team.h"
#include "field.h"

//las medidas de todo estan en cm

//inicializacion 
JF_ball *pelota;

JF_field *cancha;

JF_team *equipos[2];


void inicializar_juego()
{

	pelota = JF_ball_init(22,22,0,0,0);

	cancha = JF_field_init(9000,12000);

	//inicializar equipo 1
	equipos[0] = JF_team_init("equipo 1");

//void JF_player_edit(JF_player *pl,char *name,int position,int number,int ini_x,int ini_y,int box_w,int box_y,int height,int status);

	JF_player_edit(&equipos[0]->tplayers[0],"jugador 1",0,1,10,10,JF_form[0][0].posx,JF_form[0][0].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[1],"jugador 2",1,2,10,10,JF_form[0][1].posx,JF_form[0][1].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[2],"jugador 3",2,3,10,10,JF_form[0][2].posx,JF_form[0][2].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[3],"jugador 4",3,4,10,10,JF_form[0][3].posx,JF_form[0][3].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[4],"jugador 5",4,5,10,10,JF_form[0][4].posx,JF_form[0][4].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[5],"jugador 6",5,6,10,10,JF_form[0][5].posx,JF_form[0][5].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[6],"jugador 7",6,7,10,10,JF_form[0][6].posx,JF_form[0][6].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[7],"jugador 8",7,8,10,10,JF_form[0][7].posx,JF_form[0][7].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[8],"jugador 9",8,9,10,10,JF_form[0][8].posx,JF_form[0][8].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[9],"jugador 10",9,10,10,10,JF_form[0][9].posx,JF_form[0][9].posy,200,0);
	JF_player_edit(&equipos[0]->tplayers[10],"jugador 11",10,11,10,10,JF_form[0][10].posx,JF_form[0][10].posy,200,0);

	//inicializar equipo 2
	equipos[1] = JF_team_init("equipo 2");

	JF_player_edit(&equipos[1]->tplayers[0],"jugador 1",0,1,10,10,JF_form[0][0].posx,JF_form[0][0].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[1],"jugador 2",1,2,10,10,JF_form[0][1].posx,JF_form[0][1].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[2],"jugador 3",2,3,10,10,JF_form[0][2].posx,JF_form[0][2].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[3],"jugador 4",3,4,10,10,JF_form[0][3].posx,JF_form[0][3].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[4],"jugador 5",4,5,10,10,JF_form[0][4].posx,JF_form[0][4].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[5],"jugador 6",5,6,10,10,JF_form[0][5].posx,JF_form[0][5].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[6],"jugador 7",6,7,10,10,JF_form[0][6].posx,JF_form[0][6].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[7],"jugador 8",7,8,10,10,JF_form[0][7].posx,JF_form[0][7].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[8],"jugador 9",8,9,10,10,JF_form[0][8].posx,JF_form[0][8].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[9],"jugador 10",9,10,10,10,JF_form[0][9].posx,JF_form[0][9].posy,200,0);
	JF_player_edit(&equipos[1]->tplayers[10],"jugador 11",10,11,10,10,JF_form[0][10].posx,JF_form[0][10].posy,200,0);












}






