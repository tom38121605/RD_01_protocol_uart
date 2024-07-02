#ifndef __SOFTUART_H
#define __SOFTUART_H


//波特率9600  -- 26us
#define DIV_9600  15
#define COUNT_9600 25

//波特率19200  -- 52us
#define DIV_19200  15
#define COUNT_19200 51


void SoftUart_Init();   //模拟串口初始化
void Timer1_Init(uint16 iSplit, uint16 iTimeCount, uint8 iRepeat);  // Timer1 初始化
void SoftUart_IOInit();   //模拟串口IO初始化  PD2--带中断的RX   PD3 -- TX
void SoftUart_RXInit();   //模拟串口接收参数初始化

void SoftUart_Receive();

__interrupt void EXTI_PORTD_IRQHandler(void);           //模拟串口接收下降沿中断  
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void);   //模拟串口接收定时器Timer1中断


void SoftUart_PutChar(uint8 c);     //模拟串口输出字符
void SoftUart_Puts(uint8 *s);       //模拟串口输出字符串
void SoftUart_PutBytes(uint8 *s, uint16 ilen);  //模拟串口输出字节


//void DoWithSoftUart(void);        //处理模拟串口接收，通常放到主程序处理


//串口协议常量
#define SOFTUART_RX_START1 'A'   
#define SOFTUART_RX_END1   0x0D  
#define SOFTUART_RX_END2   0x0A  

extern volatile uint8 iRec;
extern volatile uint8 iBitCount;

#define SOFTRX_SIZE 50
extern  uint8 iRecData[SOFTRX_SIZE];
extern  uint8 iRecData2[SOFTRX_SIZE];
extern  uint16 iRecNum;
extern  uint16 iRecNum2;
extern  uint8 flg_Reced;  //已接收完一帧数据



//extern uint8 flg_Start1;   //接收第1个开始字节
//extern uint8 flg_End1;   //接收第1个结束字节
//extern uint8 flg_End2;   //接收第2个结束字节

#endif