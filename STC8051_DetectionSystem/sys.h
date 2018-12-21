#ifndef _TIME_H
#define _TIME_H

#define u8 		unsigned char
#define u16 	unsigned int
	
extern u8 Global_Timer_Flag;

void Timer0_Init(void);

void delay_ms(unsigned int x);
void delay_us(unsigned int x);

char* my_strcat(char *pszDest, char *pszSrc);
void my_itoa(u8 n,char *string);

#endif