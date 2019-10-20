#include "character.h"
#include "tile.h"

typedef struct
{

	float posinicial;
	float rot;
	float rotz;
	float zoom;
	float rotinc;
	float rotated;
	int rotate;
	float lookingright;
	SE_character *character;
	int tiempo_salto;
	float posx;
	float posy;
	int kill;
	int load;
	int jump;

	
}char_t;


char_t *create_character();
void restart_character(char_t *personaje);
int move_character(char_t *personaje, SE_tilemap *timap, int jump, int rot);
void kill_character(char_t *personaje);
void suck_enemy(char_t *personaje);
int throw_enemy(char_t *personaje);
