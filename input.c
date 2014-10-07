/*
    Superjuego Engine
    Copyright (C) 2011 Jorge Luís Cabral y Gabriel Ernesto Cabral

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: baigosoft@hotmail.com
*/


#include "input.h"


SDL_Event eventjoy;
SE_input_state internal_input_state;
int usekb=0;

int SE_input_init(){

	if(SE_input_enum()==0){
		usekb=1;
		printf("SE_input: no hay joysticks disponibles, usando teclado\n");
	}
	return SDL_InitSubSystem(SDL_INIT_JOYSTICK);


}

SE_input_joystick *SE_input_open(int joyid){

	SE_input_joystick *joystick;
	SDL_JoystickEventState(SDL_ENABLE);

	joystick = SDL_JoystickOpen(joyid);
	
	return joystick;

}

int SE_input_enum(){
	return SDL_NumJoysticks();
}


SE_input_state *SE_input_poll(SE_input_joystick **joy){
	Uint8 *keys;
	//internal_input_state.buttons=0;
	switch(usekb){
	case 0:
		while(SDL_PollEvent(&eventjoy))
		{
		    switch(eventjoy.type)
		    {

			case SDL_JOYAXISMOTION:
				if( eventjoy.jaxis.axis == 0){
					internal_input_state.axis1x=eventjoy.jaxis.value;
					if(eventjoy.jaxis.value < -3200){
						internal_input_state.buttons&=~JOY_RIGHT;
						internal_input_state.buttons|=JOY_LEFT;
					}else if(eventjoy.jaxis.value > 3200){
						internal_input_state.buttons&=~JOY_LEFT;
						internal_input_state.buttons|=JOY_RIGHT;
					}else{
						internal_input_state.buttons&=~JOY_LEFT;
						internal_input_state.buttons&=~JOY_RIGHT;
					}

				}
				if( eventjoy.jaxis.axis == 1){
					internal_input_state.axis1y=eventjoy.jaxis.value;
					if(eventjoy.jaxis.value < -3200){
						internal_input_state.buttons&=~JOY_DOWN;
						internal_input_state.buttons|=JOY_UP;
					}else if(eventjoy.jaxis.value > 3200){
						internal_input_state.buttons&=~JOY_UP;
						internal_input_state.buttons|=JOY_DOWN;
					}else{
						internal_input_state.buttons&=~JOY_UP;
						internal_input_state.buttons&=~JOY_DOWN;
					}
				}
			break;

			case SDL_JOYBUTTONDOWN:
			    switch(eventjoy.jbutton.button)
			    {
				case 0: 
					internal_input_state.buttons|=JOY_BUTTON0;break;
				case 1: 
					internal_input_state.buttons|=JOY_BUTTON1;break;
				case 2: 
					internal_input_state.buttons|=JOY_BUTTON2;break;
				case 3: 
					internal_input_state.buttons|=JOY_BUTTON3;break;
				case 4: 
					internal_input_state.buttons|=JOY_BUTTON4;break;
				case 5: 
					internal_input_state.buttons|=JOY_BUTTON5;break;
				case 6: 
					internal_input_state.buttons|=JOY_BUTTON6;break;
				case 7:
					internal_input_state.buttons|=JOY_BUTTON7;break;
			    }break;

			case SDL_JOYBUTTONUP:
			    switch(eventjoy.jbutton.button)
			    {
				case 0: 
					internal_input_state.buttons&=~JOY_BUTTON0;break;
				case 1: 
					internal_input_state.buttons&=~JOY_BUTTON1;break;
				case 2: 
					internal_input_state.buttons&=~JOY_BUTTON2;break;
				case 3: 
					internal_input_state.buttons&=~JOY_BUTTON3;break;
				case 4: 
					internal_input_state.buttons&=~JOY_BUTTON4;break;
				case 5: 
					internal_input_state.buttons&=~JOY_BUTTON5;break;
				case 6: 
					internal_input_state.buttons&=~JOY_BUTTON6;break;
				case 7:
					internal_input_state.buttons&=~JOY_BUTTON7;break;
			    }break;

			case SDL_QUIT:
				internal_input_state.buttons|=SE_QUIT;break;

		    }
		}
		break;
		case 1:
			internal_input_state.buttons=0;
			keys=SDL_GetKeyState(NULL);
					if(keys[SDLK_LEFT]){
						internal_input_state.buttons&=~JOY_RIGHT;
						internal_input_state.buttons|=JOY_LEFT;
					}
					if(keys[SDLK_RIGHT]){
						internal_input_state.buttons|=JOY_RIGHT;
						internal_input_state.buttons&=~JOY_LEFT;
					}
					if(keys[SDLK_UP]){
						internal_input_state.buttons|=JOY_UP;
						internal_input_state.buttons&=~JOY_DOWN;
					}
					if(keys[SDLK_DOWN]){
						internal_input_state.buttons&=~JOY_UP;
						internal_input_state.buttons|=JOY_DOWN;
					}
					if(keys[SDLK_z]){
						internal_input_state.buttons|=JOY_BUTTON0;
					}
					if(keys[SDLK_x]){
						internal_input_state.buttons|=JOY_BUTTON1;
					}
					if(keys[SDLK_c]){
						internal_input_state.buttons|=JOY_BUTTON2;
					}
					if(keys[SDLK_a]){
						internal_input_state.buttons|=JOY_BUTTON3;
					}
					if(keys[SDLK_s]){
						internal_input_state.buttons|=JOY_BUTTON4;
					}
					if(keys[SDLK_d]){
						internal_input_state.buttons|=JOY_BUTTON5;
					}
					if(keys[SDLK_f]){
						internal_input_state.buttons|=JOY_BUTTON6;
					}
					if(keys[SDLK_v]){
						internal_input_state.buttons|=JOY_BUTTON7;
					}
		while(SDL_PollEvent(&eventjoy))
		{
		    switch(eventjoy.type)
		    {
			case SDL_QUIT:
				internal_input_state.buttons|=SE_QUIT;

		    }
		
		}
		break;
	}

	return &internal_input_state;
}
