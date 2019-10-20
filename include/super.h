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

/*definiciones del engine*/

//#include <SDL/SDL.h>

#ifndef SUPERJUEGO_H_
#define SUPERJUEGO_H_

#ifdef DREAMCAST
#include <kos.h>
#include <png/png.h>
#include <plx/texture.h>
#include <plx/context.h>
#include <plx/prim.h>
#else
//#include "opencv.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef ANDROID
#include <GLES/gl.h>
#include <android/log.h>
//#include "eglport.h"
#endif


#include "utils.h"
#include "timer.h"
#include "render.h"
#include "image.h"
#include "animation.h"
#include "box.h"
#include "collision.h"
#include "sprite.h"
#include "audio.h"
#include "movie.h"
#include "input.h"
#include "font.h"
#include "tile.h"
#include "primitives.h"
#include "console.h"
#include "luascript.h"
#include "transform.h"


//#include "md2.h"

#endif



