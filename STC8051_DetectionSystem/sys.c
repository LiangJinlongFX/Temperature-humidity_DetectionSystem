#include "stc89c5xrc.h"
#include "sys.h"
#include "intrins.h"

static void Delay1ms();		//@22.1184MHz

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