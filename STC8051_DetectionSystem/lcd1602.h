#ifndef _LCD1602_H
#define _LCD1602_H

#include <reg51.h>
#include "sys.h"

/* �����������η��ض��� */
#define uint8 unsigned char
#define uint16 unsigned int
	
/* LCD1602�Ĵ�����ַ��ַ */
#define BUSY 0x88

/* LCD1602 Ӳ���ӿ����� */
#define LCD_DATA P0
sbit LCD_RW = P2^1;
sbit LCD_RS = P2^0;
sbit LCD_EN = P2^2;

/* LCD1602 ���ú������� */
#define LCD_DelayMs(x) delay_ms(x)
#define LCD_DelayUs(x) delay_us(x)

void LCD1602_Init(void);
void LCD1602_DisplayChar(uint8 x, uint8 y, uint8 DisplayChar);
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 code *String);
void LCD1602_Clear(void);

static void LCD1602_WriteCmd(uint8 cmd, uint8 BusyFlag);
static void LCD1602_WriteData(uint8 DisplayData);
static uint8 LCD1602_ReadData(void);
static uint8 LCD1602_ReadBusy(void);
#endif