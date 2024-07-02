
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;



//uart
UINT8  irxdata0=0;
UINT8  irxdata1=0;


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

   
   SADDR =  0xc0;          //1100 0000   
   SADEN =  0xfe;        //1111 1110   
   //SADEN =  0;             //1111 1110
 
   
   //iaddrslave0 = 0xc1;    //1100 0001
   
   SCON = 0xd0;     	//UART0 Mode3  
   SCON |= 1<<5;     //SM2=1
   
   set_ES;  
   set_EA;
   

   //iputs0("start\r\n");
   
   P16=0;
   
   
   while(1)
   {  ;       
      SADDR =  0xc0;          //1100 0000   
      Timer0_Delay1ms(3000); 
      
//      SADDR =  0xc7;          //1100 0111   
//      Timer0_Delay1ms(3000); 
      
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
      
   }
   
   if(TI==1)   
      clr_TI;  
      
}

