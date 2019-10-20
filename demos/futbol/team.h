#ifndef TEAM_H_
#define TEAM_H_

#include "player.h"

#define NUMPLAYERS 11//num of players per team

typedef struct
{

	char t_name[100];/*team's name*/
	JF_player *t_players;/*array of players*/
			

}JF_team;

JF_team *JF_team_init(const char *name);

void JF_team_edit(JF_team *te,const char *name);

void JF_team_clean(JF_team* te);












#endif
