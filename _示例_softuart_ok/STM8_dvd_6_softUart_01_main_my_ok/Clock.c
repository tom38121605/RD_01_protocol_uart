
//nclude "Clock.h"
#include "STM_Config.h"

//#include "type_def.h"
//#define HSE_Clock 0
//#define HSI_Clock 1
//#define LSI_Clock 2


//����ϵͳ��ʱ��HSI
void Clock_HSI_Ini()
{
   
   /*//-------------flash��˿λ����------------------------  // С�� -- ������  (������˿λ)
   FLASH_Unlock(FLASH_MEMTYPE_DATA);
  
   FLASH_EraseOptionByte(FLASH_WAIT_STATES_ADDRESS);//�ָ�HSIʱ��
   FLASH_EraseOptionByte(HSE_CLOCK_STARTUP_ADDRESS);
         
   FLASH_Lock(FLASH_MEMTYPE_DATA);
   */
   

   // --------------------������ʱ�� (��������16MHz����Ҫ�޸ļĴ���, ��Ĭ��ֵ) ---------------------

   CLK_CKDIVR&= (uint8)( ~( (1<<3)|(1<<4) ) );//ʱ�ӷ�Ƶ����0  -- �޷�Ƶ
   //CLK_CKDIVR|= (uint8)0x00;  //����ʱ�ӷ�Ƶ
  
}


//����ϵͳ��ʱ��HSE
//��ʱ��ԭ��, ��ģ���������Ƶ��������, ������ʱ���л���flash��������, �Ժ�������__
//����Clock_Ini_EX��չ����, ��flash���ֲ���
void Clock_HSE_Ini()   //-- ������
{ 
/*   uint8 iOldClock;
   uint8 iHSE_Clock;
   uint16 DownCounter ;
   
   //-------------flash��˿λ����------------------------  // С�� -- ������ (������˿λ)
   FLASH_Unlock(FLASH_MEMTYPE_DATA);
   
   iHSE_Clock=HSE_OVER_16MHz;
   
   if(iHSE_Clock>0)   //HSE����16MHz���, С�ڵ�������Ҫ 
      FLASH_ProgramOptionByte(FLASH_WAIT_STATES_ADDRESS,iHSE_Clock);
  
   //������HSE�ⲿʱ��, ����Ҫ
   FLASH_ProgramOptionByte(HSE_CLOCK_STARTUP_ADDRESS,HSECNT_8CLK);      
      
   FLASH_Lock(FLASH_MEMTYPE_DATA);
   
    
   // --------------------������ʱ�� ---------------------
   DownCounter = 0x0491;
   
   //�����ʱ��, �Ա�������ʱ�Ӻ�ر���
   iOldClock = CLK_CMSR;      
   
   //---�Զ��л�ģʽ
   
   //��������ʱ���л�
   CLK_SWCR &= (1<<1);   

   //�л�ʱ�Ӳ������ж�
   CLK_SWCR &= (1<<2);   
   
   //������ʱ��Ϊ�ⲿʱ��      
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
   
   
   //---------------�ֶ��л�ģʽ----------------
   
   //��������ʱ���л�
   //CLK_SWCR &= (1<<1);   

   //�л�ʱ�Ӳ������ж�
   //CLK_SWCR &= (1<<2);   
   
   //������ʱ��Ϊ�ⲿʱ��      
   //CLK_SWR = CLK_SOURCE_HSE;      
      
  
   
   //�رվ�ʱ��
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






