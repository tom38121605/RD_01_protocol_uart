#include "STM_Config.h"


uint8 flg_Start1;   //���յ�1����ʼ�ֽ�
uint8 flg_Start2;   //���յ�2����ʼ�ֽ�
uint8 flg_Start3;   //���յ�3����ʼ�ֽ�
uint8 flg_Start4;   //���յ�4����ʼ�ֽ�
uint16 iRX_Sum;

uint8 RX_data[RX_BUFFER_SIZE]={0};
uint8 RX_data2[RX_BUFFER_SIZE]={0};
uint16 iRXNum=0;
uint16 iRXNum2=0;
uint8 flg_Received=0;  //�ѽ��յ���Ч����   


//���ڳ�ʼ������
void Uart1_Init(uint32  iBaudRate)
{
   
   uint32 iBaudDiv=0;
   
   //----------------�Ĵ�����ʼ��---------------------   
   (void)UART1_SR;
   (void)UART1_DR;
    
   UART1_CR1=0;
   UART1_CR2=0;
   UART1_CR3=0;
   UART1_CR4=0;
   UART1_CR5=0;
   UART1_GTR=0;
   UART1_PSCR=0;
   
   Uart_RXInit();
   
   
   //----------------�Ĵ�������---------------------   
   
   //��������λ 8
   UART1_CR1 &= ~(1<<4);   
   
   //����ֹͣλ 1
   UART1_CR3 &= ~( (1<<4)|(1<<5) );      
   
   //������żУ��λ ��
   //UART1_CR1 &= ~( (1<<1)|(1<<2) ); 
   UART1_CR1 &= ~(1<<2) ; 
   

   //���ò�����  (ע���: Ҫ������BRR2, ������BRR1)
   //baud_div =MASTER_FREQ/iBit;  /*�����Ƶ����*/
   iBaudDiv = (uint32)( (float)((float)MASTER_FREQ/(float)iBaudRate *10 + 5)/10 );  //�����Ƶ����
   UART1_BRR2 = iBaudDiv & 0x0f;
   UART1_BRR2 |= ((iBaudDiv & 0xf000) >> 8);
   UART1_BRR1 = ((iBaudDiv & 0x0ff0) >> 4);    //�ȸ�BRR2��ֵ ���������BRR1

   
   //���ô򿪴��ڷ��ͺͽ���
   UART1_CR2 |= (1<<2)|(1<<3);     

   //��SCLK�����ϵ����ʱ���Ƿ�ʹ��  -- ��ʱ������
   //...
   
   //���ô��ڵĽ����ж�ʹ��
   UART1_CR2 |= (1<<5);         
   
   //���ô򿪴��� , 0--��
   UART1_CR1 &= ~(1<<5);
   
}

//���ڽ��ղ�����ʼ��
void Uart_RXInit()   
{
   iRXNum=0;
   iRX_Sum=0;
   
   flg_Start1='f';
   flg_Start2='f';
   flg_Start3='f';
   flg_Start4='f';
    
}

#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)  //���ݰ�: AA 00 03 02 00 04 F7  ���ָ��: 02 00 04
{ 
   uint8 cUartByte;
   uint8 i;
   uint16 iCheckSum;
   //uint16 iFunction;
   
   if( !(UART1_SR & (1<<5)) )  //������ǽ����ж����˳�
      return;
      
   cUartByte=UART1_DR;
   
   //Uart1_PutChar(cUartByte+1);   
   //return;   
   
   if(flg_Start1=='f' && cUartByte!=0xAA) 
      return;
   
   //���յ�1���ֽ�
   if(cUartByte==0xAA && flg_Start1=='f') 
   {
      flg_Start1='t';  
      
//test
      //Uart1_Puts("1");

      return;      
   }
   
   //���յ�2���ֽ�  -- iRx_Sum���ֽ�
   if(flg_Start2=='f' && flg_Start1=='t') 
   {
      flg_Start2='t';
      
//test
      //Uart1_Puts("2");

      //iRx_Sum=cUartByte;
      return;
   }
   
   //���յ�3���ֽ�  -- iRx_Sum���ֽ�
   if(flg_Start3=='f' && flg_Start2=='t') 
   {
      flg_Start3='t';
      
//test
      //Uart1_Puts("3");

      //iRx_Sum=(iRx_Sum<<8)+cUartByte;
      iRX_Sum=cUartByte;
      
      if (iRX_Sum==0)
      {
         Uart_RXInit();
      }
      
      return;
   }
   
   //���յ�4���ֽ�  -- �����ֽ�
   if(flg_Start4=='f' && flg_Start3=='t') 
   {
//test
      //Uart1_Puts("4");

      flg_Start4='t';
      //iFunction=cUartByte;
      
      RX_data[iRXNum++]=cUartByte;
      
      return;
   }   
   
   //�������������У���
   if(flg_Start4=='t') 
   {
//test
      //Uart1_Puts("5");

      if( iRXNum<iRX_Sum  )  //������iRx_Sum������: ����+����
      {
         RX_data[iRXNum++]=cUartByte;
         return;
      }
      
      //�������һ��У����ֽ�      
      //RX_data[iRXNum++]=cUartByte;
      
      //���У���
      //iCheckSum = (uint8)iRX_Sum + (uint8)( iRx_Sum >>8);
      iCheckSum = iRX_Sum;
      for(i=0; i<iRX_Sum; i++)
      {
         iCheckSum=iCheckSum+RX_data[i]; 
      }  
      
      if ( cUartByte == (uint8)( ~((uint8)iCheckSum) +1 )   )
      {
         //�����ݸ��Ƶ�������sRX_Buf2              
         iRXNum2=iRXNum;
         memcpy(RX_data2,RX_data,iRXNum);

         //���ڽ��ճ�ʼ��
         Uart_RXInit();

         flg_Received = 1;   //���ڽ��յ���Ч���ݰ���־
        
         //�ش��ڽ����жϿ���__

      }         
      else
      {
         flg_Received = 0;  
     
         //���ڽ��ճ�ʼ��
         Uart_RXInit();  

         return;
      }
      
   }  
    
}


//��������ַ�
void Uart1_PutChar(uint8 c)
{
   while ( !(UART1_SR & (1<<7)) );  //�ж��ϴη�����û�����
   UART1_DR = c;
}

//��������ַ���
void Uart1_Puts(uint8 *s)
{
   while (*s)
   {
      Uart1_PutChar(*s++);
   }
}

//��������ֽ�
void Uart1_PutBytes(uint8 *s, uint16 ilen)
{
   unsigned int i;
   
   for(i=0;i<ilen;i++)
   {
      Uart1_PutChar(*s++);
   }
}


/*
//���ڽ��մ���         //�Ƽ����������ģ��ŵ�������ȥ����
void DoWithUart(void)
{
   RX_data2[RX_BUFFER_SIZE-2]=0;
   
   UART_Puts("   ");
   UART_Puts(RX_data2);
   UART_Puts(" back  ");
   
   flg_Received=0;
}

*/
