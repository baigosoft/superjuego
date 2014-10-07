#ifndef BALL_H_
#define BALL_H_


typedef struct
{

	int ball_status;
	int ball_width,ball_height;
	int ball_x,ball_y,ball_z;


}ball;


ball *ball_init();
void ball_status_set(ball *b,int status);
void ball_dimentions_set(ball *b,int width,int height);
void ball_x(ball *b,int posx);
void ball_y(ball *b,int posy);
void ball_z(ball *b,int posz);
void ball_clean(ball *b);
















#endif
