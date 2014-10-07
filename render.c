#include "render.h"


SDL_Surface *screen;

int screen_width,screen_height;


void SE_screen_fullscreen(int fs)
{

	if(fs) SDL_WM_ToggleFullScreen(screen);

}

int SE_screen_init(int width,int height,int bpp)
{


	screen_width=width;
	screen_height=height;

	if((SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("SE_screen:Error, no se puede inicializar el subsistema de video\n");
		return 0;
	}
	

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	
	if((screen = SDL_SetVideoMode(screen_width,screen_height,bpp,SDL_OPENGL)) < 0)
	{
		printf("SE_screen:Error, resolución %dx%dx%d no soportada\n",screen_width,screen_height,bpp);
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

	

	glViewport( 0, 0, screen_width, screen_height);
	
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	SE_screen_enable2d();

	return 1;
	
}

void SE_screen_enable2d()							
{

	glMatrixMode(GL_PROJECTION);				
	glPushMatrix();							
	glLoadIdentity();						
	glOrtho(0, (GLdouble)screen_width, (GLdouble)screen_height, 0, -100000, 100000);				
	glMatrixMode(GL_MODELVIEW);					
	glPushMatrix();							
	glLoadIdentity();

	
				
}

void SE_screen_disable2d()							
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



void SE_screen_flip()
{

	SDL_GL_SwapBuffers();/*flipea la escena*/

}

void SE_screen_rotate(float rotx,float roty,float rotz,float pointx,float pointy,float pointz)
{

	glLoadIdentity();

	glTranslatef(pointx,pointy,pointz);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);
	glRotatef(rotz,0,0,1);
	glTranslatef(-pointx,-pointy,-pointz);



} 

void SE_screen_scale(float zoomx,float zoomy,float zoomz)
{
	
	
	glScalef(zoomx,zoomy,zoomz);


}

void SE_screen_resettransform()
{

	glLoadIdentity();

}

SE_transf *SE_transf_init()
{

	SE_transf *tr;
	tr = (SE_transf*)malloc(sizeof(SE_transf));

	tr->x = 0;
	tr->y = 0;
	tr->z = 0;
	
	tr->width = 1;
	tr->height = 1;

	tr->zoomx = 1;
	tr->zoomy = 1;

	tr->rotx = 0;
	tr->roty = 0;
	tr->rotz = 0;

	tr->r = 1;
	tr->g = 1;
	tr->b = 1;
	
	tr->alpha = 1;

	return tr;

}



void SE_transf_clean(SE_transf *tr)
{

	free(tr);

} 

void SE_transf_positionx_set(SE_transf *tr,float posx)
{

	tr->x = posx;

}

void SE_transf_positiony_set(SE_transf *tr,float posy)
{

	tr->y = posy;

}

void SE_transf_positionz_set(SE_transf *tr,float posz)
{

	tr->z = posz;

}

void SE_transf_position_set(SE_transf *tr,float posx,float posy,float posz)
{

	SE_transf_positionx_set(tr,posx);
	SE_transf_positiony_set(tr,posy);
	SE_transf_positionz_set(tr,posz);

}

void SE_trasf_width_set(SE_transf *tr,float width)
{

	tr->width = width;

}

void SE_trasf_height_set(SE_transf *tr,float height)
{

	tr->height = height;

}

void SE_transf_dimentions_set(SE_transf *tr,float width,float height)
{

	SE_trasf_width_set(tr,width);
	SE_trasf_height_set(tr,height);

}

void SE_transf_zoomx_set(SE_transf *tr,float zoomx)
{

	tr->zoomx = zoomx;

}

void SE_transf_zoomy_set(SE_transf *tr,float zoomy)
{

	tr->zoomy = zoomy;

}

void SE_transf_zoom_set(SE_transf *tr,float zoom)
{

	SE_transf_zoomx_set(tr,zoom);
	SE_transf_zoomy_set(tr,zoom);

}

void SE_transf_rotationx_set(SE_transf *tr,float rotx)
{

	tr->rotx = rotx;

}

void SE_transf_rotationy_set(SE_transf *tr,float roty)
{

	tr->roty = roty;

}

void SE_transf_rotationz_set(SE_transf *tr,float rotz)
{

	tr->rotz = rotz;

}

void SE_transf_rotation_set(SE_transf *tr,float rotx,float roty,float rotz)
{

	SE_transf_rotationx_set(tr,rotx);
	SE_transf_rotationy_set(tr,roty);
	SE_transf_rotationz_set(tr,rotz);

}

void SE_transf_rgb_set(SE_transf *tr,float red,float green,float blue)
{

	tr->r = red;
	tr->g = green;
	tr->b = blue;

}

void SE_transf_alpha_set(SE_transf *tr,float alpha)
{

	tr->alpha = alpha;

}
