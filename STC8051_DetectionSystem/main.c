#include <reg51.h>
#include "lcd1602.h"
#include "sys.h"

void main(void)
{
	LCD1602_Init();
	while(1)
	{
		LCD1602_DisplayString(4,0,"HelloWorld");
		delay_ms(1000);
		LCD1602_Clear();
		LCD1602_DisplayString(2,0,"Liang Jinlong");
		delay_ms(1000);
		LCD1602_Clear();
	}
}