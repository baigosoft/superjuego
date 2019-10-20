#include "team.h"


JF_team *JF_team_init(const char *name)
{

	JF_team *te;
	te->t_name = name;
	te->t_players = (JF_player*)malloc(NUMPLAYERS*sizeof(JF_player));
	int i;
	for(i=0;i<NUMPLAYERS;i++)
	{

		te->t_players[i] = JF_player_init();

	}
	
	return te;

}




void JF_team_edit(JF_team *te,const char *name)
{

	te->t_name = name;

}

void JF_team_clean(JF_team* te)
{
	
	free(te->t_players);
	free(te);

}
