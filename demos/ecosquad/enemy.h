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
	int killed;
	int sucked;
	int jump;
	int release;

	
}enemy_t;


enemy_t *create_enemy();
void restart_enemy(enemy_t *enemy);
void draw_enemy(enemy_t *enemy);
void update_enemy_position(enemy_t *enemy, SE_tilemap *timap);
void enemy_set_position(enemy_t *enemy,int posx,int posy);


