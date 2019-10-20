#include "animation.h"
/*FRAME*/


void SE_frame_init(SE_frame *fr);

void SE_frame_image_add(SE_frame *fr,SE_image *img,int delay,float x_tex,float y_tex,float width_tex,float height_tex);

int SE_frame_delay(SE_frame *fr);

void SE_frame_delay_set(SE_frame *fr,int delay);

void SE_frame_draw(SE_frame *fr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha);

void SE_ani_draw(SE_ani *ani,int frame_number, float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha);


/*FRAME*/

void SE_frame_init(SE_frame *fr)
{

	fr->image = NULL;
	fr->xt = 0;
	fr->yt = 0;
	fr->wt = 1;
	fr->ht = 1;
	fr->delay = 0;

}

void SE_frame_image_add(SE_frame *fr,SE_image *img,int delay,float x_tex,float y_tex,float width_tex,float height_tex)
{

	fr->image = img;
	fr->xt = x_tex;
	fr->yt = y_tex;
	fr->wt = width_tex;
	fr->ht = height_tex;
	fr->delay = delay;

}



int SE_frame_delay(SE_frame *fr)
{

	return fr->delay;

}



void SE_frame_delay_set(SE_frame *fr,int delay)
{

	fr->delay = delay;

}


void SE_frame_draw(SE_frame *fr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha)
{
	
	SE_image_segment_draw_fx(fr->image,
							 fr->xt,fr->yt,fr->wt,fr->ht,
							 posx,posy,posz,
							 width,height,
							 zoomx,zoomy,
							 rotationx,rotationy,rotationz,
							 red,green,blue,
							 alpha);

}


/*ANIMATION*/

SE_ani* SE_ani_init(float width,float height,int numframes)
{

	int i;
	
	SE_ani *ani;

	ani = (SE_ani*)malloc(sizeof(SE_ani));

	ani->width = width;
	ani->height = height;

	ani->numframes = numframes;

	ani->fr = (SE_frame*)malloc(numframes * sizeof(SE_frame));

	for(i=0;i < numframes;i++)
	{

		SE_frame_init(&ani->fr[i]);

	}		

	
	return ani;

}

float SE_ani_width(SE_ani *ani)
{

	return ani->width;

}



float SE_ani_height(SE_ani *ani)
{

	return ani->height;

}


void SE_ani_frame_delay_set(SE_ani *ani,int frame_number,int delay)
{

	SE_frame_delay_set(&ani->fr[frame_number],delay);

}


void SE_ani_addframe_segment(SE_ani *ani,SE_image *img,int frame_number,int delay,float xtex,float ytex,float wtex,float htex)
{
	
	if(ani->fr[frame_number].image == NULL)
	{
		SE_frame_image_add(&ani->fr[frame_number],img,delay,xtex,ytex,wtex,htex);
		printf("se ha cargado con exito imagen en animacion\n");
		fflush(stdout);
	}else{
		printf("ya se ha cargado imagen anteriormente en puntero\n");
		fflush(stdout);
	}

}


void SE_ani_addframe(SE_ani *ani,SE_image *img,int frame_number,int delay)
{

	SE_ani_addframe_segment(ani,img,frame_number,delay,0,0,img->width,img->height);

}

void SE_ani_create_from_img(SE_ani *ani,SE_image *img,int numimagex,int numimagey,int delay)
{

	int i,j;
	int count = 0;		

	float w = ani->width;
	float h = ani->height;

	for(j=0;j<numimagey;j++)
	{			
		for(i=0;i<numimagex;i++)
		{
			SE_ani_addframe_segment(ani,img,count,delay,i*w,j*h,w,h);
			count++;
		}
	}


}


void SE_ani_draw(SE_ani *ani,int frame_number, float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha)
{

	SE_frame_draw(&ani->fr[frame_number],posx,posy,posz,width,height,zoomx,zoomy,rotationx,rotationy,rotationz,red,green,blue,alpha);

}


void SE_ani_clean(SE_ani *ani)
{
	
	free(ani->fr);
	free(ani);

	printf("SE_ani:se elimino puntero de animation\n");
	
} 


/*ANIMATOR*/


SE_animator *SE_animator_init(SE_ani *ani)
{

	SE_animator *ator;
	ator = (SE_animator*)malloc(sizeof(SE_animator));
	ator->ani = ani;

	ator->numframes = ani->numframes;

	/*delay*/
	ator->delayperc = 1;

	/*animation control*/	
	ator->status = START;
	ator->counter = 0;
	ator->currentframe = 0;
	ator->initframe = 0;
	ator->endframe = ator->numframes - 1;

	return ator;

}


int SE_animator_status(SE_animator *ator)
{

	return ator->status;

}


void SE_animator_start(SE_animator *ator)
{
	ator->status = START;
}


void SE_animator_stop(SE_animator *ator)
{
	ator->status = STOP;
}

void SE_animator_initend_set(SE_animator *ator,int initframe,int endframe)
{

	ator->initframe = initframe;
	ator->currentframe = initframe;

	if(endframe > (ator->numframes - 1))
	{

		ator->endframe = ator->numframes -1;

	}else{

		ator->endframe = endframe;

	}

}


void SE_animator_reset(SE_animator *ator)
{

	ator->currentframe = 0;

}

void SE_animator_delaypercent(SE_animator *ator,float delayperc)
{

	ator->delayperc = delayperc;

}

void SE_animator_draw_fx(SE_animator *ator,
						 float posx,float posy,float posz,
						 float width,float height,float zoomx,float zoomy,
						 float rotationx,float rotationy,float rotationz,
						 float red,float green,float blue,float alpha)
{


	SE_ani_draw(ator->ani,ator->currentframe,posx,posy,posz,width,height,zoomx,zoomy,rotationx,rotationy,rotationz,red,green,blue,alpha);
	
	if(ator->status == START)
	{		
		ator->counter++;
		if(ator->counter > (ator->ani->fr[ator->currentframe].delay * ator->delayperc))
		{	
				
			ator->currentframe++;
			ator->counter = 0;

		}
		if(ator->currentframe > ator->endframe)ator->currentframe = ator->initframe;
	}

}

void SE_animator_draw_wh(SE_animator *ator,float posx,float posy,float posz,float width,float height)
{

	SE_animator_draw_fx(ator,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);


}

void SE_animator_draw(SE_animator *ator,float posx,float posy,float posz)
{

	SE_animator_draw_fx(ator,posx,posy,posz,SE_ani_width(ator->ani),SE_ani_height(ator->ani),1,1,0,0,0,1,1,1,1);


}


void SE_animator_draw_transf(SE_animator *ator,SE_transf *tr)
{

	SE_animator_draw_fx(ator,
						tr->x,tr->y,tr->z,
						tr->width,tr->height,
						tr->zoomx,tr->zoomy,
						tr->rotx,tr->roty,tr->rotz,
						tr->r,tr->g,tr->b,tr->alpha);


}

void SE_animator_clean(SE_animator *ator)
{

	free(ator);
	printf("SE_animator:se elimino puntero de animator\n");

}













