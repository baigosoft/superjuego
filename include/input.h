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

#ifndef INPUT_H_
#define INPUT_H_


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


typedef struct{
	int id;				/* device id */
	int buttons;		/* buttons bitfield */
	int axis1x;			/* joystick X */
	int axis1y;			/* joystick Y */
	int axis2x;			/* second joystick X */
	int axis2y;			/* second joystick Y */
}SE_input_state;


typedef struct{
	int buttonup;		
	int buttondown;		
	int buttonleft;		
	int buttonright;		
	int button0;		
	int button1;		
	int button2;		
	int button3;
	int button4;
	int button5;
	int button6;		
	int button7;
	int button8;		
	int button9;
	int xaxis1;		
	int yaxis1;
	int xaxis2;		
	int yaxis2;
}SE_input_mapping;

#define SE_input_joystick SDL_Joystick
//#define SE_input_state cont_state_t

#define JOY_UP 		    (1<<4)
#define JOY_DOWN 	    (1<<5)
#define JOY_LEFT 	    (1<<6)
#define JOY_RIGHT	    (1<<7)
#define JOY_BUTTON0	    (1<<8)
#define JOY_BUTTON1 	(1<<9)
#define JOY_BUTTON2 	(1<<10)
#define JOY_BUTTON3 	(1<<11)
#define JOY_BUTTON4 	(1<<12)
#define JOY_BUTTON5	    (1<<13)
#define JOY_BUTTON6 	(1<<14)
#define JOY_BUTTON7 	(1<<15)
#define JOY_BUTTON8 	(1<<16)
#define JOY_BUTTON9  	(1<<17)


#define SE_QUIT         (1<<0)
#define SE_FULLSCREEN   (1<<1)

//#define JOY_BUTTONDOWN SDL_JOYBUTTONDOWN
//#define JOY_BUTTONUP SDL_JOYBUTTONUP
//#define JOY_AXISMOTION SDL_JOYAXISMOTION

SE_input_joystick *SE_input_open(int joyid);
int                SE_input_enum();
SE_input_state    *SE_input_poll(SE_input_joystick **joy);
int                SE_input_init();
int                SE_input_close();

#endif
