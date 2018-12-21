#include "uart.h"
#include "sys.h"

#include "stc89c5xrc.h"

u8 Global_UartBuffer[20];
bit Global_UartRev_Flag=0;
unsigned char Global_UartRev_Count=0;

void Uart_Init(void)	//115200bps@11.0592MHz
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD = 0x20;
	TH1 = TL1 = 0xFF;
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	TR1 = 1;		//������ʱ��1

	// ʹ�ܴ����ж�
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
		ES = 0;	//ʧ���жϱ���Ӱ��
		RI = 0;	//��������ж�
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