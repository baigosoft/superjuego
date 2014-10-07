#include "timer.h"

Uint32 ini_mili,fin_mili;
int framerate=17;


int SE_timer_gettime(){
	return SDL_GetTicks();
}


void SE_timer_reset()
{
	ini_mili=SDL_GetTicks();
}


int SE_timer_current()
{
	fin_mili=SDL_GetTicks();
	return fin_mili - ini_mili;
}


void SE_timer_setframerate(int framespersecond)
{
	framerate=1000/framespersecond;

}


void SE_timer_waitframerate()
{
	int ftime;
	int start=SDL_GetTicks();
	/*do {
		ftime=SDL_GetTicks()-start;		
	} while (ftime<framerate);*/
	SDL_Delay(framerate);

}


SE_timer *SE_timer_start(int time_end){
	SE_timer *timer;
	timer=(SE_timer *) malloc(sizeof(SE_timer));
	timer->time_start=SE_timer_gettime();
	timer->time_end=SE_timer_gettime()+time_end;
	
	return timer;
	
}


int SE_timer_check(SE_timer *timer){
	int time;

	if((timer->time_end)>=(timer->time_start)){ 
		free(timer);
		return 1;
	}else{
		return 0;
	}

}
