#ifndef __SOFTUART_H
#define __SOFTUART_H


//������9600  -- 26us
#define DIV_9600  15
#define COUNT_9600 25

//������19200  -- 52us
#define DIV_19200  15
#define COUNT_19200 51


void SoftUart_Init();   //ģ�⴮�ڳ�ʼ��
void Timer1_Init(uint16 iSplit, uint16 iTimeCount, uint8 iRepeat);  // Timer1 ��ʼ��
void SoftUart_IOInit();   //ģ�⴮��IO��ʼ��  PD2--���жϵ�RX   PD3 -- TX
void SoftUart_RXInit();   //ģ�⴮�ڽ��ղ�����ʼ��

void SoftUart_Receive();

__interrupt void EXTI_PORTD_IRQHandler(void);           //ģ�⴮�ڽ����½����ж�  
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void);   //ģ�⴮�ڽ��ն�ʱ��Timer1�ж�


void SoftUart_PutChar(uint8 c);     //ģ�⴮������ַ�
void SoftUart_Puts(uint8 *s);       //ģ�⴮������ַ���
void SoftUart_PutBytes(uint8 *s, uint16 ilen);  //ģ�⴮������ֽ�


//void DoWithSoftUart(void);        //����ģ�⴮�ڽ��գ�ͨ���ŵ���������


//����Э�鳣��
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
extern  uint8 flg_Reced;  //�ѽ�����һ֡����



//extern uint8 flg_Start1;   //���յ�1����ʼ�ֽ�
//extern uint8 flg_End1;   //���յ�1�������ֽ�
//extern uint8 flg_End2;   //���յ�2�������ֽ�

#endif