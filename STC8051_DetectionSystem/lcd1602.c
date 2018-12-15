#include "lcd1602.h"


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
	LCD_DATA = 0;
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
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 code *String)
{
	uint8 length=0;
	
	// 限制x不能大于15, y不能大于1
	y &= 0x01;
	x &= 0x0f;
	// 若到达字符串尾则退出
	while(String[length]>=0x20)
	{
		if(x <= 0x0f)
		{
			LCD1602_DisplayChar(x,y,String[length]);
			length++;
			x++;
		}
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