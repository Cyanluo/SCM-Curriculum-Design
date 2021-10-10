#include "dev_l298n.h"
#include "timer.h"

uchar pwm_h = 1;

uchar current = 0;
bit stop_flag = 0;

// dir: 1 Õý  2 ·´
void set_direction(uchar dir)
{	
	switch(dir)
	{
		case FOREWARD:
		{
			IN1 = 1;
			IN2 = 0;
			break;
		}
		case BACKWOARD:
		{
			IN1 = 0;
			IN2 = 1;
			break;
		}
		default:
			break;
	}
}

void pwm()
{
	if(!stop_flag)
	{
		if(current < pwm_h)
		{
			PWM = 1;
		}
		else if(current >= pwm_h && current <= PWM_T)
		{
			PWM = 0;
		}
		else
		{
			PWM = 1;
			current = 0;
		}
		current++;
	}	
}

void l298n_init()
{		
	PWM = 0;
	set_direction(1);
	tevent_register("PWM", pwm);
	stop();	
}

void set_speed(uchar spd)
{
	pwm_h = spd <= PWM_T ? spd : PWM_T;
	current = 0;
	stop_flag = 0;
}

void stop()
{
	PWM = 0;
	IN1 = 0;
	IN2 = 0;
	stop_flag = 1;
}
