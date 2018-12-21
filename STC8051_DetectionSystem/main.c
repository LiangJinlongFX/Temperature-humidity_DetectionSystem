#include "sys.h"
#include "uart.h"
#include "DHT11.h"
#include "lcd1602.h"
#include "stc89c5xrc.h"

u8 Global_LinkID;
u8 Global_RevDataSize;
DHT11Data_Type Global_DHT11Structure;
sbit LED = P1^1;
sbit Switch = P1^7;

void Response_Process(char Request_Type);

void main(void)
{
	char Request_Type;
	char tmp[10];
	u8 temp;
	
	// ��ʼ��LCD1602
	LCD1602_Init();
	// ��ʼ������
	Uart_Init();
	// ��ʼ����ʱ��0
	//Timer0_Init();
	// ����ȫ���ж�
	EA = 0;
	
	LCD1602_DisplayString(3,1,"hello");
	
	//delay_ms(3000);
	Uart_SendString("AT+CIPMUX=1\r\n");	//ʹ��TCP������
	delay_ms(100);
	Uart_SendString("AT+CIPSERVER=1,8000\r\n");	//����TCP������,�����˿�8000
	delay_ms(100);
	Uart_SendString("AT+CIPSTO=600\r\n");	//������ʱʱ��
	delay_ms(100);
	while(1)
	{
//		if(Global_UartRev_Flag)
//		{
//			Global_UartRev_Flag = 0;	//��λ���ձ��
//			Global_LinkID = Global_UartBuffer[7] - '0';	//��ȡ����Ŀͻ���ID
//			Request_Type = Global_UartBuffer[11];		//��ȡ��������
//			Response_Process(Request_Type);
//			Global_UartRev_Count = 0;	//����������
//			ES = 1;
//		}
		temp = DHT11_ReadData(&Global_DHT11Structure);
		if(!temp)
		{
			my_itoa(Global_DHT11Structure.RH_H,tmp);
			Uart_SendString(tmp);
			Uart_SendChar('.');
			my_itoa(Global_DHT11Structure.RH_L,tmp);
			Uart_SendString(tmp);
			Uart_SendString("%\r\n");
			my_itoa(Global_DHT11Structure.T_H,tmp);
			Uart_SendString(tmp);
			Uart_SendChar('.');
			my_itoa(Global_DHT11Structure.T_L,tmp);
			Uart_SendString(tmp);
			Uart_SendString("*C\r\n");
		}
		delay_ms(2000);
//		LCD1602_DisplayString(3,1,"hello");
	}
}

void Response_Process(char Request_Type)
{
	char payload[10];
	
	if(Request_Type == 1)
	{
		payload[0] = 0x01;	//��Ӧ��������
		payload[1] = 0x01;	//ʪ������λ
		payload[2] = 0x02;	//ʪ��С��λ
		payload[3] = 0x03;	//�¶�����λ
		payload[4] = 0x04;	//�¶�С��λ
		payload[5] = 0x88;	//��ʪ��У��λ
		payload[6] = 0x00;	//����ַ�'\0'
		Uart_SendString("AT+CIPSEND=");
		Uart_SendChar(Global_LinkID+'0');
		Uart_SendString(",6\r\n");
		delay_ms(50);
		Uart_SendString(payload);
	}
	else if(Request_Type == 2)
	{
		Switch = ~Switch;
		payload[0] = 0x01;	//��Ӧ��������
		if(Switch)
			payload[1] = 2;
		else
			payload[1] = 1;
		payload[2] = 0x00;	//����ַ�'\0'
		Uart_SendString("AT+CIPSEND=");
		Uart_SendChar('0'+Global_LinkID);
		Uart_SendString(",2\r\n");
		delay_ms(50);
		Uart_SendString(payload);
	}
}
