#include "lcd1602.h"
#include "DHT11.h"


/**
 * 从LCD1602读取数据
 * @param   
 * @return 
 * @brief 
 **/
uint8 LCD1602_ReadData(void)
{
	LCD_RS = 1;
	LCD_RW = 1;
	LCD_EN = 0;
	LCD_EN = 0;
	LCD_DelayUs(200);
	LCD_EN = 1;
	
	return LCD_DATA;
}

/**
 * 检测LCD1602繁忙状态
 * @param   
 * @return 
 * @brief 
 **/
uint8 LCD1602_ReadBusy(void)
{
	LCD_DATA = 0xff;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EN = 0;
	LCD_EN = 0;
	LCD_DelayUs(200);
	LCD_EN = 1;
	
	return (LCD_DATA & BUSY);
}

/**
 * 往LCD1602写指令
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_WriteCmd(uint8 cmd, uint8 BusyFlag)
{
	if(BusyFlag) while(LCD1602_ReadBusy());
	LCD_DATA = cmd;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	LCD_EN = 0;
	LCD_EN = 1;
	LCD_DelayUs(200);
	LCD_EN = 0;
}

/**
 * 往LCD1602写数据
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_WriteData(uint8 DisplayData)
{
	//while(LCD1602_ReadBusy());
	LCD_DATA = DisplayData;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EN = 0;
	LCD_EN = 0;
	LCD_EN = 1;
	LCD_DelayUs(200);
	LCD_EN = 0;
}

/**
 * 初始化LCD1602
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_Init(void)
{
	// 三次显示模式设置,不检测忙信号
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	
	LCD1602_WriteCmd(0x38,0);	//显示模式设置
	LCD1602_WriteCmd(0x08,0); //关闭显示
	LCD1602_WriteCmd(0x01,0); //显示清屏
	LCD1602_WriteCmd(0x06,0); //显示光标移动设置
	LCD1602_WriteCmd(0x0c,0); //显示开及光标设置
	
}

/**
 * 在指定位置显示一个字符
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_DisplayChar(uint8 x, uint8 y, uint8 DisplayChar)
{
	// 限制x不能大于15, y不能大于1
	y &= 0x01;
	x &= 0x0f;
	// 当要显示第二行时地址码+0x40
	if(y) x |= 0x40;
	x |= 0x80;	//算出地址码
	LCD1602_WriteCmd(x,0);
	LCD1602_WriteData(DisplayChar);
}

/**
 * 在指定位置开始显示字符串
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 *String)
{
	if (y == 0) 
	{     
		LCD1602_WriteCmd(0x80 + x,0);     //表示第一行
	}
	else 
	{      
		LCD1602_WriteCmd(0xC0 + x,0);      //表示第二行
	}        
	while (*String) 
	{     
		LCD1602_WriteData(*String);     
		String ++;     
	}
}

void LCD1602_DisplayData(DHT11Data_Type *pp)
{
	char tmp[10];
	u8 count;
	
	/* 显示湿度 */
	// 显示湿度整数位
	count = my_itoa(pp->RH_H,tmp);
	LCD1602_WriteCmd(0xC0 + 7,0);
	if(count==1)
	{
		LCD1602_WriteData(' ');
		LCD1602_WriteData(tmp[0]);
	}
	else
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(tmp[1]);
	}
	// 显示湿度小数位
	count = my_itoa(pp->RH_L,tmp);
	LCD1602_WriteCmd(0xC0 + 10,0);
	if(count==1)
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(' ');
	}
	else
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(tmp[1]);
	}
	/* 显示温度部分 */
	// 显示温度整数
	count = my_itoa(pp->T_H,tmp);
	LCD1602_WriteCmd(0x80 + 7,0);
	if(count==1)
	{
		LCD1602_WriteData(' ');
		LCD1602_WriteData(tmp[0]);
	}
	else
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(tmp[1]);
	}
	// 显示温度小数
	count = my_itoa(pp->T_L,tmp);
	LCD1602_WriteCmd(0x80 + 10,0);
	if(count==1)
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(' ');
	}
	else
	{
		LCD1602_WriteData(tmp[0]);
		LCD1602_WriteData(tmp[1]);
	}
	
}


/**
 * 清屏
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_Clear(void)
{
	LCD1602_WriteCmd(0x01,0);
	LCD1602_WriteCmd(0x02,0);
}