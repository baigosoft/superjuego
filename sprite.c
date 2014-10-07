#include "sprite.h"




SE_sprite *SE_sprite_init(SE_ani *ani)
{

	SE_sprite *spr;
	spr = (SE_sprite*)malloc(sizeof(SE_sprite));
	spr->ator = SE_animator_init(ani);
	spr->box = NULL;
	spr->numboxes = 0;
	spr->offsetx = 0;
	spr->offsety = 0;

	return spr;

}

float SE_sprite_width(SE_sprite *spr)
{

	return SE_ani_width(spr->ator->ani);

}

float SE_sprite_height(SE_sprite *spr)
{

	return SE_ani_height(spr->ator->ani);

}


void SE_sprite_offset_set(SE_sprite *spr,float offsetx,float offsety)
{

	spr->offsetx = offsetx;
	spr->offsety = offsety;

}

void SE_sprite_box_add(SE_sprite *spr,float offsetx,float offsety,float width_box,float height_box)
{
	if(spr->numboxes == 0)
	{
		spr->box = (SE_box*)malloc(sizeof(SE_box));
		spr->box->x = offsetx;
		spr->box->y = offsety;
		spr->box->w = width_box;
		spr->box->h = height_box;
		spr->numboxes++; 


	}else if(spr->numboxes > 0){
		spr->numboxes++; 
		spr->box = (SE_box*)realloc(spr->box,spr->numboxes * sizeof(SE_box));
		spr->box[spr->numboxes - 1].x = offsetx;
		spr->box[spr->numboxes - 1].y = offsety;
		spr->box[spr->numboxes - 1].w = width_box;
		spr->box[spr->numboxes - 1].h = height_box;


	}


}

void SE_sprite_box_set_offset(SE_sprite *spr,int numbox,float offsetx,float offsety)
{

	SE_box_position_set(&spr->box[numbox],offsetx,offsety);

}

void SE_sprite_box_set_dimentions(SE_sprite *spr,int numbox,float width_box,float height_box)
{

	SE_box_dimentions_set(&spr->box[numbox],width_box,height_box);

}


int SE_sprite_checkcollision(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2)
{

	return SE_box_check_position(&spr1->box[numbox1],&spr2->box[numbox2],posx1,posy1,posx2,posy2);

}

int SE_sprite_checkcollision_multi(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2)
{
	
	int boxes1 = spr1->numboxes;
	int boxes2 = spr2->numboxes;
	int coll = 0;
	
	int i,j;
	
	for(i = 0;i < boxes1;i++)
	{	
		for(j = 0;j < boxes2;j++)				
		{

			/*chequea todas las cajas de sprite 1 con todas las cajas de sprite 2*/
			
			coll = SE_sprite_checkcollision(spr1,i,spr2,j,posx1,posy1,posx2,posy2);
			if(coll > 0)
			{

				return 1;

			}
		}
	}
	return 0;
}


void SE_sprite_clean(SE_sprite *spr)
{
	
	free(&spr->box);
	free(&spr->ator);
	free(spr);/*luego se borra el sprite*/

}

/*
void SE_sprite_drawbox(SE_sprite *spr,float posx,float posy)
{
	int i;
	int n = spr->numboxes;
	int x,y,w,h,relx,rely;
	
	for(i=0;i<n;i++)
	{

		w = spr->box[i].w;
		h = spr->box[i].h;

		relx = spr->box[i].relx;
		rely = spr->box[i].rely;


						

		SE_drawrectangle(posx + relx,posy + rely,0,w,h,0,0,1,0,1);

	}

}
*/

void SE_sprite_draw_fx(SE_sprite *spr,float posx,float posy,float posz,float width,float height,float zoomx,float zoomy,float rotx,float roty,float rotz,float r,float g,float b,float alpha)
{
	float offsetx = spr->offsetx;
	float offsety = spr->offsety;
	SE_animator_draw_fx(spr->ator,offsetx + posx,offsety + posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);

}

void SE_sprite_draw(SE_sprite *spr,float posx,float posy,float posz,float width,float height)
{

	SE_sprite_draw_fx(spr,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);

}

void SE_sprite_draw_transf(SE_sprite *spr,SE_transf *tr)
{

	SE_sprite_draw_fx(spr,
					  tr->x,tr->y,tr->z,
					  tr->width,tr->height,
					  tr->zoomx,tr->zoomy,
					  tr->rotx,tr->roty,tr->rotz,
					  tr->r,tr->g,tr->b,tr->alpha);
					  

}


