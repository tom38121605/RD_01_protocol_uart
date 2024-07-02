
#include "STM_Config.h"

void LedIO_Ini(void)
{
   //设置PD0为推挽快速输出, 初始高电平
   PD_DDR|=(1<<0);   // 设置数据方向寄存器 1--输出，0--输入 
   PD_CR1|=(1<<0);   // 设置推挽输出 
   PD_CR2|=(1<<0);   // 设置输出频率 1--10M(Fast)，0--2M
   PD_ODR|=(1<<0);   // 设置初始电平为高电平 
  
   //设置PC3为推挽快速输出, 初始高电平
   PC_DDR|=(1<<3);   // 设置数据方向寄存器 1--输出，0--输入
   PC_CR1|=(1<<3);   // 设置推挽输出
   PC_CR2|=(1<<3);   // 设置输出频率 1--10M(Fast)，0--2M
   PC_ODR|=(1<<3);   // 设置初始电平为高电平 
  
  
}
