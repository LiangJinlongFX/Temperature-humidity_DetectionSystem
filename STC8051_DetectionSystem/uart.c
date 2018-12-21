#include "uart.h"
#include "sys.h"

#include "stc89c5xrc.h"

u8 Global_UartBuffer[20];
bit Global_UartRev_Flag=0;
unsigned char Global_UartRev_Count=0;

void Uart_Init(void)	//115200bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD = 0x20;
	TH1 = TL1 = 0xFF;
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	TR1 = 1;		//启动定时器1

	// 使能串口中断
	ES = 1;
}

void Uart_SendString(u8 *dat)
{
	while(TI);
	while(*dat != '\0')
	{
		SBUF = *dat;
		dat++;
		while(!TI);
		TI=0;
	}
}

void Uart_SendChar(char byte)
{
	while(TI);
	SBUF = byte;
	while(!TI);
	TI=0;
}

void Uart_ISR_Handler(void) interrupt 4 using 1
{

	if(RI)
	{
		ES = 0;	//失能中断避免影响
		RI = 0;	//清除接收中断
		Global_UartBuffer[Global_UartRev_Count] = SBUF;
		if(Global_UartBuffer[Global_UartRev_Count]=='\0'||Global_UartRev_Count>19)
		{
			if((Global_UartRev_Count>4)&&(Global_UartBuffer[5]=='D'))
			{
				Global_UartRev_Flag = 1;
			}
			else
			{
				Global_UartRev_Count = 0;
				ES = 1;
			}
		}
		else
		{
			Global_UartRev_Count++;
			ES = 1;
		}
	}
}