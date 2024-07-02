
//nclude "Clock.h"
#include "STM_Config.h"

//#include "type_def.h"
//#define HSE_Clock 0
//#define HSI_Clock 1
//#define LSI_Clock 2


//设置系统主时钟HSI
void Clock_HSI_Ini()
{
   
   /*//-------------flash熔丝位配置------------------------  // 小心 -- 待测试  (配置熔丝位)
   FLASH_Unlock(FLASH_MEMTYPE_DATA);
  
   FLASH_EraseOptionByte(FLASH_WAIT_STATES_ADDRESS);//恢复HSI时钟
   FLASH_EraseOptionByte(HSE_CLOCK_STARTUP_ADDRESS);
         
   FLASH_Lock(FLASH_MEMTYPE_DATA);
   */
   

   // --------------------设置新时钟 (对于内置16MHz不需要修改寄存器, 是默认值) ---------------------

   CLK_CKDIVR&= (uint8)( ~( (1<<3)|(1<<4) ) );//时钟分频的清0  -- 无分频
   //CLK_CKDIVR|= (uint8)0x00;  //设置时钟分频
  
}


//设置系统主时钟HSE
//因时间原因, 本模块的两个分频参数部分, 及内外时钟切换对flash操作部分, 以后再完善__
//再做Clock_Ini_EX扩展函数, 对flash部分操作
void Clock_HSE_Ini()   //-- 待测试
{ 
/*   uint8 iOldClock;
   uint8 iHSE_Clock;
   uint16 DownCounter ;
   
   //-------------flash熔丝位配置------------------------  // 小心 -- 待测试 (配置熔丝位)
   FLASH_Unlock(FLASH_MEMTYPE_DATA);
   
   iHSE_Clock=HSE_OVER_16MHz;
   
   if(iHSE_Clock>0)   //HSE大于16MHz情况, 小于等于则不需要 
      FLASH_ProgramOptionByte(FLASH_WAIT_STATES_ADDRESS,iHSE_Clock);
  
   //对所以HSE外部时钟, 都需要
   FLASH_ProgramOptionByte(HSE_CLOCK_STARTUP_ADDRESS,HSECNT_8CLK);      
      
   FLASH_Lock(FLASH_MEMTYPE_DATA);
   
    
   // --------------------设置新时钟 ---------------------
   DownCounter = 0x0491;
   
   //保存旧时钟, 以便设置新时钟后关闭它
   iOldClock = CLK_CMSR;      
   
   //---自动切换模式
   
   //设置允许时钟切换
   CLK_SWCR &= (1<<1);   

   //切换时钟不产生中断
   CLK_SWCR &= (1<<2);   
   
   //设置新时钟为外部时钟      
   CLK_SWR = CLK_SOURCE_HSE;    
   
   while( ((CLK_SWCR & (1<<0)) != 0 ) && (DownCounter != 0) )
   {      
       DownCounter--;          
   }
   
   //test
   if (DownCounter == 0)
   {
      DownCounter=100;
   }
   
   
   //---------------手动切换模式----------------
   
   //设置允许时钟切换
   //CLK_SWCR &= (1<<1);   

   //切换时钟不产生中断
   //CLK_SWCR &= (1<<2);   
   
   //设置新时钟为外部时钟      
   //CLK_SWR = CLK_SOURCE_HSE;      
      
  
   
   //关闭旧时钟
   if ( iOldClock == CLK_SOURCE_HSI )
   {
      CLK_ICKR &= ~(1<<0);  
   }
   else if ( iOldClock == CLK_SOURCE_LSI )
   {
      CLK_ICKR &= ~(1<<3); 
   }     
   //else if ( iOldClock == CLK_SOURCE_HSE )  //--keep
   //{
   //   CLK_ECKR &= ~(1<<0);  
   //}
*/

}






