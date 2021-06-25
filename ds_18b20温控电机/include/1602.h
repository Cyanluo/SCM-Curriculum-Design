#ifndef __1602__H
#define __1602__H

sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit lcdrw=P3^6;
sbit wela=P2^7;
sbit dula=P2^6;

void delay2(uint z);
void write_dat(uchar dat);
void write_com(uchar com);
void init_1602();
uchar dig_convert(uint d, uint* ret);
void display_1602(uchar pos, uint v);
void write_string(uchar pos, const char* str);

#endif