#include "DHT11.h"

/**
 * DH11温湿度读取函数
 * @param DHT11Data_Type 
 * @return 0--正确
 * @brief 
 **/
u8 DHT11_ReadData(DHT11Data_Type DHT11Data_Structure)
{
	 u8 i=0,temp;	
	 u8 U8RH_data_H_temp;
	 u8 U8RH_data_L_temp;
	 u8 U8T_data_H_temp;
	 u8 U8T_data_L_temp;
	 u8 U8checkdata_temp;
	
   //主机拉低18ms 
	 DHT11_BUS = 0;
   DHT11_Delay_ms(18);
   DHT11_BUS = 1;
	 //总线由上拉电阻拉高 主机延时20us以上
	 DHT11_Delay_us(40);
	 //主机设为输入 判断从机响应信号 
   DHT11_BUS = 1;
   //判断从机是否发出 80us 的低电平响应信号,超时则判断读取失败	 
   while(DHT11_BUS)
	 {
			i++;
			DHT11_Delay_us(1);
			//超时退出
			if(i>100)
				return 1;		 
	 }
   //判断从机是否发出 80us 的高电平响应信号,超时则判断读取失败	
   i=0;
	 while(!DHT11_ReadBus())
	 {
			i++;
			DHT11_Delay_us(1);
			//超时退出
			if(i>100)
				return 1;		 
	 }
	 
   //数据接收状态		 
   U8RH_data_H_temp=DHT11_COM();
   U8RH_data_L_temp=DHT11_COM();
   U8T_data_H_temp=DHT11_COM();
   U8T_data_L_temp=DHT11_COM();
   U8checkdata_temp=DHT11_COM();
   DHT11_BUS = 1;
   
	 //数据校验 
   temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
   if(temp==U8checkdata_temp)
   {
   	  DHT11Data_Structure.RH_H=U8RH_data_H_temp;
   	  DHT11Data_Structure.RH_L=U8RH_data_L_temp;
	    DHT11Data_Structure.T_H=U8T_data_H_temp;
   	  DHT11Data_Structure.T_L=U8T_data_L_temp;
		 
		  return 0;
   }
	 else
	 {
		  return 1;
	 }

}

/**
 * DH11总线读取函数
 * @param   
 * @return 0xff--读取异常
 * @brief 从单总线读取到的一字节数据
 **/

u8 DHT11_COM(void)
{
	u8 i,j=0;
	u8 temp;
	u8 comdata;
	
	for(i=0;i<8;i++)
	{
		//等待变为高电平
		while(!DHT11_BUS)
		{
			j++;
			DHT11_Delay_us(1);
			//超时退出
			if(j>100)
				return 0xff;
		}
		DHT11_Delay_us(30);
		temp=0;
		//仍保持高电平,则判断为1
		if(DHT11_BUS)
			temp=1;
		j=0;
		while(DHT11_BUS)
		{
			j++;
			DHT11_Delay_us(1);
			//超时退出
			if(j>100)
				return 0xff;		
		}
		comdata<<1;
		comdata|=temp;
	}
	
	return comdata;
}