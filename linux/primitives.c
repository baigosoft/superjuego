#include "primitives.h"




void SE_prim_drawpoint(float x,float y,float z,float red,float green,float blue,float alpha)
{
	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	glColor4f(red,green,blue,alpha);
	glBegin(GL_POINTS);
		glVertex3f(x,y,z);
	glEnd();

	glPopMatrix();

}

void SE_prim_drawline(float x1,float y1,float x2,float y2,float z,float red,float green,float blue,float alpha)
{


	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	glColor4f(red,green,blue,alpha);
	glBegin(GL_LINES);
		glVertex3f(x1,y1,z); 
		glVertex3f(x2,y2,z);
	glEnd();

	glPopMatrix();

}

void SE_prim_drawrectangle(float x,float y,float z,float width,float height,int fill,float red,float green,float blue,float alpha)
{

	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	glTranslatef(x,y,z);
	glColor4f(red,green,blue,alpha);
	if(fill == 0)
	{
		glBegin(GL_LINE_LOOP);
	}else{
		glBegin(GL_QUADS);
	}
		glVertex3f(0,0,z);    
		glVertex3f(width,0,z);
		glVertex3f(width,height,z);
		glVertex3f(0,height,z);
	glEnd();



	glPopMatrix();



}

void SE_prim_drawcircle(float x,float y,float z,float radius,int sections,int fill,float red,float green,float blue,float alpha)
{

	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	int i;
	float twoPi = 2.0f * 3.14159f;
	glTranslatef(x,y,z);
	glColor4f(red,green,blue,alpha);
	if(fill == 0)
	{
		glBegin(GL_LINE_LOOP);
	}else{	
		glBegin(GL_TRIANGLE_FAN);
	}
	glVertex2f(0,0); 
	for(i = 0; i <= sections;i++) 
	{ 
		glVertex3f(radius * cos(i *  twoPi / sections), 
		radius* sin(i * twoPi / sections),z);
	}
	glEnd();


	glPopMatrix();

}




