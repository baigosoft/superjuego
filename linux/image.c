#include "image.h"


GLuint loadTexture(SDL_Surface *surface)
{

	GLuint texture;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	/*verifica si el ancho de la imagen es potencia de 2*/
	if(SE_utils_powerof2(surface->w) == 0) 
	{		
		printf("SE_screen: Advertencia, el ancho de la imagen no es potencia de 2\n");
		fflush(stdout);
	}
    	/*verifica si el alto de la imagen es potencia de 2*/
	if(SE_utils_powerof2(surface->h) == 0) 
	{	
		printf("SE_screen: Advertencia, el alto de la imagen no es potencia de 2\n");
		fflush(stdout);
	}
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


SE_image *SE_image_load(const char *path)
{
	
	SE_image *img;
	img = (SE_image*)malloc(sizeof(SE_image));
	
	SDL_Surface *temp; 

	printf("SE_image:Cargando textura: %s\n",path);

	if((temp = IMG_Load(path)) == NULL)
	{
		printf("SE_image:Error, no se pudo cargar la imagen\n");
	}
	
	img->texture = loadTexture(temp);

	img->width = temp->w;
	img->height = temp->h;			
	
	SDL_FreeSurface(temp);
	return img;
}




void SE_image_segment_draw_fx(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz,
	float width_image,float height_image,float zoomx,float zoomy,float rotx,float roty,float rotz,
	float r,float g,float b,float alpha)
{

	float width = wtex * zoomx;
	float height = htex * zoomy;

	float w = img->width;
	float h = img->height;


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

		SE_utils_logvertices(4);

	

}

void SE_image_segment_draw_wh(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz,float width,float height)
{

	SE_image_segment_draw_fx(img,xtex,ytex,wtex,htex,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);

}


void SE_image_segment_draw(SE_image *img,float xtex,float ytex,float wtex,float htex,float posx,float posy,float posz)
{

	SE_image_segment_draw_fx(img,xtex,ytex,wtex,htex,posx,posy,posz,wtex,htex,1,1,0,0,0,1,1,1,1);

}


void SE_image_draw_fx(SE_image *img,float posx,float posy,float posz,float width_image,float height_image,
	float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha)
{
	

	SE_image_segment_draw_fx(img,0,0,img->width,img->height,posx,posy,posz,width_image,height_image,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

}

void SE_image_draw_wh(SE_image *img,float posx,float posy,float posz,float width,float height)
{

	SE_image_draw_fx(img,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);

}

void SE_image_draw(SE_image *img,float posx,float posy,float posz)
{

	SE_image_draw_fx(img,posx,posy,posz,img->width,img->height,1,1,0,0,0,1,1,1,1);

}

void SE_image_segment_draw_transf(SE_image *img,SE_transf *tr,float xtex,float ytex,float wtex,float htex)
{

	SE_image_segment_draw_fx(img,
							 xtex,ytex,wtex,htex,
							 tr->x,tr->y,tr->z,
							 tr->width,tr->height,
							 tr->zoomx,tr->zoomy,
							 tr->rotx,tr->roty,tr->rotz,
							 tr->r,tr->g,tr->b,
							 tr->alpha);

}

void SE_image_draw_transf(SE_image *img,SE_transf *tr)
{

	SE_image_draw_fx(img,
					 tr->x,tr->y,tr->z,
					 tr->width,tr->height,
					 tr->zoomx,tr->zoomy,
					 tr->rotx,tr->roty,tr->rotz,
					 tr->r,tr->g,tr->b,
					 tr->alpha);

}

void SE_image_clean(SE_image *img)
{

	free(img);
	printf("SE_image:se elimino puntero de imagen\n");
	
}

