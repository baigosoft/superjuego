#include "field.h"



JF_field *JF_field_init(int field_width,int field_height)
{

	JF_field *fd;
	fd = (JF_field*)malloc(sizeof(JF_field));
	fd->field_w = field_width;
	fd->field_h = field_height;

	return fd;

}

void JF_field_clean(field *fd)
{

	free(fd);

}
