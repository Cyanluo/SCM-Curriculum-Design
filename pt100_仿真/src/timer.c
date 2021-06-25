#include"timer.h"

timer_desc t_event[TEVENT];
uchar T_H = (uint)(65536 - time_t/ft) / 256;
uchar T_L = (uint)(65536 - time_t/ft) % 256;

uint times = 1;  // T = times * time_t ms
uchar time_count = 1;

static void timer0_handle()
{
	int i;
	for(i = 0; i < TEVENT; i++)
	{
		if(t_event[i].fp)
		{
			t_event[i].fp();
		}
	}
}

// time : ms 50µÄ±¶Êý
void timer0_init(uint time)
{
	times = time / time_t;
	EA 	= 1;
	ET0 = 1;
	TMOD = 0x01;
	TH0 = T_H;  // 50ms
	TL0 = T_L;
	TR0 = 1;
}

void set_time(uint time)
{
	times = time / time_t;
	time_count = 0;
}

int tevent_register(char * name, ptimer fp)
{
	int i;
	for(i = 0; i < TEVENT; i++)
	{
		if(!t_event[i].fp)
		{
			t_event[i].fp = fp;
			t_event[i].name = name;
			return 0;
		}
	}
	return -1;
}

void time() interrupt 1
{
	TH0 = T_H;
	TL0 = T_L;
	if(time_count >= times)
	{
		time_count = 1;

		timer0_handle();
	}
	else
	{
		time_count++;
	}
}
