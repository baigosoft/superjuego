#include "character.h"
#include "tile.h"

typedef struct
{

	float posinicial;
	float rot;
	float rotinc;
	float rotated;
	int rotate;
	float lookingright;
	SE_character *character;
	int tiempo_salto;
	float posx;
	float posy;

	
}char_t;


char_t *create_character();
int move_character(char_t *personaje, SE_tilemap *timap, int jump, int rot);
