//��ʱģ��
#ifndef __DELAY_16M_H
#define __DELAY_16M_H


//�������������� ��ʱģ�鶨�� ������������������

//1us��ȷ��ʱ����   -- ����֤ 1us  (����������ʵ��, ������ʱ�ľ�ȷ����ֵ)
//inline Delay_1us_Prec() { asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
//                               asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
//                               asm("nop"); asm("nop"); asm("nop");asm("nop"); }

void Delay_1us(void);  //1us��ȷ��ʱ����
void Delay_nus(unsigned int n);  //nus��ʱ����, 10us����Ϊ��ȷ��ʱ

void Delay_nus_Count(unsigned int n);     //��ȷnus��ʱ������5us���ϵľ�ȷ��ʱ
#define Delay_2us()  Delay_nus_Count(3)   //16M  //ʵ��2.0us
#define Delay_5us()  Delay_nus_Count(13)   //16M
#define Delay_10us()  Delay_nus_Count(29)   //16M
#define Delay_20us()  Delay_nus_Count(61)   //16M
#define Delay_50us()  Delay_nus_Count(157)   //16M
#define Delay_52us()  Delay_nus_Count(164)   //16M   //����52.08us(19200������), ʵ��52us
#define Delay_100us()  Delay_nus_Count(317)   //16M
#define Delay_500us()  Delay_nus_Count(1597)   //16M
//#define Delay_1ms()  Delay_nus_Count(1597)   //16M

void Delay_1ms(void);  //1ms��ȷ��ʱ����
void Delay_nms(unsigned int n);  //nms��ȷ��ʱ����

#endif
