#include "game.h"


int quit;

SE_input_state *state;
SE_input_joystick *joystick;

//SDL_Event event;

Uint32 ini_milisegundos, fin_milisegundos;

int joy_cycles = 0;


void draw_bg()
{

	SE_image_segment_draw(images,0,16,186,345,227,52,0);/*tablero*/
	SE_image_segment_draw(images,201,314,108,34,428,210,0);/*logo tretris*/		

}

void draw_nextpiece_bg(board *b)
{

	SE_image_segment_draw(images,200,0,105,156,430,50,0);
	draw_next_piece(b,435,110,0);


}



void draw_score(board *b)
{

	char sscore[100];
	sprintf(sscore,"%d",b->score);
	SE_font_draw_fx(fntscore,sscore,350,424,0,32,32,1,1,0,0,0,1,1,1,1);

}


void draw_score_bg()
{

	SE_image_segment_draw(images,305,0,189,42,225,420,0);

}

void draw_gameover(float x,float y,float z)
{

	SE_image_segment_draw(images,0,440,180,28,x,y,z);

}

void draw_scene(board *b)
{
	
	int countlines = 0;

	switch(b->status)
	{
		case INIT:
					
			piece_set_current(b);
			piece_set_rotation(b,0);
			piece_set_position(b,0,0);
			board_set_status(b,READY);
			b->cycles = 0;	
			break;

		case START:
			
			b->inserted = 0;		
			piece_set_current(b);
			piece_set_rotation(b,0);
			piece_set_position(b,0,0);
			board_set_status(b,READY);
			b->cycles = 0;	
			break;
	
	
		case READY:
	
			if(b->cycles == 50)
			{
				b->piece_row++;
				b->cycles = 0;
			}else{
				b->cycles++;
			}

			if(joy_cycles == 5)
			{
				joy_cycles = 0;
				if(state=SE_input_poll(&joystick))
				{
        
					if(state->buttons & JOY_DOWN){

						b->piece_row++;
						b->cycles = 0;

					}else if(state->buttons & JOY_LEFT){
	
						b->piece_column--;
						if(check_collision_piece(b) == 1)
						{
							b->piece_column++;
						}								
	
					}else if(state->buttons & JOY_RIGHT){

						b->piece_column++;
						if(check_collision_piece(b) == 1)
						{
							b->piece_column--;
						}													

					}else if(state->buttons & JOY_BUTTON0){

						b->current_rotation++;

						if(b->current_rotation > 3)
						{	
							b->current_rotation = 0;
						}

						if(check_collision_piece(b)== 1)
						{
							b->current_rotation--;

							if(b->current_rotation < 0)
							{
								b->current_rotation = 0;
							}

						}

					}	
		
					if(state->buttons & SE_QUIT) 
					{
						quit=1;
					}

				}
			}else{
				joy_cycles++;
			}	

			/*while( SDL_PollEvent( &event ) )
			{
				switch( event.type )
				{

					case SDL_KEYDOWN:
	
						switch( event.key.keysym.sym )
						{
							case SDLK_LEFT:
								b->piece_column--;
								
								break;
							case SDLK_RIGHT:
								b->piece_column++;
								
								break;
							case SDLK_DOWN:
								b->piece_row++;
								b->cycles = 0;
								break;
							case SDLK_z:
								b->current_rotation++;
								if(b->current_rotation > 3)b->current_rotation = 0;
								if((check_collision_piece(b)||check_collision_bottom(b)) == 1)
								{
									b->current_rotation--;
									if(b->current_rotation < 0)b->current_rotation = 0;
								}

								break;
							default:
								break;
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
            
					default:                
						break;			
				}
			}*/

			

			
		
			if(check_collision_piece(b) == 1)
			{
				b->piece_row--;
				insert_piece(b);
				b->inserted = 1;

				if(detect_gameover(b) > 0)
				{
					board_set_status(b,GAME_OVER);
				}else{
					board_set_status(b,STOP);
				}

			}
			
			
			
			break;
	
			
		case STOP:
		
			b->cycles = 0;
			b->alpha = 1;
			b->pos_fill = 0; 
			detect_fill_line(b);
			if(b->pos_fill > 0)
			{
				board_set_status(b,MARK_LINE);
			}else{
				

				board_set_status(b,START);

			}
			


			break;


		case MARK_LINE:


			if(b->cycles == 10)
			{
				b->cycles = 0;
				board_set_status(b,MOVE_LINES);	

			}else{
				b->cycles++; 
			}
			break;

		case MOVE_LINES:
		

			if(b->cycles == 16)
			{
				b->cycles = 0;
				b->y_counter = 0;
				delete_line(b,b->pos_fill); 
				board_set_status(b,STOP);


			}else{						
				b->cycles++; 	
			}
			break;

		case GAME_OVER:


	
			break;
			
		default:
			
			break;
	
		
	}		

	draw_bg();
	draw_board(b);
	if(b->inserted == 0)
	{
		draw_current_piece(b);
	}
	draw_nextpiece_bg(b);
	draw_score_bg();
	draw_score(b);	
	if(b->status == GAME_OVER)
	{
		draw_gameover(228,205,0);
	}	


		

}

void ResetTimeBase() {

	ini_milisegundos=SDL_GetTicks();
}


int CurrentTime() {

	fin_milisegundos=SDL_GetTicks();
	return fin_milisegundos-ini_milisegundos;
}





