//延时模块
#ifndef __DELAY_16M_H
#define __DELAY_16M_H


//＝＝＝＝＝＝＝ 延时模块定义 ＝＝＝＝＝＝＝＝＝

//1us精确延时函数   -- 已验证 1us  (用内联函数实现, 具有延时的精确理论值)
//inline Delay_1us_Prec() { asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
//                               asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
//                               asm("nop"); asm("nop"); asm("nop");asm("nop"); }

void Delay_1us(void);  //1us精确延时函数
void Delay_nus(unsigned int n);  //nus延时函数, 10us以内为精确延时

void Delay_nus_Count(unsigned int n);     //精确nus延时函数，5us以上的精确延时
#define Delay_2us()  Delay_nus_Count(3)   //16M  //实测2.0us
#define Delay_5us()  Delay_nus_Count(13)   //16M
#define Delay_10us()  Delay_nus_Count(29)   //16M
#define Delay_20us()  Delay_nus_Count(61)   //16M
#define Delay_50us()  Delay_nus_Count(157)   //16M
#define Delay_52us()  Delay_nus_Count(164)   //16M   //所需52.08us(19200波特率), 实际52us
#define Delay_100us()  Delay_nus_Count(317)   //16M
#define Delay_500us()  Delay_nus_Count(1597)   //16M
//#define Delay_1ms()  Delay_nus_Count(1597)   //16M

void Delay_1ms(void);  //1ms精确延时函数
void Delay_nms(unsigned int n);  //nms精确延时函数

#endif
