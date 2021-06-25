#include "adc0804.h"

uint ad_read()
{
	uint v;	
	adcs = 0;
	adwr = 1;
	_nop_();
	adwr = 0;
	_nop_();
	adwr = 1;
	dataIO=0xff;						 
	adrd = 1;
	_nop_();
	adrd = 0;
	_nop_();
	v = dataIO;
	adrd = 1;
	v = (v/255.0)*5000;

	return v;
}
