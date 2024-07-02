
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;


static UINT8 imaincount =0;
static UINT8 flg_send =0;


//uart
UINT8  irxdata0=0;


void iputs0(UINT8 *msg)
{
   while(*msg)
      Send_Data_To_UART0(*msg++);
}
 
 
//uart0 txrx
void main (void) 
{      
   
   Set_All_GPIO_Quasi_Mode; 
   P12_PushPull_Mode;       
   
   
   //AUXR1 |=1<<2; 
   
   
   //uart0 init
   InitialUART0_Timer1(115200);
   //TI = 1;
   
   
   SCON = 0xd0;     	//UART0 Mode3   
   //SCON = 0xc0; 

   
   set_ES;           
   set_EA;          
   
   
   //printf("start\r\n");  
   iputs0("start\r\n");
   
   P16=0;
   
   
   while(1)
   {         
      
      imaincount++;      
      
      Timer0_Delay1ms(10);
      
      
      if(imaincount >=10)
      {
         
         flg_send ^= 1;
         
         imaincount =0;         
      }      

      
      //-------- can master send addr ----------------
      SCON = 0xc0;   //MODE1
      

      if (flg_send ==1)
         set_TB8;
      else
         clr_TB8;

   
      Send_Data_To_UART0(0xc0);  
      //Send_Data_To_UART0(0x08);  //00,0f,80
      
      //Timer0_Delay1ms(10); 

      SCON = 0xd0;   //MODE3
      
      //-------- can master send addr ---end-------------
      
   }   
      
} 



void SerialPort0_ISR(void) interrupt 4 
{
   
   if (RI==1) 
   {                                      
      clr_RI;                           
   
      irxdata0 = SBUF;
      
      //Send_Data_To_UART0(irxdata0);
  
      
      P16=~P16;
      
//      if(irxdata0==0x55) 
//         P16=1;
//      else if(irxdata0==0xaa)
//         P16=0;
      
   }
   
   if(TI==1)   
      clr_TI;  
      
}



