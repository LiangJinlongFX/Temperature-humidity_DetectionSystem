#include "lcd1602.h"
#include "DHT11.h"


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
void LCD1602_DisplayString(uint8 x, uint8 y, uint8 *String)
{
	if (y == 0) 
	{     
		LCD1602_WriteCmd(0x80 + x,0);     //��ʾ��һ��
	}
	else 
	{      
		LCD1602_WriteCmd(0xC0 + x,0);      //��ʾ�ڶ���
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
	
	/* ��ʾʪ�� */
	// ��ʾʪ������λ
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
	// ��ʾʪ��С��λ
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
	/* ��ʾ�¶Ȳ��� */
	// ��ʾ�¶�����
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
	// ��ʾ�¶�С��
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