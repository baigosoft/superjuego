#ifndef FIELD_H_
#define FIELD_H_

typedef struct
{

	int field_width,field_height;/*dimensiones del campo de juego en cm*/
	int field_goal_width,field_goal_height;
	int field_goal_pos;		

}field;



field *field_init(int field_width,int field_height);
void field_clean(field *fd);




















#endif
