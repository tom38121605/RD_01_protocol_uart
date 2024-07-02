#ifndef __TIMER1_H
#define __TIMER1_H

//#include "stm8s_it.h"
//#include "tim1.h"

void Timer1_Init(uint16 iSplit, uint16 iTimeCount, uint8 iRepeat);        // Timer1 初始化


__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void);   //Timer1 中断程序
void DoWithTimer1(void);       //Timer1中断服务程序

//extern volatile unsigned char flg_Timer1;  //有比较匹配中断发生标志
//extern unsigned long iSecond;              
//extern unsigned char sSecond[10];


extern volatile uint8 iTimeCount;


#endif



