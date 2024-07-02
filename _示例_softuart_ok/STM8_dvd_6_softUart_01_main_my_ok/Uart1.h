#ifndef __UART1_H
#define __UART1_H



void Uart1_Init(uint32  iBaudRate);  //串口初始化函数
void Uart_RXInit(); //串口接收参数初始化

__interrupt void UART1_RX_IRQHandler(void);//串口中断函数  (包括接收和其它与接收有关的中断)
void Uart1_PutChar(uint8 c); //串口输出字符
void Uart1_Puts(uint8 *s); //串口输出字符串
void Uart1_PutBytes(uint8 *s, uint16 ilen); //串口输出字节
//void DoWithUart(void);     //处理串口接收，通常放到主程序处理


//串口协议常量
#define UART_RX_START1 0xAA  

#define RX_BUFFER_SIZE 50 
extern uint8 RX_data[RX_BUFFER_SIZE];
extern uint8 RX_data2[RX_BUFFER_SIZE];
extern uint16 iRXNum;
extern uint16 iRXNum2;
extern uint8 flg_Received;  //已接收到有效数据   

extern uint16 iRx_Sum2;

#endif