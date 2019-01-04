#ifndef __DHT11_H
#define __DHT11_H

#include "stc89c5xrc.h"
#include "sys.h"

//DHT11检测数据结构体
typedef struct
{
	u8 RH_H;
	u8 RH_L;
	u8 T_H;
	u8 T_L;
	u8 CheckData;
}DHT11Data_Type;

sbit DHT11_BUS = P2^4; 

//延时函数(us)
#define DHT11_Delay_us(time) delay_us(time)
//延时函数(ms)
#define DHT11_Delay_ms(time) delay_ms(time)


u8 DHT11_COM(void);
u8 DHT11_ReadData(DHT11Data_Type *pp);


#endif