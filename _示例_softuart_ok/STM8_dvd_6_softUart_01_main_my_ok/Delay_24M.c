#include "STM_Config.h"

/*-----------------------------------------------------------------------
延时函数  (IAR1311环境编译)
系统时钟：24MHz  
-----------------------------------------------------------------------*/

//1us精确延时函数  //这个无参数函数调用与返回需10t, 1个nop指令为1t
//--  24t * 1/24M ＝1us整
void Delay_1us(void)     //24MHz       --待验证
{
   asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  //5t
   asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");  //5t
   
   asm("nop");
   asm("nop");   
   asm("nop");
   asm("nop");
   
}


//精确nus延时函数, 5us-1000us以内为精确延时, 少于5us建议用多个Delay_1us()
void Delay_nus(unsigned int n)  //24MHz
{
   while (n--)
      Delay_1us();
}

/*
//精确nus延时函数，10us以上的精确延时
void Delay_nus_Count(unsigned int n)
{
   //Delay_10us： Delay_nus_Count(11);   //7.3728M
   //Delay_20us： Delay_nus_Count(25);   //7.3728M
   //Delay_50us： Delay_nus_Count(60);   //7.3728M
   //Delay_100us： Delay_nus_Count(121);   //7.3728M
   //Delay_500us： Delay_nus_Count(613);   //7.3728M
   
   while (n)
      n--;
}
*/


//1ms精确延时函数
//延时时间 = 6t + 2t +2t + n * 1t + (n+1)*2.5t + 4t  = 10t + 3.5nt + 6.5t = 3.5nt + 16.5t 
//即 (3.5n + 16.5) * 1/24 us = 1000us , 得 n= (1000*24 -16.5)/3.5 = 6852.4

void Delay_1ms(void)    //24M      --待验证
{
   unsigned int n;
   //n=6852;
   n=2278;
   while (n)
      n--;
}


//nms精确延时函数
void Delay_nms(unsigned int n)
{
   while(n--)
      Delay_1ms();
}

