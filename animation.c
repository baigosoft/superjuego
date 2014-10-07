#include "animation.h"


/*FRAME*/

void SE_frame_image_add_segment(SE_frame *fr,SE_image *img,float x_tex,float y_tex,float width_tex,float height_tex)
{

	fr->image = img;
	fr->xt = x_tex;
	fr->yt = y_tex;
	fr->wt = width_tex;
	fr->ht = height_tex;

}

void SE_frame_image_add(SE_frame *fr,SE_image *img)
{

	SE_frame_image_add_segment(fr,img,0,0,img->width,img->height);

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

SE_ani* SE_ani_init(float width,float height)
{

	SE_ani *ani;

	ani = (SE_ani*)malloc(sizeof(SE_ani));

	ani->numframes = 0;

	ani->width = width;
	ani->height = height;

	
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

	if(ani->numframes == 1)	
	{
		SE_frame_delay_set(ani->fr,delay);

	}else if(ani->numframes > 1){

		SE_frame_delay_set(&ani->fr[frame_number],delay);

	}

}


void SE_ani_addframe_segment(SE_ani *ani,SE_image *img,int delay,float xtex,float ytex,float wtex,float htex)
{
	
	if(ani->numframes == 0)
	{	
		ani->numframes++;			
		ani->fr = (SE_frame*)malloc(sizeof(SE_frame));
		SE_frame_image_add_segment(ani->fr,img,xtex,ytex,wtex,htex);
		SE_ani_frame_delay_set(ani,0,delay);
		
	}else if(ani->numframes > 0){
	
		ani->numframes++;	
		ani->fr = (SE_frame*)realloc(ani->fr,ani->numframes * sizeof(SE_frame));
		SE_frame_image_add_segment(&ani->fr[ani->numframes - 1],img,xtex,ytex,wtex,htex);
		SE_ani_frame_delay_set(ani,(ani->numframes - 1),delay);

	}


}

void SE_ani_addframe(SE_ani *ani,SE_image *img,int delay)
{

	SE_ani_addframe_segment(ani,img,delay,0,0,img->width,img->height);

}


void SE_ani_draw(SE_ani *ani,int frame_number, float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,
		   float rotationx,float rotationy,float rotationz,float red,float green,float blue,float alpha)
{

	if((ani->numframes) == 1)
	{

		SE_frame_draw(ani->fr,posx,posy,posz,width,height,zoomx,zoomy,rotationx,rotationy,rotationz,red,green,blue,alpha);

	}else if((ani->numframes) > 1){

		SE_frame_draw(&ani->fr[frame_number],posx,posy,posz,width,height,
				zoomx,zoomy,rotationx,rotationy,rotationz,
				red,green,blue,alpha);

	}

}


void SE_ani_clean(SE_ani *ani)
{
	
	free(ani->fr);
	free(ani);

	if(ani != 0)
	{
		printf("error, no se pudo borrar puntero de animacion");
	}
	
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

void SE_animator_initframe_set(SE_animator *ator,int initframe)
{

	ator->initframe = initframe;
	ator->currentframe = initframe;

}

void SE_animator_endframe_set(SE_animator *ator,int endframe)
{

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

void SE_animator_draw(SE_animator *ator,float posx,float posy,float posz,float width,float height)
{

	SE_animator_draw_fx(ator,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);


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

}













