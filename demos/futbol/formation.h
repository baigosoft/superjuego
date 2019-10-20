#ifndef FORMATION_H_
#define FORMATION_H_


/*Formaciones del equipo. Ej: 4-4-2,4-3-3,etc*/

typedef struct
{

	int posx,posy;

}JF_f_pos;

extern JF_fpos JF_form[3][11];//0 = 4-4-2;1 = 4-3-3;2 = 3-5-2


void JF_formation_init();


























#endif
