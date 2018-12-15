#include "lcd1602.h"


/**
 * ��LCD1602��ȡ����
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
 * ���LCD1602��æ״̬
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
 * ��LCD1602дָ��
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
 * ��LCD1602д����
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
 * ��ʼ��LCD1602
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_Init(void)
{
	LCD_DATA = 0;
	// ������ʾģʽ����,�����æ�ź�
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	LCD1602_WriteCmd(0x38,0);
	LCD_DelayMs(5);
	
	LCD1602_WriteCmd(0x38,0);	//��ʾģʽ����
	LCD1602_WriteCmd(0x08,0); //�ر���ʾ
	LCD1602_WriteCmd(0x01,0); //��ʾ����
	LCD1602_WriteCmd(0x06,0); //��ʾ����ƶ�����
	LCD1602_WriteCmd(0x0c,0); //��ʾ�����������
	
}

/**
 * ��ָ��λ����ʾһ���ַ�
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_DisplayChar(uint8 x, uint8 y, uint8 DisplayChar)
{
	// ����x���ܴ���15, y���ܴ���1
	y &= 0x01;
	x &= 0x0f;
	// ��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40
	if(y) x |= 0x40;
	x |= 0x80;	//�����ַ��
	LCD1602_WriteCmd(x,0);
	LCD1602_WriteData(DisplayChar);
}

/**
 * ��ָ��λ�ÿ�ʼ��ʾ�ַ���
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 code *String)
{
	uint8 length=0;
	
	// ����x���ܴ���15, y���ܴ���1
	y &= 0x01;
	x &= 0x0f;
	// �������ַ���β���˳�
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
 * ����
 * @param   
 * @return 
 * @brief 
 **/
void LCD1602_Clear(void)
{
	LCD1602_WriteCmd(0x01,0);
	LCD1602_WriteCmd(0x02,0);
}