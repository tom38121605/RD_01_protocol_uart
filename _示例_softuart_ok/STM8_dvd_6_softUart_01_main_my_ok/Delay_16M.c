#include "STM_Config.h"


/*-----------------------------------------------------------------------
��ʱ���� (IAR1311��������)
ϵͳʱ�ӣ�16MHz
-----------------------------------------------------------------------*/

//1us��ʱ����  //����޲������������뷵����10t, 1��nopָ��Ϊ1t
//--  16t * 1/16M ��1us��
void Delay_1us(void)     //16MHz    --����֤  -- ʵ��ֻ��0.92us  ����һ��nopָ�0.98us -- ����ȷ
{
   asm("nop");
   asm("nop");
   asm("nop");
   
   asm("nop");
   asm("nop");
   asm("nop");
   
   asm("nop");
   //asm("nop");
}


//��ȷnus��ʱ����, 5us-1000us����Ϊ��ȷ��ʱ, ����5us�����ö��Delay_1us()
void Delay_nus(unsigned int n)  //16MHz
{
   while (n--)
      Delay_1us();
}

//��ȷnus��ʱ������5us���ϵľ�ȷ��ʱ
void Delay_nus_Count(unsigned int n)  //��������10, ��ʱ����5us
{
   //Delay_2us()  Delay_nus_Count(3)   //16M
   //Delay_5us()  Delay_nus_Count(13)   //16M
   //Delay_10us()  Delay_nus_Count(29)   //16M
   //Delay_20us()  Delay_nus_Count(61)   //16M
   //Delay_50us()  Delay_nus_Count(157)   //16M
   //Delay_52us()  Delay_nus_Count(164)   //16M
   //Delay_100us()  Delay_nus_Count(317)   //16M
   //Delay_500us()  Delay_nus_Count(1597)   //16M
   
   while (n)
      n--;
}



//1ms��ȷ��ʱ����
void Delay_1ms(void)    //16M    
{
   unsigned int n;
   //n=4566;
   n=3197;
   while (n)
      n--;
}



//nms��ȷ��ʱ����
void Delay_nms(unsigned int n)
{
   while(n--)
      Delay_1ms();
}

