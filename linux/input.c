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


#include "super.h"


SDL_Event eventjoy;
SE_input_state internal_input_state[8];
SE_input_mapping internal_input_map[8];
int usekb=0;

int SE_input_init(){

	return SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	if(SE_input_enum()<1){
		usekb=1;
		SE_utils_log("INPUT: joystick not found, using keyboard\n");
	}

}

int SE_input_close(){

	const char *message = "INPUT: closing Input system";
	SE_utils_log(message);
	return 0;

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


/*read input events*/
SE_input_state *SE_input_poll(SE_input_joystick **joy){

	int joyid;
	joyid = SDL_JoystickIndex(*joy);
//	internal_input_state[eventjoy.jaxis.which].buttons=0;
	while(SDL_PollEvent(&eventjoy))
	{
	    switch(eventjoy.type)
	    {

		case SDL_JOYAXISMOTION:
	        if( eventjoy.jaxis.axis == 0){
				if(eventjoy.jaxis.value < -3200){
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_RIGHT;
					internal_input_state[eventjoy.jaxis.which].buttons|=JOY_LEFT;
				}else if(eventjoy.jaxis.value > 3200){
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_LEFT;
					internal_input_state[eventjoy.jaxis.which].buttons|=JOY_RIGHT;
				}else{
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_LEFT;
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_RIGHT;
				}
			}
			if( eventjoy.jaxis.axis == 1){
				if(eventjoy.jaxis.value < -3200){
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_DOWN;
					internal_input_state[eventjoy.jaxis.which].buttons|=JOY_UP;
				}else if(eventjoy.jaxis.value > 3200){
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_UP;
					internal_input_state[eventjoy.jaxis.which].buttons|=JOY_DOWN;
				}else{
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_UP;
					internal_input_state[eventjoy.jaxis.which].buttons&=~JOY_DOWN;
				}
			}
		break;

		case SDL_JOYBUTTONDOWN:

				if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.button].button0)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON0;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button1)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON1;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button2)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON2;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button3)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON3;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button4)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON4;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button5)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON5;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button6)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON6;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button7)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON7;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button8)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON8;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button9)
				{
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON9;
				}
		break;

		case SDL_JOYBUTTONUP:

				if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.button].button0)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON0;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button1)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON1;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button2)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON2;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button3)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON3;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button4)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON4;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button5)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON5;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button6)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON6;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button7)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON7;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button8)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON8;
				}
				else if(eventjoy.jbutton.button==internal_input_map[eventjoy.jbutton.which].button9)
				{
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON9;
				}
		break;

		case SDL_QUIT:
			internal_input_state[joyid].buttons|=SE_QUIT;break;

		case SDL_KEYDOWN:
	                switch( eventjoy.key.keysym.sym ){
				case SDLK_LEFT:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_RIGHT;
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_LEFT;break;
				case SDLK_RIGHT:
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_RIGHT;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_LEFT;break;
				case SDLK_UP:
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_UP;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_DOWN;break;
				case SDLK_DOWN:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_UP;
					internal_input_state[eventjoy.jbutton.which].buttons|=JOY_DOWN;break;
				case SDLK_z:
			        	internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON0;break;
				case SDLK_x:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON1;break;
				case SDLK_c:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON2;break;
				case SDLK_v:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON3;break;
				case SDLK_a:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON4;break;
				case SDLK_s:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON5;break;
				case SDLK_d:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON6;break;
				case SDLK_f:
		        		internal_input_state[eventjoy.jbutton.which].buttons|=JOY_BUTTON7;break;
				default:
					break;
			}break;

		case SDL_KEYUP:
	                switch( eventjoy.key.keysym.sym ){
				case SDLK_LEFT:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_RIGHT;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_LEFT;break;
				case SDLK_RIGHT:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_RIGHT;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_LEFT;break;
				case SDLK_UP:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_UP;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_DOWN;break;
				case SDLK_DOWN:
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_UP;
					internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_DOWN;break;
				case SDLK_z:
			        	internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON0;break;
				case SDLK_x:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON1;break;
				case SDLK_c:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON2;break;
				case SDLK_v:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON3;break;
				case SDLK_a:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON4;break;
				case SDLK_s:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON5;break;
				case SDLK_d:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON6;break;
				case SDLK_f:
		        		internal_input_state[eventjoy.jbutton.which].buttons&=~JOY_BUTTON7;break;
				default:
					break;
			}break;

	    }
	}

	return &internal_input_state[joyid];
}
