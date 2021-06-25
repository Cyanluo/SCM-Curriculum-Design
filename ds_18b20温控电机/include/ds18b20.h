#ifndef _DS18B20_H_
#define _DS18B20_H_
 
#define uchar unsigned char
#define uint unsigned int

void delay(uint count);
void dsreset(void);
bit tmpreadbit(void);
uchar tmpread(void);
void tmpwritebyte(uchar dat);
void tmpchange(void);
uint tmp();
uint get_tmp();

#endif
