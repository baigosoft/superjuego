#ifndef GAME_H_
#define GAME_H_

#include "board.h"

#define P1_LEFT 0
#define P1_RIGHT 1
#define P1_DOWN 2
#define P1_UP 3
#define P1_B1 4
#define P1_B2 5

int joybutton = 0;

extern int quit;

extern SE_input_state *state;
extern SE_input_joystick *joystick;

void draw_bg();
void draw_nextpiece_bg(board *b);
void draw_gameover(float x,float y,float z);


void draw_score(board *b);
void draw_score_bg();
void draw_scene(board *b);
void ResetTimeBase();
int CurrentTime();





















#endif
