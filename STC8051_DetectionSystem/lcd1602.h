#ifndef _LCD1602_H
#define _LCD1602_H

#include "stc89c5xrc.h"
#include "sys.h"
#include "DHT11.h"

/* 数据类型修饰符重定义 */
#define uint8 unsigned char
#define uint16 unsigned int
	
/* LCD1602寄存器地址地址 */
#define BUSY 0x88

/* LCD1602 硬件接口配置 */
#define LCD_DATA P0
sbit LCD_RW = P2^6;
sbit LCD_RS = P2^7;
sbit LCD_EN = P2^5;

/* LCD1602 调用函数设置 */
#define LCD_DelayMs(x) delay_ms(x)
#define LCD_DelayUs(x) delay_us(x)

void LCD1602_Init(void);
void LCD1602_DisplayChar(uint8 x, uint8 y, uint8 DisplayChar);
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 *String);
void LCD1602_DisplayData(DHT11Data_Type *pp);
void LCD1602_Clear(void);

static void LCD1602_WriteCmd(uint8 cmd, uint8 BusyFlag);
static void LCD1602_WriteData(uint8 DisplayData);
static uint8 LCD1602_ReadData(void);
static uint8 LCD1602_ReadBusy(void);
#endif