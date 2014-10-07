#ifndef BOARD_H_
#define BOARD_H_

#include "pieces.h"

#define INIT 0
#define READY 1
#define STOPPED 2
#define MARK_LINE 3
#define MOVE_LINES 4
#define DELETE_LINES 5

typedef struct{

	float x,y,z;	
	int columns,rows;
	int tile_width,tile_height;
	int *array_board;
	int current_piece,current_rotation;
	int piece_column,piece_row;
	int pos_fill;
	int score;	
	int status;
	int cycles;
	float colour;
	float alpha;
	float y_counter;

}board;


int calc_pos(int x,int y,int columns);
board *init_board(int columns,int rows,int tile_width,int tile_height);
void board_set_position(board *b,float posx,float posy,float posz);
void piece_set_current(board *b,int current_piece);
void piece_set_rotation(board *b,int current_rotation);
void piece_set_position(board *b,int piece_column,int piece_row);
void board_set_status(board *b,int status);
int check_collision_lateral(board *b);
int check_collision_bottom(board *b);
int check_collision_piece(board *b);

void insert_piece(board *b);
void delete_line(board *b,int row);
void delete_empty_lines(board *b);
void draw_piece(board *b);
void detect_fill_line(board *b);
int detect_gameover(board *b);
void draw_line(board *b,int line,int num_columns,int posx,int posy,int posz,float alpha);
void draw_board(board *b);



















#endif
