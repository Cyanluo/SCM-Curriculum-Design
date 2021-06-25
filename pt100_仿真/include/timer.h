#ifndef _TIMER_H_
#define _TIMER_H_

#include "reg51.h"

//--------config--------
#define TEVENT 3
#define fos  11.0592	 // M
#define time_t 5 		 // ms
//----------------------

#define NULL ((void *)0)
#define ft	((1.0/fos*12)/1000)

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

