#ifndef PIECES_H_
#define PIECES_H_

#include <stdio.h>
#include <stdlib.h>

#include "super.h"

#include "files.h"

#define PIECE_BLOCKS 5


extern int pieces[7][4][25];

void draw_tile(int numtile,float posx,float posy,float posz,int width,int height,float alpha);



















#endif
