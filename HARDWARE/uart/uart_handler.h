#ifndef UART_HANDLER_H_
#define UART_HANDLER_H_

#include "main.h"
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"

void Uart_Get(void);
void Uart_DataProcess(void);
void Get_Value(unsigned char* ucFlag);//��ȡVL53L0����
#endif
