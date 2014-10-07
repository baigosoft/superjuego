#include "pieces.h"




int pieces[7][4][25] =
{
	{
		/*pieza I*/
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,1,1,1,1,
		 0,0,0,0,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0},
	
		{0,0,0,0,0,
		 0,0,0,0,0,
		 1,1,1,1,0,
		 0,0,0,0,0,
		 0,0,0,0,0},
	
		{0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,0,0,0}
	},
	{
		/*pieza cuadrado*/
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,2,2,0,
		 0,0,2,2,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,2,2,0,
		 0,0,2,2,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,2,2,0,
		 0,0,2,2,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,2,2,0,
		 0,0,2,2,0,
		 0,0,0,0,0}
	},
	{
		/*pieza n*/
		{0,0,0,0,0,
		 0,0,0,3,0,
		 0,0,3,3,0,
		 0,0,3,0,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,3,3,0,0,
		 0,0,3,3,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,3,0,0,
		 0,3,3,0,0,
		 0,3,0,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,3,3,0,0,
		 0,0,3,3,0,
		 0,0,0,0,0,
		 0,0,0,0,0}
	},
	{
		/*pieza n invertida*/
		{0,0,0,0,0,
		 0,0,4,0,0,
		 0,0,4,4,0,
		 0,0,0,4,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,4,4,0,
		 0,4,4,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,4,0,0,0,
		 0,4,4,0,0,
		 0,0,4,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,4,4,0,
		 0,4,4,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0}
	},
	{
		/*pieza L*/
		{0,0,0,0,0,
		 0,0,5,0,0,
		 0,0,5,0,0,
		 0,0,5,5,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,5,5,5,0,
		 0,5,0,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,5,5,0,0,
		 0,0,5,0,0,
		 0,0,5,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,0,5,0,
		 0,5,5,5,0,
		 0,0,0,0,0,
		 0,0,0,0,0}
	},
	{
		/*pieza L invertida*/
		{0,0,0,0,0,
		 0,0,6,0,0,
		 0,0,6,0,0,
		 0,6,6,0,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,6,0,0,0,
		 0,6,6,6,0,
		 0,0,0,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,6,6,0,
		 0,0,6,0,0,
		 0,0,6,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,6,6,6,0,
		 0,0,0,6,0,
		 0,0,0,0,0}
	},
	{
		/*pieza T*/
		{0,0,0,0,0,
		 0,0,7,0,0,
		 0,0,7,7,0,
		 0,0,7,0,0,
		 0,0,0,0,0},	

		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,7,7,7,0,
		 0,0,7,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,7,0,0,
		 0,7,7,0,0,
		 0,0,7,0,0,
		 0,0,0,0,0},
	
		{0,0,0,0,0,
		 0,0,7,0,0,
		 0,7,7,7,0,
		 0,0,0,0,0,
		 0,0,0,0,0}
	}
};/*piezas*/





void draw_tile(int numtile,float posx,float posy,float posz,int width,int height,float alpha)
{

	switch(numtile)
	{
		case 0:
			SE_image_segment_draw_fx(images,0,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;	
		case 1:
			SE_image_segment_draw_fx(images,16,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;
		case 2:
			SE_image_segment_draw_fx(images,32,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;
		case 3:
			SE_image_segment_draw_fx(images,48,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;	
		case 4:
			SE_image_segment_draw_fx(images,64,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;
		case 5:
			SE_image_segment_draw_fx(images,96,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;	
		case 6:
			SE_image_segment_draw_fx(images,112,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;	
		case 7:
			SE_image_segment_draw_fx(images,128,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;
		default:
			SE_image_segment_draw_fx(images,0,0,16,16,posx,posy,posz,width,height,1,1,0,0,0,1,1,1,alpha);
			break;	
	}

}







