#ifndef __ADC0804_H_
#define __ADC0804_H_

#include "reg51.h"
#include<intrins.h>

#define dataIO P2

sbit adrd = P1^1;
sbit adwr = P1^2;
sbit adcs = P1^0;

uint ad_read();

#endif