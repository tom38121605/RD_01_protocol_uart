
   
#include "STM_Config.h"  

#define TIM1_COUNTERMODE_UP  0x00
#define TIM1_IT_UPDATE       0x01


//unsigned char flg_Timer1;  //有比较匹配中断发生标志
//unsigned long iSecond;              
//unsigned char sSecond[10];

uint8 volatile iTimeCount;

// Timer1 初始化
void Timer1_Init(uint16 iSplit, uint16 iCount, uint8 iRepeat)  
{  
   //flg_Timer1=0; 
   
   iTimeCount =0;

   //=========Timer1寄存器设置============
      
   //计数次数设置
   TIM1_ARRH = (uint8)(iCount >> 8);
   TIM1_ARRL = (uint8)(iCount);


   //预分频设置 
   TIM1_PSCRH = (uint8)(iSplit >> 8);
   TIM1_PSCRL = (uint8)(iSplit);
  
   
   //选择边沿对齐方式
   TIM1_CR1 &= ~( (1<<5)|(1<<6) );
   
   //向上计数设置 
   TIM1_CR1 &= ~(1<<4);    

   
   //重复计数次数设置
   TIM1_RCR = iRepeat;
  
   //计数寄存器初值设置
   TIM1_CNTRH = 0;
   TIM1_CNTRL = 0;   
      
   //预装载不使能 
   //TIM1_CR1 &= ~(1<<7);
   TIM1_CR1 |= (1<<7);
   
   //允许更新中断 
   TIM1_IER |= (1<<0);
   
   //使能定时器   
   TIM1_CR1 |= (1<<0);
   
}  

//Timer1 中断程序
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{     
	//iTimeCount++;
   PD_ODR^= (1<<0);

   
	TIM1_SR1 &= ~(1<<0);  
}


//Timer1中断服务程序
void DoWithTimer1(void)
{
   //iSecond++;
   //Long2Str_10(iSecond,sSecond);     
   //LCD_WriteStrAuto(sSecond);   
   
   //if (iSecond==60) iSecond=0;
}
