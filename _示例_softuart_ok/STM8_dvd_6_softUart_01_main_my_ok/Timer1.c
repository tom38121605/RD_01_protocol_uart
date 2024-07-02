
   
#include "STM_Config.h"  

#define TIM1_COUNTERMODE_UP  0x00
#define TIM1_IT_UPDATE       0x01


//unsigned char flg_Timer1;  //�бȽ�ƥ���жϷ�����־
//unsigned long iSecond;              
//unsigned char sSecond[10];

uint8 volatile iTimeCount;

// Timer1 ��ʼ��
void Timer1_Init(uint16 iSplit, uint16 iCount, uint8 iRepeat)  
{  
   //flg_Timer1=0; 
   
   iTimeCount =0;

   //=========Timer1�Ĵ�������============
      
   //������������
   TIM1_ARRH = (uint8)(iCount >> 8);
   TIM1_ARRL = (uint8)(iCount);


   //Ԥ��Ƶ���� 
   TIM1_PSCRH = (uint8)(iSplit >> 8);
   TIM1_PSCRL = (uint8)(iSplit);
  
   
   //ѡ����ض��뷽ʽ
   TIM1_CR1 &= ~( (1<<5)|(1<<6) );
   
   //���ϼ������� 
   TIM1_CR1 &= ~(1<<4);    

   
   //�ظ�������������
   TIM1_RCR = iRepeat;
  
   //�����Ĵ�����ֵ����
   TIM1_CNTRH = 0;
   TIM1_CNTRL = 0;   
      
   //Ԥװ�ز�ʹ�� 
   //TIM1_CR1 &= ~(1<<7);
   TIM1_CR1 |= (1<<7);
   
   //��������ж� 
   TIM1_IER |= (1<<0);
   
   //ʹ�ܶ�ʱ��   
   TIM1_CR1 |= (1<<0);
   
}  

//Timer1 �жϳ���
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{     
	//iTimeCount++;
   PD_ODR^= (1<<0);

   
	TIM1_SR1 &= ~(1<<0);  
}


//Timer1�жϷ������
void DoWithTimer1(void)
{
   //iSecond++;
   //Long2Str_10(iSecond,sSecond);     
   //LCD_WriteStrAuto(sSecond);   
   
   //if (iSecond==60) iSecond=0;
}
