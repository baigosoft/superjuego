#include "sprite.h"




SE_sprite *SE_sprite_init(int type)/*puede ser IMG o ANI*/
{

	SE_sprite *spr;
	spr = (SE_sprite*)malloc(sizeof(SE_sprite));
	spr->type = type;
	if(type > 1) printf("tipo no especificado, debe ser IMG o ANI");
	spr->ator = NULL;
	spr->img = NULL;
	spr->box = NULL;
	spr->numboxes = 0;
	spr->offsetx = 0;
	spr->offsety = 0;

	spr->frbox = NULL;
	spr->numfrboxes = 0;

	return spr;

}

void SE_sprite_img_segment_add(SE_sprite *spr,SE_image *img,float xt,float yt,float wt,float ht)
{
	if(spr->type == IMG)
	{
		spr->img = img;
		spr->xt = xt;
		spr->yt = yt;
		spr->wt = wt;
		spr->ht = ht;
	}else{
		printf("tipo incorrecto, debe ser IMG");
	}

}



void SE_sprite_img_add(SE_sprite *spr,SE_image *img)
{

	if(spr->type == IMG)
	{
		spr->img = img;
		spr->xt = 0;
		spr->yt = 0;
		spr->wt = img->width;
		spr->ht = img->height;
	}else{
		printf("tipo incorrecto, debe ser IMG");
	}

	
}

void SE_sprite_ani_add(SE_sprite *spr,SE_ani *ani)
{

	spr->ator = SE_animator_init(ani);
	
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


void SE_sprite_box_init(SE_sprite *spr,int numboxes)
{

	spr->box = (SE_box*)malloc(numboxes * sizeof(SE_box));
	spr->numboxes = numboxes;

}

void SE_sprite_box_set(SE_sprite *spr,int box_number,float offsetx,float offsety,float width_box,float height_box)
{

		spr->box[box_number].x = offsetx;
		spr->box[box_number].y = offsety;
		spr->box[box_number].w = width_box;
		spr->box[box_number].h = height_box;

}


int SE_sprite_collision_single(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2)
{

	return SE_coll_check_position(&spr1->box[numbox1],&spr2->box[numbox2],posx1,posy1,posx2,posy2);

}

int SE_sprite_collision(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2)
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
			
			coll = SE_sprite_collision_single(spr1,i,spr2,j,posx1,posy1,posx2,posy2);
			if(coll > 0)
			{

				return 1;

			}
		}
	}
	return 0;
}

int SE_sprite_collision_box(SE_sprite *spr,SE_box *box,float posx_spr,float posy_spr,float posx_box,float posy_box)
{
	
	int boxes = spr->numboxes;
	int coll = 0;
	
	int i,j;
	
	for(i = 0;i < boxes;i++)
	{	
		
			/*chequea todas las cajas de sprite 1 con todas las cajas de sprite 2*/
			
			coll = SE_coll_check_position(&spr->box[i],box,posx_spr,posy_spr,posx_box,posy_box);
			if(coll > 0)
			{

				return 1;

			}
		
	}
	return 0;
}


/*void SE_sprite_box_pf_init(SE_sprite *spr,int numboxes)
{

	int i,j;
	int numframes = spr->ator->numframes;
	
	spr->numfrboxes = numboxes;		

	spr->frbox = (SE_box_pf*)malloc(numframes * sizeof(SE_box_pf));

	for(i=0;i < numframes;i++)
	{

		spr->frbox[i].box = (SE_box*)malloc(numboxes * sizeof(SE_box));

		for(j=0;j < numboxes;j++)
		{

			spr->box[j].x = 0;
			spr->box[j].y = 0;
			spr->box[j].w = 0;
			spr->box[j].h = 0;

		} 		

	}


}

void SE_sprite_box_pf_set(SE_sprite *spr,int frame_number,int box_number,float offsetx,float offsety,float width_box,float height_box)
{

		spr->frbox[frame_number].box[box_number].x = offsetx;
		spr->frbox[frame_number].box[box_number].y = offsety;
		spr->frbox[frame_number].box[box_number].w = width_box;
		spr->frbox[frame_number].box[box_number].h = height_box;

}


int SE_sprite_collision_pf_single(SE_sprite *spr1,int frame_number1,int numbox1,
								  SE_sprite *spr2,int frame_number2,int numbox2,
								  float posx1,float posy1,float posx2,float posy2)
{

	return SE_coll_check_position(&spr1->frbox[frame_number1].box[numbox1],&spr2->frbox[frame_number2].box[numbox2],posx1,posy1,posx2,posy2);

}

int SE_sprite_collision_pf_current(SE_sprite *spr1,int numbox1,SE_sprite *spr2,int numbox2,float posx1,float posy1,float posx2,float posy2)
{

	int frame1 = spr1->ator->currentframe;
	int frame2 = spr2->ator->currentframe;

	return SE_sprite_collision_pf_single(spr1,frame1,numbox1,spr2,frame2,numbox2,posx1,posy1,posx2,posy2);
	
}

int SE_sprite_collision_pf(SE_sprite *spr1,SE_sprite *spr2,float posx1,float posy1,float posx2,float posy2)
{

	int boxes1 = spr1->numfrboxes;
	int boxes2 = spr2->numfrboxes;

	int frame1 = spr1->ator->currentframe;
	int frame2 = spr2->ator->currentframe;
	
	int coll = 0;
	
	int i,j;

	for(i = 0;i < boxes1;i++)
	{	
		for(j = 0;j < boxes2;j++)				
		{

			coll = SE_sprite_collision_pf_single(spr1,frame1,i,spr2,frame2,j,posx1,posy1,posx2,posy2);

			if(coll > 0)
			{

				return 1;

			}


		}
	}

	return 0;

}*/


void SE_sprite_clean(SE_sprite *spr)
{
	
	free(spr->box);
	free(spr->ator);
	free(spr->frbox);
	free(spr);
	
	printf("SE_sprite:se elimino puntero de sprite\n");

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

	if(spr->type == IMG)
	{

	//SE_image_draw_fx(spr->img,offsetx + posx,offsety + posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);
		SE_image_segment_draw_fx(spr->img,spr->xt,spr->yt,spr->wt,spr->ht,offsetx + posx,offsety + posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);
					   
	}else if(spr->type == ANI){


		SE_animator_draw_fx(spr->ator,offsetx + posx,offsety + posy,posz,width,height,zoomx,zoomy,rotx,roty,rotz,r,g,b,alpha);
				
	}else{
		printf("tipo debe ser IMG o ANI");
	}
}

void SE_sprite_draw_wh(SE_sprite *spr,float posx,float posy,float posz,float width,float height)
{

	SE_sprite_draw_fx(spr,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,1);

}

void SE_sprite_draw(SE_sprite *spr,float posx,float posy,float posz)
{

	SE_sprite_draw_fx(spr,posx,posy,posz,SE_ani_width(spr->ator->ani),SE_ani_height(spr->ator->ani),1,1,0,0,0,1,1,1,1);

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


