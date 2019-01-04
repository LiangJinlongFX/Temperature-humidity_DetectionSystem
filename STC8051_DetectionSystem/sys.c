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
 * 字符串拼接函数
 * @param   *pszDest[目标拼接字符串指针] *pszSrc[源字符串指针]
 * @return  拼接后的字符串指针
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
 * 数值转文本
 * @param   
 * @return 
 * @brief 
 **/
u8 my_itoa (u8 n,char *string)
{
	int i,j,sign,k;
	char s[5];
	if((sign=n)<0)//记录符号
	n=-n;//使n成为正数
	i=0;
	do{
       s[i++]=n%10+'0';//取下一个数字
	}
	while ((n/=10)>0);//删除该数字
	for(j=i-1,k=0;j>=0;j--,k++)//生成的数字是逆序的，所以要逆序输出
       *string++ = s[j];
	*string = '\0';
	
	return k;
}