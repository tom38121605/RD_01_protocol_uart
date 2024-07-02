
#include "STM_Config.h"

// KEY1 -- PD7  -- LED3  ��  PC3
// KEY2 -- PE3  -- LED2  ��  PD0 


void ExIntIO_Ini(void)
{
   //����PE3Ϊ����������, ʹ���ж�����
   PE_DDR|=(0<<3);   // �������ݷ���Ĵ��� 1Ϊ�����0Ϊ����
   PE_CR1|=(1<<3);   // ���ô�������������   
   PE_CR2|=(1<<3);   // ʹ���ⲿ�ж�
   
   PE_ODR&=~(0<<3);   // ����ģʽʱ -- ��������ODR 
   
   //����PE�ڵ��жϴ�����ʽ --�½���
   EXTI_CR2&=~( 1<<0 );
   EXTI_CR2|=( 1<<1 );
   
  
   //����PD7(TL1)Ϊ����������, ʹ���ж�����
   PD_DDR|=(0<<7);   // �������ݷ���Ĵ��� 1Ϊ�����0Ϊ����
   PD_CR1|=(1<<7);   // ���ô�������������   
   PD_CR2|=(1<<7);   // ʹ���ⲿ�ж�
   
   PD_ODR&=~(0<<3);   // ����ģʽʱ -- ��������ODR 

   //����TL1(PD7)�ڵ��жϴ�����ʽ
   EXTI_CR2&=~( 1<<2 );
  
  
}

#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
   //if(!(PD_IDR & (1<<7)) ) 
      PC_ODR^=(1<<3);   
  
}

#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{
   
   //if( (PE_IDR & (1<<3))==0 ) 
      PD_ODR^=(1<<0);   
   
   __disable_interrupt();
   
   //__enable_interrupt();
 }

/*   ------�ж����ĸ����ŷ����ж�----- keep ---------------
__interrupt void EXTI_PORTE_IRQHandler(void)
{
  // In order to detect unexpected events during development,
  //   it is recommended to set a breakpoint on the following instruction.
  
  EXTI_Sensitivity_TypeDef  Keyexti_Sensitivity_Type;
	
	 
	//  ������Ҫ֪������Ϣ�ǣ�
	//  �ĸ����ţ������ĸ��ж�
	 
	Keyexti_Sensitivity_Type = EXTI_GetExtIntSensitivity(EXTI_PORT_GPIOE);
	
	switch (Keyexti_Sensitivity_Type)	// �õ���ǰ�������������ж�����  
	{
		case EXTI_SENSITIVITY_FALL_LOW :	// �͵�ƽ����  

		break;
		case EXTI_SENSITIVITY_RISE_ONLY :	// �����ش���  

		break;
		case EXTI_SENSITIVITY_FALL_ONLY :	// �½��ش���  
		  	// �ж����ĸ����ŷ����ⲿ�ж�  
			if (!GPIO_ReadInputPin(KEY_PORTE, KEY_2)) {	
				LED_Reverse(LED_2);
			}

		break;
		case EXTI_SENSITIVITY_RISE_FALL :	// �ߵ�ƽ����  

		break;
		default:
	 		break;
	}
}
*/