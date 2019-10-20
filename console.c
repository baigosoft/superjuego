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
#include "font8x8.h"

char bufferc[4096];
SE_image *ifont;
SE_font *font;
int show_console=0;


void SE_console_init()
{

	//setvbuf(stdout, bufferc, _IOFBF, 4096);
	const char *font_type = "font8x8.png";
    ifont = SE_image_load(font_type);
	font = SE_font_create(ifont,16,16,8,8);
	SE_font_space_set(font,5);
	SE_font_letterspacing_set(font,1);


}

void SE_console_draw()
{

	if(show_console)
	{
		SE_screen_clear(0,0,0,0);	
		SE_font_draw(font,(char*)bufferc,0,0,0);
	}
}


void SE_console_hide()
{

	show_console=0;

}

void SE_console_show()
{

	show_console=1;

}

void SE_console_toggle()
{
	if(show_console)
		show_console=0;
	else
		show_console=1;

}

