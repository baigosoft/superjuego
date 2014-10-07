#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <SDL/SDL.h>
#define SE_timems int



/*Estructura para controlar eventos*/
typedef struct{
SE_timems time_start;
SE_timems time_end;

}SE_timer;

/*obtener el tiempo actual (en milisegundos)*/
SE_timems SE_timer_gettime();

/*Resetear timer*/
void SE_timer_reset();

/*Obtener tiempo actual (en milisegundos)*/
SE_timems SE_timer_current();

/*Setear framerate fijo*/
void SE_timer_setframerate(int framespersecond);

/*Esperar para cumplir con el framerate*/
void SE_timer_waitframerate();

/*Crear un timer nuevo*/
SE_timer *SE_timer_start(int time_end);

/*Chequear un timer. Retorna 1 si se sobrepaso el tiempo final y 0 en caso contrario*/
int SE_timer_check(SE_timer *timer);


#endif

