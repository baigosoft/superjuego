#include "render.h"
#include "utils.h"


SDL_Surface *screen;

int screen_width;
int screen_height;
int screen_bpp;

int SE_screen_width()
{
	return screen_width;
}

int SE_screen_height()
{
	return screen_height;
}

int SE_screen_bpp()
{
	return screen_bpp;
}

void SE_screen_fullscreen(int fs){

	if(fs) SDL_WM_ToggleFullScreen(screen);

}

int SE_screen_init(int width,int height,int bpp)
{

/*	SE_screen.width=width;
	SE_screen.height=height;
	SE_screen.bpp=bpp;
	SE_screen.fullscreen=0;*/

	screen_width = width;
	screen_height = height;
	screen_bpp = bpp;
	
	if((SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("error, no inicia video");
		return 0;
	}
	

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	
//	if((screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_OPENGL)) < 0)
	if((screen = SDL_SetVideoMode(width,height,bpp,SDL_OPENGL)) < 0)
	{
		printf("error, no inicia modo gráfico");
		return 0;
	}
	

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable( GL_TEXTURE_2D );

	/* This allows alpha blending of 2D textures with the scene */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE );

	
//	glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glViewport( 0, 0, width, height);
	
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	enable2d();
	
	
	return 1;
	
}

void enable2d()							
{

	glMatrixMode(GL_PROJECTION);				
	glPushMatrix();							
	glLoadIdentity();						
	glOrtho(0, (GLdouble)screen_width, (GLdouble)screen_height, 0, -100000, 100000);				
	glMatrixMode(GL_MODELVIEW);					
	glPushMatrix();							
	glLoadIdentity();

	
				
}

void disable2d()							
{
	glMatrixMode( GL_PROJECTION );					
	glPopMatrix();							
	glMatrixMode( GL_MODELVIEW );					
	glPopMatrix();							
}

void SE_screen_clear(float r,float g,float b,float a)
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(r,g,b,a);

}

void SE_screen_fade(float r,float g,float b,float a)
{

	SE_drawrectangle(0,0,0,screen_width,screen_height,1,r,g,b,a);


}

GLuint loadTexture(SDL_Surface *surface)
{
	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	//verifica si el ancho de la imagen es potencia de 2
	if(SE_utils_powerof2(surface->w) == 0) printf("warning: image width is not a power of 2\n");
    	//verifica si el alto de la imagen es potencia de 2
	if(SE_utils_powerof2(surface->h) == 0) printf("warning: image height is not a power of 2\n");

	w = surface->w;
	h = surface->h;
	
	
	image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
#endif
		       );
	if ( image == NULL ) {
		return 0;
	}

	/* Save the alpha blending attributes */
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, 0, 0);
	}

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     w, h,
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     image->pixels);
	SDL_FreeSurface(image); /* No longer needed */

	return texture;


}


SE_image *SE_image_load(char *path)
{
	
	SE_image *img;
	img = (SE_image*)malloc(sizeof(SE_image));
	
	SDL_Surface *temp; 

	if((temp = IMG_Load(path)) == NULL)
	{
		printf("error, no se pudo cargar la imagen");
	}
	
	img->texture = loadTexture(temp);

	img->w = temp->w;
	img->h = temp->h;
	
	img->x = 0;
	img->y = 0;

	
	SDL_FreeSurface(temp);
	return img;
}


void SE_image_draw(SE_image *img,float posx,float posy,float posz)
{

	SE_image_full_draw(img,posx,posy,posz,1,1,0,0,0,1,1,1,1);

}


void SE_image_full_draw(SE_image *img,float posx,float posy,float posz,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha)
{
	

	SE_image_segment_draw(img,0,0,img->w,img->h,posx,posy,posz,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

}


void SE_image_segment_draw(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha)
{

float width = wtex * zoomx;
float height = htex * zoomy;

float w = img->w;
float h = img->h;
/*printf("%f",h);*/


if(w == 0)w = 1;
if(h == 0)h = 1;


float x1 = xtex/w;
float y1 = ytex/h;
float x2 = (xtex + wtex)/w;
float y2 = (ytex + htex)/h;

	glPushMatrix();	

	glEnable( GL_TEXTURE_2D );		

	glTranslatef(width/2 ,height/2,posz);
	glTranslatef(posx,posy,posz);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);
	glRotatef(rotz,0,0,1);

	glTranslatef(-width/2,-height/2,posz);




	glColor4f(r,g,b,alpha);/*alpha blending*/
		
	glBindTexture(GL_TEXTURE_2D,img->texture);

	glBegin(GL_QUADS);

		glTexCoord2f(x1,y1);
		glVertex2f(0,0);    

		glTexCoord2f(x2,y1);
		glVertex2f(width,0);

		glTexCoord2f(x2,y2);
		glVertex2f(width,height);
    
		glTexCoord2f(x1,y2);
		glVertex2f(0,height);
	glEnd();


	glPopMatrix();

}


void SE_image_triangle_draw(SE_image *img,SE_vector *vertex,float *u,float *v,float posx,float posy,float posz,float rotx, float roty, float rotz)
{

	glBindTexture(GL_TEXTURE_2D,img->texture);

	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);
	glRotatef(rotz,0,0,1);

	glBegin(GL_TRIANGLES);

		glTexCoord2f(u[0],v[0]);
		glVertex2f(vertex[0].x,vertex[0].y);    

		glTexCoord2f(u[1],v[1]);
		glVertex2f(vertex[1].x,vertex[1].y);

		glTexCoord2f(u[2],v[2]);
		glVertex2f(vertex[2].x,vertex[2].y);
    
	glEnd();


	SE_utils_logtriangles(1);


}


void SE_image_clean(SE_image *img)
{

	free(img);
	if(img != 0)
	{
		printf("error, no se pudo borrar puntero de imagen");
	}
	

}

void SE_screen_flip()
{

	SDL_GL_SwapBuffers();/*flipea la escena*/

}

void SE_rotateatpoint(float rotx,float roty,float rotz,float pointx,float pointy,float pointz)
{

	glLoadIdentity();

	glTranslatef(pointx,pointy,pointz);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);
	glRotatef(rotz,0,0,1);
	glTranslatef(-pointx,-pointy,-pointz);



} 

void SE_scale(float zoomx,float zoomy,float zoomz)
{
	
	
	glScalef(zoomx,zoomy,zoomz);


}

void SE_resettransform()
{

	glLoadIdentity();

}

void SE_image_position(SE_image *img,float posx,float posy)
{

	img->x = posx;
	img->y = posy;


}


/*primitives*/

void SE_drawpoint(float x,float y,float z,float red,float green,float blue,float alpha)
{
	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	glColor4f(red,green,blue,alpha);
	glBegin(GL_POINTS);
		glVertex3f(x,y,z);
	glEnd();

	glPopMatrix();

}

void SE_drawline(float x1,float y1,float x2,float y2,float red,float green,float blue,float alpha)
{


	glPushMatrix();

	glDisable( GL_TEXTURE_2D );

	glColor4f(red,green,blue,alpha);
	glBegin(GL_LINES);
		glVertex2f(x1,y1); 
		glVertex2f(x2,y2);
	glEnd();

	glPopMatrix();

}

void SE_drawrectangle(float x,float y,float z,float width,float height,int fill,float red,float green,float blue,float alpha)
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
		glVertex2f(0,0);    
		glVertex2f(width,0);
		glVertex2f(width,height);
		glVertex2f(0,height);
	glEnd();



	glPopMatrix();



}

void SE_drawcircle(float x,float y,float z,float radius,int sections,int fill,float red,float green,float blue,float alpha)
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
		glVertex2f(radius * cos(i *  twoPi / sections), 
		radius* sin(i * twoPi / sections));
	}
	glEnd();


	glPopMatrix();

}




