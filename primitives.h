#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_


#include <stdio.h>
#include <stdlib.h>
#include "render.h"


void SE_prim_drawpoint(float x,float y,float z,float red,float green,float blue,float alpha);
void SE_prim_drawline(float x1,float y1,float x2,float y2,float red,float green,float blue,float alpha);
void SE_prim_drawrectangle(float x,float y,float z,float width,float height,int fill,float red,float green,float blue,float alpha);
void SE_prim_drawcircle(float x,float y,float z,float radius,int sections,int fill,float red,float green,float blue,float alpha);

