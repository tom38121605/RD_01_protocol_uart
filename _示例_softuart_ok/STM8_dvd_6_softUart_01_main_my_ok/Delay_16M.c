#include "STM_Config.h"


/*-----------------------------------------------------------------------
延时函数 (IAR1311环境编译)
系统时钟：16MHz
-----------------------------------------------------------------------*/

//1us延时函数  //这个无参数函数调用与返回需10t, 1个nop指令为1t
//--  16t * 1/16M ＝1us整
void Delay_1us(void)     //16MHz    --待验证  -- 实际只有0.92us  增加一个nop指令到0.98us -- 不精确
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


//精确nus延时函数, 5us-1000us以内为精确延时, 少于5us建议用多个Delay_1us()
void Delay_nus(unsigned int n)  //16MHz
{
   while (n--)
      Delay_1us();
}

//精确nus延时函数，5us以上的精确延时
void Delay_nus_Count(unsigned int n)  //计数增加10, 延时增加5us
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



//1ms精确延时函数
void Delay_1ms(void)    //16M    
{
   unsigned int n;
   //n=4566;
   n=3197;
   while (n)
      n--;
}



//nms精确延时函数
void Delay_nms(unsigned int n)
{
   while(n--)
      Delay_1ms();
}

