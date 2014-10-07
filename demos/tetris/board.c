#include "board.h"



int calc_pos(int x,int y,int columns)
{	

	int t = (y*columns) + x;
	return t;

}



board *init_board(int columns,int rows,int tile_width,int tile_height)
{

	int pieces_total = columns * rows;

	board *b;
	b = (board*)malloc(sizeof(board));
	b->x = 0;
	b->y = 0;
	b->z = 0;
	b->columns = columns;
	b->rows = rows;
	b->tile_width = tile_width;
	b->tile_height = tile_height;
	b->array_board = (int*)malloc(pieces_total * sizeof(int));
	
	int i;
	for(i=0;i<pieces_total;i++)
	{
		b->array_board[i] = 0;
	}	

	b->current_piece = 0;
	b->current_rotation = 0;
	b->piece_column = 0;
	b->piece_row = 0;
	b->pos_fill = 0;
	b->score = 0;
	b->status = 1;
	b->cycles = 0;
	b->colour = 1;
	b->alpha = 1;
	b->y_counter = 0;
	
	return b;

}

void board_set_position(board *b,float posx,float posy,float posz)
{

	b->x = posx;
	b->y = posy;
	b->z = posz;

}


void piece_set_current(board *b,int current_piece)
{

	b->current_piece = current_piece;

}

void piece_set_rotation(board *b,int current_rotation)
{

	b->current_rotation = current_rotation;

}

void piece_set_position(board *b,int piece_column,int piece_row)
{

	b->piece_column = piece_column;
	b->piece_row = piece_row;

}

void board_set_status(board *b,int status)
{

	b->status = status;

}

int check_collision_lateral(board *b)
{

	int i,j,k,l;

	int piece_number = b->current_piece;
	int rotation = b->current_rotation;

	int column_board = b->piece_column;
	int row_board = b->piece_row;

	int x_piece = column_board;
	int y_piece = row_board;

	int piece_pos = 0;
	int piece_value = 0;

	int board_pos = 0;
	int board_value = 0;

	int columns = b->columns;
	int rows = b->rows;

	int width = b->tile_width;
	int height = b->tile_height;

	int cont = 0;

	/*si la pieza supera las paredes*/		
	for(j=0;j<5;j++)
	{		
		for(i=0;i<5;i++)
		{
			piece_pos = calc_pos(i,j,5);
			piece_value = pieces[piece_number][rotation][piece_pos];

			/*la pieza sobrepasa costado izquierdo*/
			if((piece_value > 0) && (x_piece < 0 ))
			{
				return 1;
			}

			/*la pieza sobrepasa costado derecho*/
			if((piece_value > 0) && (x_piece >= columns))
			{
				return 2;
			}			
			
			x_piece++; 
		}

		y_piece++;
		x_piece = column_board; 

	}
	return 0;
				
	
}

int check_collision_bottom(board *b)
{

	int i,j,k,l;

	int piece_number = b->current_piece;
	int rotation = b->current_rotation;

	int column_board = b->piece_column;
	int row_board = b->piece_row;

	int x_piece = column_board;
	int y_piece = row_board;

	int piece_pos = 0;
	int piece_value = 0;

	int board_pos = 0;
	int board_value = 0;

	int columns = b->columns;
	int rows = b->rows;

	int width = b->tile_width;
	int height = b->tile_height;

	int cont = 0;

	/*si la pieza supera las paredes*/		
	for(j=0;j<5;j++)
	{		
		for(i=0;i<5;i++)
		{
			piece_pos = calc_pos(i,j,5);
			piece_value = pieces[piece_number][rotation][piece_pos];
			
			/*la pieza sobrepasa el final*/
			if((piece_value > 0) && (y_piece >= (rows)))
			{
				return 1;
			}
				
			/*la pieza se solapa con las piezas insertadas en el tablero*/
			for(l=0;l < rows;l++)
			{
				for(k=0;k<columns;k++)
				{
					if((x_piece == k) && (y_piece == l))
					{
						board_pos = calc_pos(k,l,columns);
						board_value = b->array_board[board_pos];
						if((piece_value > 0) && (board_value > 0))
						{
							return 1;
						}
					}		
				}
			}

		
			x_piece++; 
		}

		y_piece++;
		x_piece = column_board; 

	}
	return 0;
				
}

int check_collision_piece(board *b)
{

	int i,j,k,l;

	int piece_number = b->current_piece;
	int rotation = b->current_rotation;

	int column_board = b->piece_column;
	int row_board = b->piece_row;

	int x_piece = column_board;
	int y_piece = row_board;

	int piece_pos = 0;
	int piece_value = 0;

	int board_pos = 0;
	int board_value = 0;

	int columns = b->columns;
	int rows = b->rows;

	int width = b->tile_width;
	int height = b->tile_height;

	int cont = 0;

	/*si la pieza supera las paredes*/		
	for(j=0;j<5;j++)
	{		
		for(i=0;i<5;i++)
		{
			piece_pos = calc_pos(i,j,5);
			piece_value = pieces[piece_number][rotation][piece_pos];
			
			/*la pieza se solapa con las piezas insertadas en el tablero*/
			for(l=0;l < rows;l++)
			{
				for(k=0;k<columns;k++)
				{
					if((x_piece == k) && (y_piece == l))
					{
						board_pos = calc_pos(k,l,columns);
						board_value = b->array_board[board_pos];
						if((piece_value > 0) && (board_value > 0))
						{
							return 1;
						}
					}		
				}
			}
			
			x_piece++; 
		}

		y_piece++;
		x_piece = column_board; 

	}
	return 0;
				




}

void insert_piece(board *b)
{
	
	int i,j;
	int ini_col = b->piece_column;
	int ini_row = b->piece_row;
	
	int end_col = b->piece_column + PIECE_BLOCKS;
	int end_row = b->piece_row + PIECE_BLOCKS;

	int pos_board = 0;
	int pos_piece = 0;
	int v_board = 0;
	int v_piece = 0;

	for(j=ini_row;j < end_row;j++)
	{
		for(i=ini_col;i < end_col;i++)
		{

			pos_board = calc_pos(i,j,b->columns);
			v_piece = pieces[b->current_piece][b->current_rotation][pos_piece];
			if(v_piece > 0)
			{
				b->array_board[pos_board] = 8;
			}
			pos_piece++;
			if(pos_piece > 24) return;
		}
	} 

	
}

void delete_line(board *b,int row)
{

	int i,j;
	int columns = b->columns;

	int pos_1 = 0;
	int v_1 = 0;
	int pos_2 = 0;
	for(j=row;j > 0;j--)
	{
		for(i=0;i < columns;i++)
		{	

			pos_2 = calc_pos(i,j,columns);
			pos_1 = calc_pos(i,j - 1,columns);
			v_1 = b->array_board[pos_1];
			b->array_board[pos_2] = v_1;
			
		}
	}
}



void delete_empty_lines(board *b)
{

	int i,j;
	int columns = b->columns;
	int rows = b->rows;

	int pos;

	int cont = 0;
	
	for(j=0;j < rows;j++)
	{

		i=0;
		while (i < columns)
        {
				pos = calc_pos(i,j,columns);
            	if (b->array_board[pos] == 0) break;
           		i++;			
       	}
 
       		if (i == columns) 
			{	
				
				delete_line(b,j);

			}
	}

}

void draw_piece(board *b)
{

	int i,j;

	int width = b->tile_width;
	int height = b->tile_height;

	int piece_column = b->piece_column;
	int piece_row = b->piece_row;

	int current_piece = b->current_piece;
	int current_rotation = b->current_rotation;

	float x_piece,y_piece;

	float posx = b->x;
	float posy = b->y;
	float posz = b->z;

	int v = 0;
	int pos = 0;

	if(b->status == READY)
	{
		for(j=0;j < PIECE_BLOCKS;j++)
		{
			for(i=0;i < PIECE_BLOCKS;i++)
			{
	
				pos = calc_pos(i,j,5);
				v = pieces[current_piece][current_rotation][pos];
				x_piece = (piece_column + i)*width + posx;
				y_piece = (piece_row + j)*height + posy;
				if(v > 0)
				{												
					draw_tile(v,x_piece,y_piece,posz,width,height,1);
				}
			}	
		}
	}
}

void detect_fill_line(board *b)
{

	int i,j;
	int columns = b->columns;
	int rows = b->rows;

	int pos;

	int cont = 0;
	
	for(j=0;j < rows;j++)
	{

		i=0;
		while (i < columns)
        {
				pos = calc_pos(i,j,columns);
            	if (b->array_board[pos] == 0) break;
           		i++;			
       	}
 
       		if (i == columns) 
			{	
				
				b->pos_fill = j;	

			}
	}

}

int detect_gameover(board *b)
{

	int i;
	int columns = b->columns;
	int rows = b->rows;

	int pos = 0;

	for(i=0;i < columns;i++)
	{
		
		pos = calc_pos(i,0,columns);
		if((b->array_board[pos]) > 0)
		{ 
			return 1;
		}else{
			return 0;
		}		

	}

}

void draw_line(board *b,int line,int num_columns,int posx,int posy,int posz,float alpha)
{

	int i;
	int x_board,y_board;
	int pos = 0;
	int v = 0;
	int width = b->tile_width;
	int height = b->tile_height;	


	for(i=0;i < num_columns;i++)
	{

			pos = calc_pos(i,line,num_columns);
			v = b->array_board[pos];
			x_board = i*width + posx;
			y_board = line*height + posy;
			if(v>0)
			{
				draw_tile(v,x_board,y_board,posz,width,height,alpha);
			}
	
	}



}

void draw_board(board *b)
{

	int j;

	int columns = b->columns;
	int rows = b->rows;

	float posx = b->x;
	float posy = b->y;
	float posz = b->z;

	
	
	for(j=rows-1;j>=0;j--)
	{
		
		switch(b->status)
		{	
			case MARK_LINE:
								
				if(j == b->pos_fill)
				{
					draw_line(b,j,columns,posx,posy,posz,b->alpha);
					b->alpha -= 0.1;
					//if(b->alpha <= 0)b->alpha = 0;					
				}else{
					draw_line(b,j,columns,posx,posy,posz,1);
				}						
				break;

			case MOVE_LINES:

				
				if(j == b->pos_fill)
				{
					draw_line(b,j,columns,posx,posy,posz,b->alpha);
				}					

				if(j < b->pos_fill)
				{						
					draw_line(b,j,columns,posx,posy + b->y_counter,posz,1);
					b->y_counter++;
					if(b->y_counter++ >= b->tile_height)b->y_counter = b->tile_height;
				}
						
				if(j > b->pos_fill)
				{
					draw_line(b,j,columns,posx,posy,posz,1);
				}
							
				break;
				
			default:
				draw_line(b,j,columns,posx,posy,posz,1);
				break;
		}
	}
	

}
