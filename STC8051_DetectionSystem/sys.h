#ifndef _TIME_H
#define _TIME_H

#define u8 		unsigned char
#define u16 	unsigned int
	
void delay_ms(unsigned int x);
void delay_us(unsigned int x);

char* my_strcat(char *pszDest, char *pszSrc);
u8 my_itoa(u8 n,char *string);

#endif