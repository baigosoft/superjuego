#ifndef BALL_H_
#define BALL_H_


typedef struct
{

	int ball_status;
	int ball_width,ball_height;
	int ball_x,ball_y,ball_z;


}JF_ball;


JF_ball *JF_ball_init(int width,int height,int x,int y,int z);
void JF_ball_status_set(JF_ball *b,int status);
void JF_ball_dimentions_set(JF_ball *b,int width,int height);
void JF_ball_clean(ball *b);
















#endif
