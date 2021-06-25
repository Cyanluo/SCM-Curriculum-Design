#ifndef __L298N_H_
#define __L298N_H_

#include "reg51.h"

#define PWM_T 50		// real_time = PWM_T * PWM_TIME_TICK
#define PWM_TIME_TICK 5  // ms
#define FOREWARD 1
#define BACKWOARD 2

sbit IN1 = P2^4;
sbit IN2 = P2^5;
sbit PWM = P2^6;

void l298n_init();
void set_direction(uchar dir);
void set_speed(uchar spd);
void stop();

#endif