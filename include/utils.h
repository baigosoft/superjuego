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

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

#define TRUE 1
#define FALSE 0

static int vertices=0;

/*Verifica si es potencia de 2*/
int SE_utils_powerof2(int number); 

/*Muestra y almacena mensajes de log*/
void SE_utils_log(const char *message);

void SE_utils_logvertices(int verts);
void SE_utils_logvertices_init();
int  SE_utils_vertices();



#endif






