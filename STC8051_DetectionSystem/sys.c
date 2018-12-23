#include "reg51.h"
#include "sys.h"
#include "intrins.h"

static void Delay1ms();		//@22.1184MHz

sbit LED1 = P1^1;

u8 Global_Timer_Flag;

void Timer0_Init(void)	//10����@22.1184MHz
{
	TMOD = 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		  //���ö�ʱ��ֵ
	TH0 = 0xB8;	    //���ö�ʱ��ֵ
	TF0 = 0;		    //���TF0��־
	TR0 = 1;		    //��ʱ��0��ʼ��ʱ
	
	ET0 = 1;		    //������ʱ��0�ж�
}

void delay_ms(unsigned int x)
{
	unsigned int i;
	
	for(i=0;i<x;i++)
		Delay1ms();
}

void delay_us(unsigned int x)
{
	unsigned int i;
	
	for(i=0;i<x;i++)
	{
		_nop_();
	}
}


void Delay1ms()		//@22.1184MHz
{
	unsigned char i, j;

	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j);
	} while (--i);
}

/**
 * �ַ���ƴ�Ӻ���
 * @param   *pszDest[Ŀ��ƴ���ַ���ָ��] *pszSrc[Դ�ַ���ָ��]
 * @return  ƴ�Ӻ���ַ���ָ��
 * @brief 
 **/
char* my_strcat(char *pszDest, char *pszSrc)
{
	while(*pszDest)
		pszDest++;
	while(*pszDest++ = *pszSrc++);
	
	return --pszDest;
}


/**
 * ��ֵת�ı�
 * @param   
 * @return 
 * @brief 
 **/
u8 my_itoa (u8 n,char *string)
{
	int i,j,sign,k;
	char s[5];
	if((sign=n)<0)//��¼����
	n=-n;//ʹn��Ϊ����
	i=0;
	do{
       s[i++]=n%10+'0';//ȡ��һ������
	}
	while ((n/=10)>0);//ɾ��������
	for(j=i-1,k=0;j>=0;j--,k++)//���ɵ�����������ģ�����Ҫ�������
       *string++ = s[j];
	*string = '\0';
	
	return k;
}