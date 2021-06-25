#include "reg51.h"
#include "1602.h"

uchar dig_convert(uint d, uint* ret)
{
	if(d <= 999)
	{
		ret[0] = d/100;
		ret[1] = d/10%10;
		ret[2] = d%10;

		return 0;
	}
	else
	{
		ret[0] = d/1000;
		ret[1] = d/100%10;
		ret[2] = d/10%10;
		ret[3] = d%10;

		return 1;
	}
}

void display_1602(uchar pos, uint v)
{	
	uint da[4];
	uchar flag;
	if(pos != 0)
		write_com(pos);

	flag = dig_convert(v, da);
	write_dat(0x30 + da[0]);
	write_dat(0x30 + da[1]);
	
	if(flag)
	{
		write_dat(0x30 + da[2]);
		write_dat('.');
		write_dat(0x30 + da[3]);
	}
	else
	{
		write_dat('.');
		write_dat(0x30 + da[2]);
	}
}

void write_string(uchar pos, const char* str)
{
	if(pos != 0)
		write_com(pos);
	
	while(*str)
	{
		write_dat(*str);
		
		str++;
	}
}

void delay2(uint z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_dat(uchar dat)
{
	lcden=0;
	lcdrs=1;
	P0=dat;
	delay2(5);
	lcden=1;
	delay2(5);
	lcden=0;
	lcdrs=0;
}

void write_com(uchar com)
{
	lcden=0;
	lcdrs=0;
	P0=com;
	delay2(5);
	lcden=1;
	delay2(5);
	lcden=0;
}

void init_1602()
{
	dula=0;
	wela=0;	
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80+0x00);
}