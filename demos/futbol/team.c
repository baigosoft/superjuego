


team *team_init()
{

	team *te;
	te = (team*)malloc(sizeof(team));
	te->team_players = (player**)malloc(11*sizeof(player*));
	int i;
	for(i=0;i<11;i++)
	{

		te->team_players[i] = player_init();

	}
	
	return te;

}

void team_player_edit(team *te,int order_number,int player_number,int player_ini_x,int player_ini_y,int player_area_width,int player_area_height,int player_height)
{

	player_edit(te->team_players[order_number],player_number,player_ini_x,player_ini_y,player_area_width,player_area_height,player_height);	

}

void team_player_x(team *te,int order_number,int pos_field_x)
{

	player_x(te->team_players[order_number],pos_field_x);

}

void team_player_y(team *te,int order_number,int pos_field_y)
{

	player_y(te->team_players[order_number],pos_field_y);

}

void team_clean(team* te)
{

	int i;
	for(i=0;i<11;i++)
	{

		free(te->team_players[i];

	}
	free(te->team_players);
	free(te);

}
