#ifndef __PT100_H_
#define __PT100_H_

#include "reg51.h"

#define R3 10.0
#define R4 100.0
#define I  2.5    //恒流源电流 ma
#define K  ((R3 + R4) / R3)

// u_out mv
float calc_pt100res(uint u_out);
uint median(uint* dat, uchar num_d);
float temperature(uint* u_out, uchar num);
bit get_sign();

#endif
