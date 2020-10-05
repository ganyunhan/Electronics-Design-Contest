#ifndef SERVO__H_
#define SERVO__H_

#include "main.h"
#include "tim.h"

void servo_init(void);
void servo_up_reset(void);
void servo_down_reset(void);
void servo_up_speed(int speed);
void servo_down_speed(int speed);
void servo_scan(void);

#endif
