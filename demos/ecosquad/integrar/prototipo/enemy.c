#include "enemy.h"

enemy_t *create_enemy(){

	enemy_t *personaje;
	personaje=(enemy_t *)malloc(sizeof(enemy_t));
	personaje->rotated=1;		//indica si el personaje terminó de rotar (ver máquina de estados)
	personaje->rotate=0;		//indica si el personaje tiene que rotar a la izquierda o derecha
	personaje->lookingright=1;	//hacia donde esta mirando el personaje
	personaje->rot=0.0f;		//ángulo de rotación del sprite
	personaje->rotinc=10.0f;	//incremento de la rotación
	personaje->posx=0;
	personaje->posy=0;
	personaje->posinicial=0;
	personaje->tiempo_salto=0;

	return personaje;

}


void draw_enemy(enemy_t *enemy){



}


void update_enemy_position(enemy_t *enemy, SE_tilemap *timap){

float incremento=0;
int jump=0;

//if(rot!=0)enemy->rotate=rot;

	if(enemy->lookingright==1){
		enemy->posx+=1;
		if(enemy->posx>550){ 
			enemy->posx=550;
			enemy->rotate=-1;
//			enemy->lookingright=0;
		}else{
		//	SE_sprite_updateboxes(enemy->character->spr[0],enemy->character->spr[0]->box->x+5,0);
			enemy->character->spr[0]->box->x+=1;
		}

	}else{

		enemy->posx-=1;
		if(enemy->posx<50){
			 enemy->posx=50;
			enemy->rotate=1;
//			enemy->lookingright=1;
		}else{
			//SE_sprite_updateboxes(enemy->character->spr[0],enemy->character->spr[0]->box->x,enemy->character->spr[0]->box->y);
			enemy->character->spr[0]->box->x-=1;
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
			if(jump)incremento=-18*enemy->tiempo_salto+(1*(enemy->tiempo_salto*enemy->tiempo_salto))/2;
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
						jump=0;
						//enemy->jumping=0;
						enemy->tiempo_salto=0;
						incremento=0;
						enemy->posinicial=enemy->character->spr[0]->box->y;
					}
				}

	printf("%f %f\n",enemy->posx,enemy->posy);
//	return jump;

}
