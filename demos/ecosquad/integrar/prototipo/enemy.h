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

	
}enemy_t;


enemy_t *create_enemy();
void draw_enemy(enemy_t *enemy);
void update_enemy_position(enemy_t *enemy, SE_tilemap *timap);


