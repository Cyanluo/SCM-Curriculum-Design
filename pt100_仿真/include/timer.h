#ifndef _TIMER_H_
#define _TIMER_H_
#include "reg51.h"

//--------config--------
#define TEVENT 3
#define fosc  12	 // M
#define time_t 1 		 // ms
//----------------------

#define NULL ((void *)0)
#define tcy	((1.0/fosc*12)/1000)

typedef void(*ptimer)(void);
typedef struct timer_desc{
	char   *name;
	ptimer fp ;
}timer_desc;
extern timer_desc t_event[TEVENT];

void timer0_init(uint time);
void set_time(uint time);
int tevent_register(char * name, ptimer fp);
#endif

