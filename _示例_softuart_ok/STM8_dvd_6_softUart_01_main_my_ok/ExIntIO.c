
#include "STM_Config.h"

// KEY1 -- PD7  -- LED3  —  PC3
// KEY2 -- PE3  -- LED2  —  PD0 


void ExIntIO_Ini(void)
{
   //设置PE3为带上拉输入, 使能中断输入
   PE_DDR|=(0<<3);   // 设置数据方向寄存器 1为输出，0为输入
   PE_CR1|=(1<<3);   // 设置带上拉电阻输入   
   PE_CR2|=(1<<3);   // 使能外部中断
   
   PE_ODR&=~(0<<3);   // 输入模式时 -- 不用设置ODR 
   
   //设置PE口的中断触发方式 --下降沿
   EXTI_CR2&=~( 1<<0 );
   EXTI_CR2|=( 1<<1 );
   
  
   //设置PD7(TL1)为带上拉输入, 使能中断输入
   PD_DDR|=(0<<7);   // 设置数据方向寄存器 1为输出，0为输入
   PD_CR1|=(1<<7);   // 设置带上拉电阻输入   
   PD_CR2|=(1<<7);   // 使能外部中断
   
   PD_ODR&=~(0<<3);   // 输入模式时 -- 不用设置ODR 

   //设置TL1(PD7)口的中断触发方式
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

/*   ------判断是哪个引脚发生中断----- keep ---------------
__interrupt void EXTI_PORTE_IRQHandler(void)
{
  // In order to detect unexpected events during development,
  //   it is recommended to set a breakpoint on the following instruction.
  
  EXTI_Sensitivity_TypeDef  Keyexti_Sensitivity_Type;
	
	 
	//  我们需要知道的信息是：
	//  哪个引脚，发生哪个中断
	 
	Keyexti_Sensitivity_Type = EXTI_GetExtIntSensitivity(EXTI_PORT_GPIOE);
	
	switch (Keyexti_Sensitivity_Type)	// 得到当前发生的是哪种中断类型  
	{
		case EXTI_SENSITIVITY_FALL_LOW :	// 低电平触发  

		break;
		case EXTI_SENSITIVITY_RISE_ONLY :	// 上升沿触发  

		break;
		case EXTI_SENSITIVITY_FALL_ONLY :	// 下降沿触发  
		  	// 判断是哪个引脚发生外部中断  
			if (!GPIO_ReadInputPin(KEY_PORTE, KEY_2)) {	
				LED_Reverse(LED_2);
			}

		break;
		case EXTI_SENSITIVITY_RISE_FALL :	// 高电平触发  

		break;
		default:
	 		break;
	}
}
*/