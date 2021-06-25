#include "reg51.h"
#include "1602.h"
#include "dev_l298n.h"
#include "ds18b20.h"
#include "timer.h"

sbit BEEP = P2^3;
sbit LED  =	P1^3;

sbit key1 = P3^0;
sbit key2 = P3^1;
sbit key3 = P3^2;
sbit Key_g = P3^7;

bit led_flag = 0;

uint h_threshold = 28, l_threshold = 25;
uchar threshold_flag = 0;

enum KEY_MODE
{
	NORMAL,
	HIGH_THRESHOLD,
	LOW_THRESHOLD
} key_mode = NORMAL;

void LED_F()
{
	static uchar count = 0;

	if(led_flag && ( count++ >= 100))
	{
		count = 0;
		LED = LED == 1 ? 0 : 1;
	}
}

void disp_threshold()
{
	write_com(0x0c);
	write_string(0x80 + 0x40, "L:");
	display_1602(0, l_threshold*10);
	write_dat(0xDF);
	write_dat(0x43);
	write_string(0, "H:");
	display_1602(0, h_threshold*10);
	write_dat(0xDF);
	write_dat(0x43);	
}

void keydscan() 
{
	Key_g = 0;
	key1 = 1;
	key2 = 1;
	key3 = 1;
	
	if(key1==0)
	{
		delay2(5);
		if(key1==0)
		{
			switch(key_mode)
			{
				case NORMAL:
					key_mode = LOW_THRESHOLD;
					break;
				case LOW_THRESHOLD:
					key_mode = HIGH_THRESHOLD;
					break;
				case HIGH_THRESHOLD:
					key_mode = NORMAL;
					break;
			}
			while(!key1);					
		}
	}
	if(key2==0)
	{
		delay2(5);
		if(key2==0)
		{
		   	switch(key_mode)
			{
				case HIGH_THRESHOLD:
					h_threshold++;
					break;
				case LOW_THRESHOLD:
					l_threshold++;
			}
			disp_threshold();
			while(!key2);
		}
	}
	if(key3==0)
	{
		delay2(5);
		if(key3==0)
		{
			switch(key_mode)
			{					
				case HIGH_THRESHOLD:
					h_threshold--;
					break;
				case LOW_THRESHOLD:
					l_threshold--;
			}
			disp_threshold();
			while(!key3);
		}
	}
}

int main()
{	
	float temp = 0, speed = 0;

	init_1602();
	timer0_init(PWM_TIME_TICK);
	l298n_init();
	tevent_register("LED", LED_F);
	tevent_register("KEY", keydscan);
	disp_threshold();

	while(1)
	{
		if(key_mode == NORMAL)
		{
			temp = get_tmp() / 10.0;
		   	
			if(temp > 40)
				continue;

			if(temp <= l_threshold || temp >= h_threshold)
			{
				led_flag = 1;
				BEEP = 0;
				
				if(temp <= l_threshold)
				{
					set_direction(BACKWOARD);
	
					speed = (l_threshold - temp) / l_threshold;				
				}
				else
				{
					set_direction(FOREWARD);
	
					speed = (temp - h_threshold) / h_threshold;
				}
				
				speed > 1 ? set_speed(PWM_T/2) : set_speed(PWM_T * speed/2);	
			}
			else
			{
				led_flag = 0;
	
				LED = 1;
				BEEP = 1;
	
				set_speed(0);
			}
	
			write_string(0x80, "Temp:");
			display_1602(0, temp*10);
			write_dat(0xDF);
			write_dat(0x43);
		}
		else
		{
			stop();
		}

		switch(key_mode)
		{
			case NORMAL:
				write_com(0x0c);
				break;
			case HIGH_THRESHOLD:
				write_com(0x80 + 0x40 + 8);
				write_com(0x0f);
				break;
			case LOW_THRESHOLD:
				write_com(0x80 + 0x40);
				write_com(0x0f);
		}		
	}

	return 0;
}
