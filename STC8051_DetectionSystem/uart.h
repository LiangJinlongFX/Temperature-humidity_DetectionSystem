#ifndef _UART_H
#define _UART_H

#include "sys.h"

#define FOSC 11059200L      //System frequency
#define BAUD 115200           //UART baudrate

extern u8 Global_UartBuffer[20];
extern bit Global_UartRev_Flag;
extern unsigned char Global_UartRev_Count;

void Uart_Init(void);
void Uart_SendString(u8 *dat);
void Uart_SendChar(char byte);

#endif