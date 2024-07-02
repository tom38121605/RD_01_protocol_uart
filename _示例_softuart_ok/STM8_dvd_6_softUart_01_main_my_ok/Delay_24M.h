//��ʱģ��
#ifndef __DELAY_24M_H
#define __DELAY_24M_H


//�������������� ��ʱģ�鶨�� ������������������

void Delay_1us(void);  //1us��ȷ��ʱ����
void Delay_nus(unsigned int n);  //nus��ʱ����, 10us����Ϊ��ȷ��ʱ

void Delay_nus_Count(unsigned int n);     //��ȷnus��ʱ������10us���ϵľ�ȷ��ʱ
#define Delay_10us()  Delay_nus_Count(11)   //7.3728M
#define Delay_20us()  Delay_nus_Count(25)   //7.3728M
#define Delay_50us()  Delay_nus_Count(60)   //7.3728M
#define Delay_100us()  Delay_nus_Count(121)   //7.3728M
#define Delay_500us()  Delay_nus_Count(613)   //7.3728M

void Delay_1ms(void);  //1ms��ȷ��ʱ����
void Delay_nms(unsigned int n);  //nms��ȷ��ʱ����

#endif
