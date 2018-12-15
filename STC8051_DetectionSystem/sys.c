#include "reg51.h"
#include "sys.h"
#include "intrins.h"

static void Delay1ms();		//@24.000MHz

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
		_nop_();
	}
}


void Delay1ms()		//@24.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 225;
	do
	{
		while (--j);
	} while (--i);
}