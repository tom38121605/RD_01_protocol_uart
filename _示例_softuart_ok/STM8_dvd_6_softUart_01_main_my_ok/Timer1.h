#ifndef __TIMER1_H
#define __TIMER1_H

//#include "stm8s_it.h"
//#include "tim1.h"

void Timer1_Init(uint16 iSplit, uint16 iTimeCount, uint8 iRepeat);        // Timer1 ��ʼ��


__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void);   //Timer1 �жϳ���
void DoWithTimer1(void);       //Timer1�жϷ������

//extern volatile unsigned char flg_Timer1;  //�бȽ�ƥ���жϷ�����־
//extern unsigned long iSecond;              
//extern unsigned char sSecond[10];


extern volatile uint8 iTimeCount;


#endif



