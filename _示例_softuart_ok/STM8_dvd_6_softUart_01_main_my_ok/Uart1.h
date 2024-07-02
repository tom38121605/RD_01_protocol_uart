#ifndef __UART1_H
#define __UART1_H



void Uart1_Init(uint32  iBaudRate);  //���ڳ�ʼ������
void Uart_RXInit(); //���ڽ��ղ�����ʼ��

__interrupt void UART1_RX_IRQHandler(void);//�����жϺ���  (�������պ�����������йص��ж�)
void Uart1_PutChar(uint8 c); //��������ַ�
void Uart1_Puts(uint8 *s); //��������ַ���
void Uart1_PutBytes(uint8 *s, uint16 ilen); //��������ֽ�
//void DoWithUart(void);     //�����ڽ��գ�ͨ���ŵ���������


//����Э�鳣��
#define UART_RX_START1 0xAA  

#define RX_BUFFER_SIZE 50 
extern uint8 RX_data[RX_BUFFER_SIZE];
extern uint8 RX_data2[RX_BUFFER_SIZE];
extern uint16 iRXNum;
extern uint16 iRXNum2;
extern uint8 flg_Received;  //�ѽ��յ���Ч����   

extern uint16 iRx_Sum2;

#endif