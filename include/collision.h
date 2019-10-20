#ifndef COLLISION_H_
#define COLLISION_H_

#include "box.h"



int SE_coll_check_position(SE_box *box1,SE_box *box2,float posx1,float posy1,float posx2,float posy2);

int SE_coll_check(SE_box *box1,SE_box *box2);











#endif
