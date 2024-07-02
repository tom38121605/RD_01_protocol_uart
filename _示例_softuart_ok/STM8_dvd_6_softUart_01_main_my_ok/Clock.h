#ifndef __CLOCK_H
#define __CLOCK_H


#define   CLK_SOURCE_HSE 0xB4   //外部时钟 ,最大24MHz
#define   CLK_SOURCE_HSI 0xE1   //内部16MHz
#define   CLK_SOURCE_LSI 0xD2   //内部128KHz

#define HSE_LESS_16MHz 0
#define HSE_OVER_16MHz 1

#define   HSECNT_2048CLK 0x00 
#define   HSECNT_128CLK 0xb4 
#define   HSECNT_8CLK 0xd2 
#define   HSECNT_0_5CLK 0xe1 



void Clock_HSE_Ini();
void Clock_HSI_Ini();
//void Clock_LSI_Ini();


#endif

