#include "enemy.h"

#define ENEMY_SPEED 3

enemy_t *create_enemy(){

	enemy_t *enemy;
	enemy=(enemy_t *)malloc(sizeof(enemy_t));
	enemy->rotated=1;		//indica si el enemy terminó de rotar (ver máquina de estados)
	enemy->rotate=0;		//indica si el enemy tiene que rotar a la izquierda o derecha
	enemy->lookingright=1;	//hacia donde esta mirando el enemy
	enemy->rot=0.0f;		//ángulo de rotación del sprite
	enemy->rotinc=10.0f;	//incremento de la rotación
	enemy->posx=0;
	enemy->posy=0;
	enemy->posinicial=0;
	enemy->tiempo_salto=0;
	enemy->killed=0;
	enemy->sucked=0;
	enemy->jump=0;
	enemy->release=0;
	enemy->zoom=1.0f;
	enemy->rotz=0.0f;

	return enemy;

}

void restart_enemy(enemy_t *enemy)
{

	enemy->rotated=1;		//indica si el enemy terminó de rotar (ver máquina de estados)
	enemy->rotate=0;		//indica si el enemy tiene que rotar a la izquierda o derecha
	enemy->lookingright=1;	//hacia donde esta mirando el enemy
	enemy->rot=0.0f;		//ángulo de rotación del sprite
	enemy->rotinc=10.0f;	//incremento de la rotación
	enemy->posx=0;
	enemy->posy=0;
	enemy->posinicial=0;
	enemy->tiempo_salto=0;
	enemy->killed=0;
	enemy->sucked=0;
	enemy->jump=0;
	enemy->zoom=1.0f;
	enemy->rotz=0.0f;

}

void enemy_set_position(enemy_t *enemy,int posx,int posy)
{

	enemy->posx=posx;
	enemy->posy=posy;
	enemy->character->spr[0]->box->x=posx+10;
	enemy->character->spr[0]->box->y=posy;
	enemy->posinicial=posy;



}

void draw_enemy(enemy_t *enemy){



}


void update_enemy_position(enemy_t *enemy, SE_tilemap *timap){

float incremento=0;

//if(rot!=0)enemy->rotate=rot;
if(!enemy->killed){
	if(enemy->lookingright==1){
		enemy->posx+=ENEMY_SPEED;
		enemy->character->spr[0]->box->x+=ENEMY_SPEED;
		if(enemy->posx>550){ 
			enemy->posx=550;
			enemy->character->spr[0]->box->x=555;
			enemy->rotate=-1;
			enemy->jump=1;
//			enemy->lookingright=0;

		}

	}else{

		enemy->posx-=ENEMY_SPEED;
		enemy->character->spr[0]->box->x-=ENEMY_SPEED;
		if(enemy->posx<50){
			 enemy->posx=50;
			enemy->character->spr[0]->box->x=55;
			enemy->rotate=1;
			enemy->jump=1;
//			enemy->lookingright=1;
		}
	}
}

//	SE_sprite_updateboxes(enemy->character->spr[0],enemy->character->spr[0]->box->x+5,enemy->character->spr[0]->box->y);

				
	if((enemy->lookingright)&&(enemy->rotated)&&(enemy->rotate==-1)){
		enemy->rotated=0;
		enemy->lookingright=0;
		enemy->rot-=enemy->rotinc;
	}
	if((enemy->lookingright)&&(enemy->rotated==0)&&(enemy->rotate==-1)){
		enemy->lookingright=0;
		enemy->rot-=enemy->rotinc;
	}
	if((enemy->lookingright==0)&&(enemy->rotated)&&(enemy->rotate==1)){
		enemy->rotated=0;
		enemy->lookingright=1;
		enemy->rot+=enemy->rotinc;
	}
	if((enemy->lookingright==0)&&(enemy->rotated==0)&&(enemy->rotate==1)){
		enemy->lookingright=1;
		enemy->rot+=enemy->rotinc;
	}
	if((enemy->lookingright)&&(enemy->rotated==0)&&(enemy->rot>0.0f)){
		enemy->rotate=0;
		enemy->rotated=1;
	}
	if((enemy->lookingright==0)&&(enemy->rotated==0)&&(enemy->rot<-180.0f)){
		enemy->rotate=0;
		enemy->rotated=1;
	}
	if((enemy->lookingright==0)&&(enemy->rotated==0)){
		enemy->rot-=enemy->rotinc;
	}
	if((enemy->lookingright)&&(enemy->rotated==0)){
		enemy->rot+=enemy->rotinc;
	}
				
//	if(jump){
//		if(jumping){
			if(enemy->jump)incremento=-18*enemy->tiempo_salto+(1*(enemy->tiempo_salto*enemy->tiempo_salto))/2;
			else incremento=+(1*(enemy->tiempo_salto*enemy->tiempo_salto))/2;

//			printf("incremento %f %f\n",enemy->posinicial,incremento);
		
//			if(incremento>200)incremento=200;
			//incremento=-20*tiempo_salto+(1*(tiempo_salto*tiempo_salto))/2;
			enemy->tiempo_salto++;
//			printf("incremento %f %f\n",incremento,caja.y);
				if ((enemy->posinicial+incremento)<=enemy->character->spr[0]->box->y){ 	/*si esta subiendo no chequeamos colisiones*/
					enemy->character->spr[0]->box->y=enemy->posinicial+incremento;
					enemy->posy=enemy->posinicial+incremento;
					if(enemy->character->spr[0]->box->y<-200) enemy->character->spr[0]->box->y=-200;
				}else{					/*si esta cayendo chequeamos colisiones*/

					if(!SE_tilemap_collision(timap,enemy->character->spr[0]->box,0,(enemy->posinicial+incremento)-enemy->character->spr[0]->box->y,0)){ /*si no hay colisión*/
						enemy->character->spr[0]->box->y=enemy->posinicial+incremento;
						enemy->posy=enemy->posinicial+incremento;

					}else{ /*si hay colisión, terminamos el salto*/
						if(enemy->jump==1){
						//	if(enemy->rotate==-1)enemy->rotate=1;
						//	else enemy->rotate=1;
						}
						enemy->jump=0;
						//enemy->jumping=0;
						enemy->tiempo_salto=0;
						incremento=0;
						enemy->posinicial=enemy->character->spr[0]->box->y;

					}
				}


//	return jump;

}
