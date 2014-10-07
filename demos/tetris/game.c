#include "game.h"


int quit;

SDL_Event event;

Uint32 ini_milisegundos, fin_milisegundos;


void draw_bg()
{

	



}

void draw_scene(board *b)
{
	
	switch(b->status)
	{
		case INIT:
					
			piece_set_current(b,rand()%7);
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
		
			while( SDL_PollEvent( &event ) )
			{
				switch( event.type )
				{
		            /* Look for a keypress */
					case SDL_KEYDOWN:
	
	                /* Check the SDLKey values and move change the coords */
						switch( event.key.keysym.sym )
						{
							case SDLK_LEFT:
								b->piece_column--;
								if((check_collision_piece(b)||check_collision_bottom(b)) == 1)
								{
									b->piece_column++;
								}
								break;
							case SDLK_RIGHT:
								b->piece_column++;
								if((check_collision_piece(b)||check_collision_bottom(b)) == 1)
								{
									b->piece_column--;
								}
								break;
							case SDLK_DOWN:
								b->piece_row++;
								b->cycles = 0;
								break;
							case SDLK_z:
								b->current_rotation++;
								if(b->current_rotation > 3)b->current_rotation = 0;
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
			}

			if(check_collision_lateral(b) == 1)
			{
				b->piece_column++;
			}

			if(check_collision_lateral(b) == 2)
			{
				b->piece_column--;
			}
		
			if(check_collision_bottom(b) == 1)
			{
				b->piece_row--;
				insert_piece(b);
				board_set_status(b,STOPPED);
			}
			
			
			break;
	
			
		case STOPPED:
		
			b->cycles = 0;
			b->alpha = 1;
			b->pos_fill = 0; 
			detect_fill_line(b);
			if(b->pos_fill > 0)
			{
				board_set_status(b,MARK_LINE);	
			}else{
				board_set_status(b,INIT);
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
				board_set_status(b,STOPPED);

			}else{						
				b->cycles++; 	
			}
			break;
			
		default:
			
			break;
	
		
	}		

	draw_board(b);
	draw_piece(b);
	


		
	


}

void ResetTimeBase() {

	ini_milisegundos=SDL_GetTicks();
}


int CurrentTime() {

	fin_milisegundos=SDL_GetTicks();
	return fin_milisegundos-ini_milisegundos;
}





