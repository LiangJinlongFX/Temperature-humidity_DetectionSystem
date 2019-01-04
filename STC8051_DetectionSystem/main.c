#include "sys.h"
#include "uart.h"
#include "DHT11.h"
#include "lcd1602.h"
#include "stc89c5xrc.h"

u8 TimerISR_Count=0;
u8 Global_LinkID;
u8 Global_RevDataSize;
DHT11Data_Type Global_DHT11Structure;
sbit Switch = P2^3;
void Response_Process(char Request_Type,DHT11Data_Type *pp);

void main(void)
{
	char Request_Type;
	u8 temp;
	unsigned long i=0;
	
	// 初始化LCD1602
	LCD1602_Init();
	// 初始化串口
	Uart_Init();
	// 串口中断设置为最高优先级
	PS = 1;
	// 开启全局中断
	EA = 1;
	
	// 显示启动信息
	LCD1602_DisplayString(5,0,"Welcome");
	LCD1602_DisplayString(3,1,"ChenJiandong");
	
	// AT指令设置ESP8266 TCP Server
	delay_ms(3000);
	Uart_SendString("ATE0\r\n");	//关闭指令回显
	delay_ms(100);
	Uart_SendString("AT+CIPMUX=1\r\n");	//使能TCP多连接
	delay_ms(100);
	Uart_SendString("AT+CIPSERVER=1,8000\r\n");	//建立TCP服务器,监听端口8000
	delay_ms(100);
	Uart_SendString("AT+CIPSTO=600\r\n");	//建立超时时间
	delay_ms(100);
	
	// 显示温湿度显示界面
	LCD1602_Clear();
	LCD1602_DisplayString(2,0,"TEMP:  .  ^C");
	LCD1602_DisplayString(3,1,"RH :  .  %");
	while(1)
	{
		if(Global_UartRev_Flag)
		{
			Global_UartRev_Flag = 0;	//复位接收标记
			Global_LinkID = Global_UartBuffer[7] - '0';	//获取请求的客户端ID
			Request_Type = Global_UartBuffer[11];		//获取请求类型
			Response_Process(Request_Type,&Global_DHT11Structure);
			Global_UartRev_Count = 0;	//清除缓冲计数
			ES = 1;
		}
		i++;
		if(i>50000)
		{
			i=0;
			temp = DHT11_ReadData(&Global_DHT11Structure);
			if(!temp)
			{
//				Response_Process(1,&Global_DHT11Structure);
				LCD1602_DisplayData(&Global_DHT11Structure);
			}
		}
	}
}

void Response_Process(char Request_Type,DHT11Data_Type *pp)
{
	char payload[10];
	
	if(Request_Type == 1)
	{
		payload[0] = 0x88;	//响应数据类型
		payload[1] = pp->T_H;	//湿度整数位
		payload[2] = pp->T_L;	//湿度小数位
		payload[3] = pp->RH_H;	  //温度整数位
		payload[4] = pp->RH_L;	  //温度小数位
		payload[5] = 23;	//温湿度校验位
		payload[6] = 0x00;	//填充字符'\0'
		Uart_SendString("AT+CIPSEND=");
		Uart_SendChar(Global_LinkID+'0');
		Uart_SendString(",6\r\n");
		delay_ms(10);
		//Uart_SendString(payload);
		Uart_SendChar(payload[0]);
		Uart_SendChar(payload[1]);
		Uart_SendChar(payload[2]);
		Uart_SendChar(payload[3]);
		Uart_SendChar(payload[4]);
		Uart_SendChar(payload[5]);
		
	}
	else if(Request_Type == 2)
	{
		Switch = ~Switch;
		payload[0] = 0x89;	//响应数据类型
		if(Switch)
			payload[1] = 2;
		else
			payload[1] = 1;
		payload[2] = 0x00;	//填充字符'\0'
		Uart_SendString("AT+CIPSEND=");
		Uart_SendChar('0'+Global_LinkID);
		Uart_SendString(",2\r\n");
		delay_ms(50);
		Uart_SendString(payload);
	}
}


