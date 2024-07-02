//延时模块
#ifndef __DELAY_24M_H
#define __DELAY_24M_H


//＝＝＝＝＝＝＝ 延时模块定义 ＝＝＝＝＝＝＝＝＝

void Delay_1us(void);  //1us精确延时函数
void Delay_nus(unsigned int n);  //nus延时函数, 10us以内为精确延时

void Delay_nus_Count(unsigned int n);     //精确nus延时函数，10us以上的精确延时
#define Delay_10us()  Delay_nus_Count(11)   //7.3728M
#define Delay_20us()  Delay_nus_Count(25)   //7.3728M
#define Delay_50us()  Delay_nus_Count(60)   //7.3728M
#define Delay_100us()  Delay_nus_Count(121)   //7.3728M
#define Delay_500us()  Delay_nus_Count(613)   //7.3728M

void Delay_1ms(void);  //1ms精确延时函数
void Delay_nms(unsigned int n);  //nms精确延时函数

#endif
