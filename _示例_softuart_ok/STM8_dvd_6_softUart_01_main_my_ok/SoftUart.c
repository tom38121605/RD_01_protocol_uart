#include "STM_Config.h"


volatile uint8 iRec;
volatile uint8 iBitCount;


uint8 f_Start1;   //���յ�1����ʼ�ֽ�
uint8 f_End1;     //���յ�1�������ֽ�
uint8 f_End2;     //���յ�2�������ֽ�


//��������
uint8 iRecData[SOFTRX_SIZE];
uint8 iRecData2[SOFTRX_SIZE];
uint16 iRecNum;
uint16 iRecNum2;
uint8 flg_Reced;   //�ѽ�����һ֡����



//ģ�⴮�ڳ�ʼ��
void SoftUart_Init()
{
   //��ʱ52us, ������19200 
   Timer1_Init(DIV_19200,COUNT_19200,0);    
   
   //ģ�⴮��IO��ʼ��
   SoftUart_IOInit(); 
   
   //ģ�⴮�ڽ��ղ�����ʼ��
   SoftUart_RXInit();   
}
   
//ģ�⴮�ڽ��ն˿ڳ�ʼ��  PD2--���жϵ����ݶ˿�
void SoftUart_IOInit()   
{
   //����PD3Ϊ����������, �����ⲿ�ж�     --RX
   //PD_DDR|=(0<<3);   // �������ݷ���Ĵ��� 1--�����0--����
   PD_DDR&=~(0<<3);   // �������ݷ���Ĵ��� 1--�����0--����
   PD_CR1|=(1<<3);   // ���ô�������������   
   PD_CR2&=~(1<<3);   // �����ⲿ�ж�   
   
   
   //����PD2Ϊ����������, ��ʼ�ߵ�ƽ  --TX
   PD_DDR|=(1<<2);   // �������ݷ���Ĵ��� 1--�����0--���� 
   PD_CR1|=(1<<2);   // ����������� 
   PD_CR2|=(1<<2);   // �������Ƶ�� 1--10M(Fast)��0--2M
   PD_ODR|=(1<<2);   // ���ó�ʼ��ƽΪ�ߵ�ƽ 
    
}

//ģ�⴮�ڽ��ղ�����ʼ��
void SoftUart_RXInit()   
{
   iRecNum=0;
   f_Start1='f';
   f_End1='f';
   f_End2='f';
    
}

// Timer1 ��ʼ��
void Timer1_Init(uint16 iSplit, uint16 iCount, uint8 iRepeat)  
{  
   //flg_Timer1=0; 
   
   //iTimeCount =0;

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
   //TIM1_IER |= (1<<0);
   
   //ʹ�ܶ�ʱ��  --�򿪶�ʱ�� 
   //TIM1_CR1 |= (1<<0);
   
}  


//ģ�⴮�ڽ����½����ж�           
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{
   
   //  ------------ �ر��ⲿ�ж� -----------------

   PD_CR2&=~(1<<3);   // ��ʱ�ر��ⲿ�ж�   


   //  ------------ ������ʱ���ж� -----------------
   
   //������������
   //TIM1_ARRH = (uint8)(iCount >> 8);
   TIM1_ARRL = (uint8)(78);
   
   TIM1_IER |= (1<<0); //��������ж� 
   TIM1_CR1 |= (1<<0); //�򿪶�ʱ��     
   
   //  ------------ ��ʼbit���� -----------------
   iBitCount=0;
   
}

//ģ�⴮�ڽ����ַ���
void SoftUart_Receive()  // �������ݰ�: AT#CW10086 0D 0A (���� 10086)  //���: AT#CW10086 0D 0A
{   
      //�����ģ�����
      if( ( PD_IDR & (1<<3) )==0    )
      {
         
         //PA_ODR &= ~(1<<3);         
         Delay_52us();   
         Delay_5us();   
         
         //����1���ַ�
         for(iBitCount=1; iBitCount<9; iBitCount++) 
         { 
            iRec>>=1; 

            if(  PD_IDR & (1<<3)   )
               iRec|=0X80; 
        
            //PA_ODR ^= (1<<3);
            Delay_52us();   
         }   
         
         //��Ч���ݵĴ���
         if(f_Start1=='f' && iRec!=SOFTUART_RX_START1) return ;
         
         //���յ�1���ֽ�
         if(iRec==SOFTUART_RX_START1 && f_Start1=='f') 
         {
            f_Start1='t';
            iRecData[iRecNum]=iRec;
            iRecNum++;
            
            return;
         }
         
         //��ʼ����ָ����������
         if(f_Start1=='t')  
         {
            iRecData[iRecNum]=iRec;
            iRecNum++;
            
            if (iRec==SOFTUART_RX_END1 && f_End1=='f')
            {
               f_End1='t';
               return ;
            }
            if (iRec==SOFTUART_RX_END2 && f_End2=='f')
            {
               iRecNum2=iRecNum;
               memcpy(iRecData2,iRecData,iRecNum);
               flg_Reced=1;
            
               //iRecNum=0;
               //f_Start1='f';
               //f_End1='f';
               //f_End2='f';
               SoftUart_RXInit();
            }  
           
         }         

      }  //if( ( PD_IDR & (1<<2) )==0    )
           
}


//ģ�⴮�ڽ��ն�ʱ��Timer1�ж�
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
   iBitCount++; 

   if(iBitCount<9) 
   { 
      iRec>>=1; 

      if( !( PD_IDR & (1<<3) )  )
         iRec|=0X80; 
   } 
   
   //RX_data1[RX_counter1] = iRec; 
   //RX_counter1++;        // Increment counter  
   //if (RX_counter1 >= 14)  
   //{  
   //   RX_data1[12]=0; 
   //   puts( RX_data1,12);  //����һӲ�����������PC 
   //   RX_counter1 = 0; 
   //} 
   
   //SoftUart_PutChar(iRec);
   
   
   Uart1_PutChar(iRec);
   

   //TIMSK&=~(1<<TOIE2);   //close  
   //GICR|= (1<<6);      //ʹ��int0�ж� 

   //������������
   //TIM1_ARRH = (uint8)(iCount >> 8);
   TIM1_ARRL = (uint8)(52);   
   
   
   TIM1_IER &= ~(1<<0);   //����������ж� 
   TIM1_CR1 &= ~(1<<0);   //�رն�ʱ���ж�   
   
   PD_CR2|=(1<<3);        // ���ⲿ�ж�   
   
   iBitCount=0; 
   
}


//ģ�⴮������ַ�
void SoftUart_PutChar(uint8 cSend)     
{

   //�����ģ�ⷢ��1���ַ�      
   //������ʼλ
   PD_ODR &= ~(1<<2);

   //PA_ODR &= ~(1<<3);         
   Delay_52us();  

   for(iBitCount=1; iBitCount<9; iBitCount++) 
   {  
      if ( cSend& 0x01 )
         PD_ODR |= (1<<2);
      else
         PD_ODR &= ~(1<<2);           
   
      cSend>>=1; 

      //PA_ODR ^= (1<<3);
      Delay_52us();   
   }  

   //����ֹͣλ
   PD_ODR |= (1<<2);   
   Delay_52us();  

}


//ģ�⴮������ַ���
void SoftUart_Puts(uint8 *s)       
{
   while (*s)
   {
      SoftUart_PutChar(*s++);
   }
  
}

//ģ�⴮������ֽ�
void SoftUart_PutBytes(uint8 *s, uint16 ilen)  
{
   unsigned int i;
   
   for(i=0;i<ilen;i++)
   {
      SoftUart_PutChar(*s++);
   }
   
}


/*//����ģ�⴮�ڽ��գ�ͨ���ŵ���������
void DoWithSoftUart(void)        
{
  ; 
 
}
*/