#ifndef FIELD_H_
#define FIELD_H_




typedef struct
{

	int field_w,field_h;/*dimensiones del campo de juego en cm*/

}JF_field;



JF_field *JF_field_init(int field_width,int field_height);
void JF_field_clean(JF_field *fd);




















#endif
