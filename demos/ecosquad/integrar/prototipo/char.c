#include "char.h"

char_t *create_character()
{
	char_t *personaje;
	personaje=(char_t *)malloc(sizeof(char_t));
	personaje->rotated=1;		//indica si el personaje terminó de rotar (ver máquina de estados)
	personaje->rotate=0;		//indica si el personaje tiene que rotar a la izquierda o derecha
	personaje->lookingright=1;	//hacia donde esta mirando el personaje
	personaje->rot=0.0f;		//ángulo de rotación del sprite
	personaje->rotinc=10.0f;	//incremento de la rotación
	personaje->posx=0;
	personaje->posy=0;

	return personaje;
}

int move_character(char_t *personaje, SE_tilemap *timap, int jump, int rot)
{

float incremento;
if(rot!=0)personaje->rotate=rot;

	if(rot==1){
		personaje->posx+=5;
		if(personaje->posx>510){ 
			personaje->posx=510;
		}else{
		//	SE_sprite_updateboxes(personaje->character->spr[0],personaje->character->spr[0]->box->x+5,0);
			personaje->character->spr[0]->box->x+=5;
		}

	}else if(rot==-1){
		personaje->posx-=5;
		if(personaje->posx<0){
			 personaje->posx=0;
		}else{
			//SE_sprite_updateboxes(personaje->character->spr[0],personaje->character->spr[0]->box->x,personaje->character->spr[0]->box->y);
			personaje->character->spr[0]->box->x-=5;
		}
	}

//	SE_sprite_updateboxes(personaje->character->spr[0],personaje->character->spr[0]->box->x+5,personaje->character->spr[0]->box->y);

				
	if((personaje->lookingright)&&(personaje->rotated)&&(personaje->rotate==-1)){
		personaje->rotated=0;
		personaje->lookingright=0;
		personaje->rot-=personaje->rotinc;
	}
	if((personaje->lookingright)&&(personaje->rotated==0)&&(personaje->rotate==-1)){
		personaje->lookingright=0;
		personaje->rot-=personaje->rotinc;
	}
	if((personaje->lookingright==0)&&(personaje->rotated)&&(personaje->rotate==1)){
		personaje->rotated=0;
		personaje->lookingright=1;
		personaje->rot+=personaje->rotinc;
	}
	if((personaje->lookingright==0)&&(personaje->rotated==0)&&(personaje->rotate==1)){
		personaje->lookingright=1;
		personaje->rot+=personaje->rotinc;
	}
	if((personaje->lookingright)&&(personaje->rotated==0)&&(personaje->rot>0.0f)){
		personaje->rotate=0;
		personaje->rotated=1;
	}
	if((personaje->lookingright==0)&&(personaje->rotated==0)&&(personaje->rot<-180.0f)){
		personaje->rotate=0;
		personaje->rotated=1;
	}
	if((personaje->lookingright==0)&&(personaje->rotated==0)){
		personaje->rot-=personaje->rotinc;
	}
	if((personaje->lookingright)&&(personaje->rotated==0)){
		personaje->rot+=personaje->rotinc;
	}
				
//	if(jump){
//		if(jumping){
			if(jump)incremento=-18*personaje->tiempo_salto+(1*(personaje->tiempo_salto*personaje->tiempo_salto))/2;
			else incremento=+(1*(personaje->tiempo_salto*personaje->tiempo_salto))/2;
		
//			if(incremento>200)incremento=200;
			//incremento=-20*tiempo_salto+(1*(tiempo_salto*tiempo_salto))/2;
			personaje->tiempo_salto++;
//			printf("incremento %f %f\n",incremento,caja.y);
				if ((personaje->posinicial+incremento)<=personaje->character->spr[0]->box->y){ 	/*si esta subiendo no chequeamos colisiones*/
					personaje->character->spr[0]->box->y=personaje->posinicial+incremento;
					personaje->posy=personaje->posinicial+incremento-10;
					if(personaje->character->spr[0]->box->y<-200) personaje->character->spr[0]->box->y=-200;
				}else{					/*si esta cayendo chequeamos colisiones*/
	//			printf("incremento %f %f\n",posinicial+incremento,caja.y);
					if(!SE_tilemap_collision(timap,personaje->character->spr[0]->box,0,(personaje->posinicial+incremento)-personaje->character->spr[0]->box->y,0)){ /*si no hay colisión*/
						personaje->character->spr[0]->box->y=personaje->posinicial+incremento;
						personaje->posy=personaje->posinicial+incremento-10;

					}else{ /*si hay colisión, terminamos el salto*/
						jump=0;
						//personaje->jumping=0;
						personaje->tiempo_salto=0;
						incremento=0;
						personaje->posinicial=personaje->character->spr[0]->box->y;
					}
				}

	return jump;

}
