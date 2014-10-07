#include "field.h"



field *field_init(int field_width,int field_height)
{

	field *fd;
	fd = (field*)malloc(sizeof(field));
	fd->field_width = field_width;
	fd->field_height = field_height;
	fd->field_goal_width = 500;
	fd->field_goal_height = 240;
	fd->field_goal_pos = 0;/*lo calculo despues, en realidad no lo necesito*/

	return fd;

}

void field_clean(field *fd)
{

	free(fd);

}
