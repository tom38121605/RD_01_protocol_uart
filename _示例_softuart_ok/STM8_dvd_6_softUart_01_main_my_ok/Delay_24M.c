#include "STM_Config.h"

/*-----------------------------------------------------------------------
��ʱ����  (IAR1311��������)
ϵͳʱ�ӣ�24MHz  
-----------------------------------------------------------------------*/

//1us��ȷ��ʱ����  //����޲������������뷵����10t, 1��nopָ��Ϊ1t
//--  24t * 1/24M ��1us��
void Delay_1us(void)     //24MHz       --����֤
{
   asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  //5t
   asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  //5t
   
   asm("nop");
   asm("nop");   
   asm("nop");
   asm("nop");
   
}


//��ȷnus��ʱ����, 5us-1000us����Ϊ��ȷ��ʱ, ����5us�����ö��Delay_1us()
void Delay_nus(unsigned int n)  //24MHz
{
   while (n--)
      Delay_1us();
}

/*
//��ȷnus��ʱ������10us���ϵľ�ȷ��ʱ
void Delay_nus_Count(unsigned int n)
{
   //Delay_10us�� Delay_nus_Count(11);   //7.3728M
   //Delay_20us�� Delay_nus_Count(25);   //7.3728M
   //Delay_50us�� Delay_nus_Count(60);   //7.3728M
   //Delay_100us�� Delay_nus_Count(121);   //7.3728M
   //Delay_500us�� Delay_nus_Count(613);   //7.3728M
   
   while (n)
      n--;
}
*/


//1ms��ȷ��ʱ����
//��ʱʱ�� = 6t + 2t +2t + n * 1t + (n+1)*2.5t + 4t  = 10t + 3.5nt + 6.5t = 3.5nt + 16.5t 
//�� (3.5n + 16.5) * 1/24 us = 1000us , �� n= (1000*24 -16.5)/3.5 = 6852.4

void Delay_1ms(void)    //24M      --����֤
{
   unsigned int n;
   //n=6852;
   n=2278;
   while (n)
      n--;
}


//nms��ȷ��ʱ����
void Delay_nms(unsigned int n)
{
   while(n--)
      Delay_1ms();
}

