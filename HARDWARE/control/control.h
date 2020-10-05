#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include "mlx90614.h"
#include "stdio.h"
#include "motor.h"
#include "linefinder.h"

extern int speed_set;

int Position_PID_X (float value, float Target);
int Position_PID_Y (float value, float Target);
void Track(void);
void Control_Loop(void);

#endif
