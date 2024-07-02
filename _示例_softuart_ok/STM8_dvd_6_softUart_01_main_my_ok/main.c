//ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����, ��: lflg_DVDCMD = ATCMD_MC; 
//��������DVD��ָ���, �ó�ֵ����, ��: lflg_DVDCMD=oxFFFF;  

//ע�Ȿ�������timer1.c��ExIntIO.c������softUart.c��, ����2���ļ�һ��Ҫremove��������


#include "STM_Config.h"


#define ATCMD_CA  (uint16)( 'C'*256 + 'A')
#define ATCMD_CB  (uint16)( 'C'*256 + 'B')
#define ATCMD_CD  (uint16)( 'C'*256 + 'D')
#define ATCMD_CG  (uint16)( 'C'*256 + 'G')
#define ATCMD_CH  (uint16)( 'C'*256 + 'H')
#define ATCMD_CY  (uint16)( 'C'*256 + 'Y')
#define ATCMD_CW  (uint16)( 'C'*256 + 'W')

#define ATCMD_MA  (uint16)( 'M'*256 + 'A')
#define ATCMD_MC  (uint16)( 'M'*256 + 'C')
#define ATCMD_MD  (uint16)( 'M'*256 + 'D')
#define ATCMD_ME  (uint16)( 'M'*256 + 'E')

#define ATCMD_MF  (uint16)( 'M'*256 + 'F')
#define ATCMD_MG  (uint16)( 'M'*256 + 'G')
#define ATCMD_MQ  (uint16)( 'M'*256 + 'Q')
#define ATCMD_MV  (uint16)( 'M'*256 + 'V')
#define ATCMD_MW  (uint16)( 'M'*256 + 'W')


//MCU ����3��
uint8 CMDTEXT1[7]={0xAA,0x00,0x03,0x02,0x00,0x17,0xE4};
uint8 CMDTEXT2[7]={0xAA,0x00,0x03,0x02,0x00,0x3B,0xC0};

uint8 CMDTEXT3[21]={0xAA,0x00,0x11,0x05,0x42,0x6C,0x75,0x65,0x74,0x6F,0x6F,0x74,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34}; 
                    //                  Bluetooth
//uint8 CMDTEXT3[21]={0xAA,0x00,0x11,0x05,0x42,0x6B,0x75,0x65,0x74,0x6F,0x6F,0x74,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x35}; 
                    //                  Bkuetooth
 
uint8 CMDTEXT4[7]={0xAA,0x00,0x03,0x02,0x00,0x16,0xE5};

uint8 CMDTEXT_TEST[7]={0x05,0x06,0x07,0x08,0x09,0x0D,0x0A};  //"56789"

uint8 iTelNo[20];
uint8 iTelLen=0;

//uint8 iCYStatu=0;

#define DVDCMD00 0xFFFF
#define STM8CMD00 0xFFFF
uint16 lflg_DVDCMD=DVDCMD00;
uint16 lflg_STM8CMD=STM8CMD00;

uint8 flg_PlayReady=0;
uint8 iHF_Times=0;
uint32 lDelayCounts;


uint8 flg_MG=0;
uint8 iCH_Times=0;

//uint8 flg_Connected=0;

uint8 f_PlayIO=0;

uint8 f_McuStart1=0;
uint8 f_McuStart2=0;
uint8 f_McuStart3=0;
uint8 f_McuStart4=0;
uint8 f_McuStart5=0;

uint32 lMcuStart_Count1;
uint32 lMcuStart_Count2;


void DoWith_Uart1();
void DoWith_SoftUart();


int main(void)
{ 
   uint8 iOutData[SOFTRX_SIZE];
   uint8 flg_PlayIO_Old;
   uint8 flg_PlayIO_New;         
         
      
   //������ʱ�� 
   Clock_HSI_Ini();  
  
   //__disable_interrupt(); 
   
   
   //ģ�⴮�ڳ�ʼ��
   SoftUart_Init(); 
   
   
   //����PD4Ϊ����������, ��ʼ�͵�ƽ
   PD_DDR|=(1<<4);   // �������ݷ���Ĵ��� 1--�����0--���� 
   PD_CR1|=(1<<4);   // ����������� 
   PD_CR2|=(1<<4);   // �������Ƶ�� 1--10M(Fast)��0--2M
   PD_ODR&=~(1<<4);   // ���ó�ʼ��ƽΪ�͵�ƽ 
  

   //����PC3Ϊ����������, �����ⲿ�ж�  
   PC_DDR&=~(0<<3);   // �������ݷ���Ĵ��� 1--�����0--����
   PC_CR1|=(1<<3);    // ���ô�������������   
   PC_CR2&=~(1<<3);   // ʹ���ⲿ�ж�      
   
   //���ڳ�ʼ��, ���ò�����
   Uart1_Init(19200);    
   
   __enable_interrupt();
   
   //asm("sim");
   //__disable_interrupt();
  
   //Delay_nms(100);    
   //Delay_nms(1000);    
   //Delay_nms(1000);  


   flg_Reced=0;
   iRecNum2=0;
   
   //Uart1_Puts("12345");
   //Uart1_PutBytes(a1,5);
   
   //iCYStatu=0;
   lflg_DVDCMD=DVDCMD00;
   lflg_STM8CMD=STM8CMD00;
   
   flg_PlayReady=0;
   iHF_Times=0;   
   
   flg_MG=0;
   
   iCH_Times=0;
   
   f_PlayIO=0;
   
   flg_PlayIO_Old = ( PC_IDR & (1<<3) );
   
   f_McuStart1=0;
   f_McuStart2=0;
   f_McuStart3=0;
   f_McuStart4=0;
   f_McuStart5=0;
   
   
   //test
   //SoftUart_Puts("12345\r\n");
   //SoftUart_Puts("abcde\r\n");
   
   //���INT���� 420ms�� + 9 * 160ms(5��4��) + ��
   PD_ODR|=(1<<4); //�ߵ�ƽ 
   Delay_nms(420);       
   PD_ODR&=~(1<<4); //�͵�ƽ 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //�ߵ�ƽ 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //�͵�ƽ 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //�ߵ�ƽ 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //�͵�ƽ 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //�ߵ�ƽ 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //�͵�ƽ 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //�ߵ�ƽ 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //�͵�ƽ 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //�ߵ�ƽ    

   
   while(1)  
   {   //test 5.0us //3.0us 
      
      //test count time
      PD_ODR^=(1<<4);   
      
      
      //scan softuart
      SoftUart_Receive();        
            
      //ģ�⴮���յ�DVD��Ϣ�Ĵ���
      if (flg_Reced==1)   
      {  
         DoWith_SoftUart();            
         flg_Reced=0;      
      }            
      
      //Uart1�յ�������Ϣ�Ĵ���
      if (flg_Received==1)  
      {//���ݰ�: AA 00 03 02 00 04 F7  ����ģ������ݰ�: 02 00 04  (����+����)
         
         DoWith_Uart1();
         flg_Received=0;        
      }  
     
      // MCU�����������ݳ���
      if (f_McuStart1==0)
      {
         lMcuStart_Count1++;
            
         if(lMcuStart_Count1>=300000)  //10000
         {
            lMcuStart_Count1=0;
            f_McuStart1=1;    
         }         
      }
      else if (f_McuStart1==1)
      {
         //�յ�����������Ϣ��, �ٷ����ݸ�����, ��ȡ�豸���Ƶ�
         Uart1_PutBytes(CMDTEXT1,7);  //����               
         Uart1_PutBytes(CMDTEXT2,7);  //A2DP�������               
         Uart1_PutBytes(CMDTEXT3,21); //�豸����: bluetooth + 7 x 00  
         
         f_McuStart1=2;
      }  
      
      
      //�ȴ�����AT#MCָ������
      if (f_McuStart2==0 && f_McuStart1==2)
      {
         lMcuStart_Count2++;
            
         if(lMcuStart_Count2>=600000)  //10000
         {
            lMcuStart_Count2=0;
            f_McuStart2=1;    
         }         
      }
      else if (f_McuStart2==1 && f_McuStart1==2)
      {        
         f_McuStart2=2;
      } 
      
          
      //����3��AA 00 03 02 00 16 E5 ָ�����
      if(f_McuStart2==2)
      {
         if (iHF_Times<1)
         {           
            lDelayCounts++;
            
            if(lDelayCounts>=10000)  //100000
            {
               lDelayCounts=0;
               iHF_Times++;
               f_McuStart3=1;
               
               lflg_DVDCMD=DVDCMD00;            
               lflg_STM8CMD=0x0016;
               
               Uart1_PutBytes(CMDTEXT4,7);    
            }
         }  
         
         //if ( (iHF_Times>0) && (iHF_Times<3) && (flg_MG==1) )
         else if ( (iHF_Times>0) && (iHF_Times<3) )
         {           
            lDelayCounts++;
            
            if(lDelayCounts>=10000)
            {
               lDelayCounts=0;
      
               if(flg_MG<1) //������Ҫ<1,2,3��(��AT#MG��������Ӧ�޸�flg_MG=1,2,3)
               {
                  flg_MG++;
               }
               else
               {
                  iHF_Times++;
               
                  lflg_DVDCMD=DVDCMD00;            
                  lflg_STM8CMD=0x0016;
               
                  Uart1_PutBytes(CMDTEXT4,7);    
               
                  if(iHF_Times==2) f_McuStart4=1;
               
                  if(iHF_Times==3) f_McuStart5=1;  //�������̽��� 
               }
               
            }
         } 
         
      }      
      
        
      //�������ż��
      if (flg_PlayReady==1)
      {
         
         flg_PlayIO_New = ( PC_IDR & (1<<3) );
         
         if( flg_PlayIO_New >  flg_PlayIO_Old ) //���
         {     
            //������DVD: MB                  
            iOutData[0]='M';
            iOutData[1]='B';
            iOutData[2]=0x0D;
            iOutData[3]=0x0A;
            SoftUart_PutBytes(iOutData,4); 
            
            //flg_Playing=1;
            
            flg_PlayIO_Old=flg_PlayIO_New;
         }
         else if( flg_PlayIO_New <  flg_PlayIO_Old ) //���
         {
            //������DVD: MA                  
            iOutData[0]='M';
            iOutData[1]='A';
            iOutData[2]=0x0D;
            iOutData[3]=0x0A;
            SoftUart_PutBytes(iOutData,4);            
            
            //flg_Playing=0;
            
            flg_PlayIO_Old=flg_PlayIO_New;
         }
      
      } //if (flg_PlayReady==2)     
      
      
      
   } //while(1)
   
   
}


//ģ�⴮�ڽ���DVD���ݴ���
void DoWith_SoftUart()
{ //��ʽ: AT#CW10086 0D 0A
   uint16 iATCmd;
   uint8 iSendData[SOFTRX_SIZE]; 
   uint16 iSendNum;
   uint8 i;
   uint16 iTempSum;
   
   //test
   //SoftUart_PutBytes(iRecData2,iRecNum2); 

   iATCmd = (uint16)(iRecData2[3]*256+iRecData2[4]);  //��: CW
   switch (iATCmd)
   {
      case ATCMD_CA:    //���
      
         lflg_DVDCMD = ATCMD_CA;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         lflg_STM8CMD= 0x0050;
      
         //���͵�����: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x50;   //lflg_DVDCMD��           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);  
      
         break;
         
      
      case ATCMD_CB:    //ȡ�����
      
         lflg_DVDCMD = ATCMD_CB;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         lflg_STM8CMD= 0x0050;
      
         //���͵�����: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x50;   //lflg_DVDCMD��           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);  
      
         break;
      
      case ATCMD_CD:    //�Ͽ����ֻ�����������
      
         //lflg_DVDCMD = ATCMD_CD;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         lflg_STM8CMD= 0x0017;
      
         //���͵�����: AA 00 03 02 00 17 E4
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x17;   //lflg_DVDCMD��           
         iSendData[6]=0xE4;               
         Uart1_PutBytes(iSendData,7); 
      
      
         //���͵�����: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x50;   //lflg_DVDCMD��           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);       
      
         break;
         
      case ATCMD_CG:    //�Ҷ�
         
         //lflg_DVDCMD = ATCMD_CG;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         //lflg_STM8CMD= 0x0002;
      
         //���͵�����: AA 00 03 02 00 02 F9
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x02;   //lflg_DVDCMD��           
         iSendData[6]=0xF9;               
         Uart1_PutBytes(iSendData,7); 
      
      
         //���͵�����: AA 00 03 02 00 06 F5
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x06;   //lflg_DVDCMD��           
         iSendData[6]=0xF5;               
         Uart1_PutBytes(iSendData,7);       
      
         break;       
      
      case ATCMD_CH:    //�ز��绰����
      
         lflg_DVDCMD = ATCMD_CH;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         lflg_STM8CMD= 0x000C;
         
         //���͵�����: AA 00 03 02 00 0C EF
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD��             
         iSendData[5]=0x0C;   //lflg_DVDCMD��           
         iSendData[6]=0xEF;               
         Uart1_PutBytes(iSendData,7); 
      
         break;      
         
      case ATCMD_CW:    //�绰����
      
         lflg_DVDCMD = ATCMD_CW;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         
         iTelLen=iRecNum2-7;

         //���͵�����: AA 00 ���� 00 00 xxxxx �绰����
         iSendData[0]=0xAA;
         iSendData[1]=0x0;
         iSendData[2]=iTelLen+2;
         iSendData[3]=0x0;
         iSendData[4]=0x0;               
      
         memcpy( iTelNo,&iRecData2[5],iTelLen); 
      
         memcpy( &iSendData[5],&iRecData2[5],iTelLen);                           
      
         iSendNum= iSendData[2]+ 4 ;
      
         iTempSum = iSendData[1];               
         for(i=2; i<(iSendNum-1); i++)
         {
            iTempSum = iTempSum + iSendData[i];                  
         }
      
         iSendData[iSendNum-1]= (uint8)( ~((uint8)iTempSum) +1 );  //ȡ��У���
         
         Uart1_PutBytes(iSendData,iSendNum);
      
         break;

      case ATCMD_CY:  //��ѯHFP���ӵ�ǰ��״̬   MG0 -- ready
      
         if(f_McuStart5==0)
         {
            //������DVD: MG
            iSendData[0]='M';
            iSendData[1]='G';
            iSendData[2]='0';
            iSendData[3]=0x0D;               
            iSendData[4]=0x0A;               
            SoftUart_PutBytes(iSendData,5);
         }
         else
         {
            //������DVD: MG3 
            iSendData[0]='M';
            iSendData[1]='G';
            iSendData[2]='3';
            iSendData[3]=0x0D;               
            iSendData[4]=0x0A;               
            SoftUart_PutBytes(iSendData,5);
         }

         break;   
         
      
      case ATCMD_MA: //---- ����/��ͣAV source����, ������A2DP���ӻ�����     
     
         //lflg_DVDCMD = ATCMD_MC;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         //lflg_STM8CMD= 0x0032;
         
         //���͵�����: AA 00 03 02 00 32 C9
         iSendData[0]=0xAA; 
         iSendData[1]=0x00; 
         iSendData[2]=0X03; 
         
         iSendData[3]=0X02; 
         iSendData[4]=0x00;  //lflg_DVDCMD��             
         iSendData[5]=0x32;  //lflg_DVDCMD��           
         iSendData[6]=0xC9;               
         Uart1_PutBytes(iSendData,7); 
         
      
         break;    
      
         
      case ATCMD_MC: // ����/��ͣAV source����, ������A2DP���ӻ�����   

         //if (f_McuStart2==0) 
         if (f_McuStart5==0) 
         {
             //lflg_DVDCMD = ATCMD_MC;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
            lflg_STM8CMD= 0x0032;
      
            //���͵�����: AA 00 03 02 00 32 C9
            iSendData[0]=0xAA;
            iSendData[1]=0x00;
            iSendData[2]=0X03;
         
            iSendData[3]=0X02;         
            iSendData[4]=0x00;  //lflg_DVDCMD��             
            iSendData[5]=0x32;  //lflg_DVDCMD��           
            iSendData[6]=0xC9;               
            Uart1_PutBytes(iSendData,7);           
         }
         else   //-- in use
         {                       
            Delay_nms(250);
            Delay_nms(250);

            f_PlayIO = PC_IDR & (1<<3);            
            if( f_PlayIO==0 ) return;  //�͵�ƽ�˳�

            //lflg_DVDCMD = ATCMD_MC;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
            lflg_STM8CMD= 0x0032;
      
            //���͵�����: AA 00 03 02 00 32 C9
            iSendData[0]=0xAA;
            iSendData[1]=0x00;
            iSendData[2]=0X03;
         
            iSendData[3]=0X02;         
            iSendData[4]=0x00;  //lflg_DVDCMD��             
            iSendData[5]=0x32;  //lflg_DVDCMD��           
            iSendData[6]=0xC9;               
            Uart1_PutBytes(iSendData,7);            
         }         
      
         break;   

        
      case ATCMD_MD: // ����/��ͣAV source����, ������A2DP���ӻ�����               
      
         //lflg_DVDCMD = ATCMD_MC;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         //lflg_STM8CMD= 0x0032;
         
         //���͵�����: AA 00 03 02 00 34 C7
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;         
         iSendData[4]=0x00;  //lflg_DVDCMD��             
         iSendData[5]=0x34;  //lflg_DVDCMD��           
         iSendData[6]=0xC7;               
         Uart1_PutBytes(iSendData,7);
      
         break;     
      
      case ATCMD_ME: // ����/��ͣAV source����, ������A2DP���ӻ�����               
      
         //lflg_DVDCMD = ATCMD_MC;  //ֻ��DVD�������辭MCU����ָ��������踳ֵlflg_DVDCMD����
         //lflg_STM8CMD= 0x0032;
      
         //���͵�����: AA 00 03 02 00 35 C6
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;  //lflg_DVDCMD��             
         iSendData[5]=0x35;  //lflg_DVDCMD��           
         iSendData[6]=0xC6;               
         Uart1_PutBytes(iSendData,7);
         break;     
    
      
      case ATCMD_MF: //Ӧ��MFָ��: 0 -- ���Զ���������, 1 -- �ϵ��Զ�������ƥ��������豸
      
         //������DVD: MF01
         iSendData[0]='M';
         iSendData[1]='F';
         iSendData[2]='0';
         iSendData[3]='1';
         iSendData[4]=0x0D;               
         iSendData[5]=0x0A;               
         SoftUart_PutBytes(iSendData,6);
      
         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);
      
         break;   
         
      
      case ATCMD_MG: 
         
         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);
         
         //if(iHF_Times <= 1 )  // -- nouse
         //{
            flg_MG=1;
         //}

         break;  
      
      case ATCMD_MQ: 

         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      case ATCMD_MV: 

         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      case ATCMD_MW: 
         
         //������DVD: MW20121218 
         iSendData[0]='M';
         iSendData[1]='W';
         iSendData[2]='2';
         iSendData[3]='0';
         iSendData[4]='1';
         iSendData[5]='2';
         iSendData[6]='1';
         iSendData[7]='2';
         iSendData[8]='1';
         iSendData[9]='8';
         iSendData[10]=0x0D;               
         iSendData[11]=0x0A;  
         SoftUart_PutBytes(iSendData,12);         

         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      default: 
      
         //������DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
       
   }
   
}


//����Uart1�����������ݴ���
void DoWith_Uart1(void)
{  //���ݰ�: AA 00 03 02 00 04 F7  ����ģ������ݰ�: 02 00 04  (����+����)

   //uint16 iATCmd;
   uint8 iSendData2[SOFTRX_SIZE]; 
   uint16 iSendNum2;
   uint8 iNameLen;
   
   
   //test
   //Uart1_PutBytes(RX_data2,iRXNum2);  
   
   switch (RX_data2[0])
   {
      case 0x00:   //��������״̬����00
         
         if(RX_data2[1]==0x02) //״̬: �����Ϊ0x02�ĳɹ�����
         {                
            switch (lflg_STM8CMD)
            {
               case 0x0032:  //ATCMD_MC   
                  
                  //if(f_McuStart2 == 0 )  //����
                  if(f_McuStart5 == 0 )  //����
                  {
                     //������DVD: OK                  
                     iSendData2[0]='O';
                     iSendData2[1]='K';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     if(f_McuStart2==0) 
                        f_McuStart2=1;
                  }
                  else
                  {
                     ; //(��)
                  }
                  lflg_DVDCMD=DVDCMD00;  // ��������DVD��ָ���, �ó�ֵ����
                   
                  break;  
                  
                  
               case 0x0016:  ////�B�YHF�B������
                  
                  //if(lflg_DVDCMD == DVDCMD00 )
                  if(iHF_Times == 1 )  //����
                  {
                     //������DVD: IA                  
                     iSendData2[0]='I';
                     iSendData2[1]='A';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     //������DVD: IV                  
                     iSendData2[0]='I';
                     iSendData2[1]='V';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4); 
                  }
                  else
                  {
                     //������DVD: IV                     
                     iSendData2[0]='I';
                     iSendData2[1]='V';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);                      
                  }
                                          
                  //lflg_STM8CMD = STM8CMD00;  //repeat
                  lflg_DVDCMD=DVDCMD00;  // ��������DVD��ָ���, �ó�ֵ����
                  break;    
                  
                  
               case 0x0050:  //���״̬����
                  
                  if(lflg_DVDCMD == ATCMD_CA )
                  {
                     //������DVD: II                  
                     iSendData2[0]='I';
                     iSendData2[1]='I';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     lflg_DVDCMD=DVDCMD00;  // ��������DVD��ָ���, �ó�ֵ����
                  } 
                  else if(lflg_DVDCMD == ATCMD_CB )
                  {
                     //������DVD: IJ                  
                     iSendData2[0]='I';
                     iSendData2[1]='J';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     lflg_DVDCMD=DVDCMD00;  // ��������DVD��ָ���, �ó�ֵ����
                  }
                  
                  break;   
               /*   
               case 0x000C:  //ATCMD_CH
                  
                  //������DVD: OK                  
                  iSendData2[0]='O';
                  iSendData2[1]='K';
                  iSendData2[2]=0x0D;
                  iSendData2[3]=0x0A;
                  SoftUart_PutBytes(iSendData2,4);  

                  iCH_Times++;
                  if(iCH_Times==2)
                  {
                     lflg_DVDCMD = DVDCMD00;  //�ó�ֵ
                     iCH_Times=0;
                  }
                   
                  break;       
                  
               default: break; 
               */
                  
            }  //switch (lflg_STM8CMD)              
            
            lflg_STM8CMD = STM8CMD00;
             
         } //if(RX_data2[1]==0x02)     
         


         if(RX_data2[1]==0x05) //״̬: �����Ϊ0x05�ĳɹ�����
         { //���Ϳ���4��, �豸���Ƶ�
            
            //������DVD: IS                  
            iSendData2[0]='I';
            iSendData2[1]='S';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;
            SoftUart_PutBytes(iSendData2,4);  
            
            //������DVD: IA                  
            iSendData2[0]='I';
            iSendData2[1]='A';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;                  
            SoftUart_PutBytes(iSendData2,4);  
            
            //������DVD: zemy                  
            iSendData2[0]='z';
            iSendData2[1]='e';
            iSendData2[2]='m';
            iSendData2[3]='y';
            iSendData2[4]=0x0D;
            iSendData2[5]=0x0A;
            SoftUart_PutBytes(iSendData2,6);  
           
            //������DVD: Bluetooth
            memcpy( iSendData2,&CMDTEXT3[4],16);  
            iSendData2[16]=0x0D;
            iSendData2[17]=0x0A;
            SoftUart_PutBytes(iSendData2,18);                     
         }
         
         break;

      case 0x01:   //��������״̬����01      

           if(RX_data2[1]==0x05) //״̬: HF������
           {
              ;
              
              //-----------------------------------------
              ////����������ʾ  -- ����0x17����
              ////������DVD: IV                  
              //iSendData2[0]='I';
              //iSendData2[1]='V';
              //iSendData2[2]=0x0D;
              //iSendData2[3]=0x0A;
              //SoftUart_PutBytes(iSendData2,4);  
              
              ////Delay_10us();
              
              ////HFP���ӳɹ�
              ////������DVD: IB                  
              //iSendData2[0]='I';
              //iSendData2[1]=0x42; //'B'
              //iSendData2[2]=0x0D;
              //iSendData2[3]=0x0A;
              //SoftUart_PutBytes(iSendData2,4);  
             //-------------------------------------------
              
              
              
              //flg_Connected =1;
              
              //Delay_10us();
              
           }  
       
           if(RX_data2[1]==0x07) //״̬: HF�Ѷ���
           {
              //HFP���ӶϿ���ʾ
              //������DVD: IA                  
              iSendData2[0]='I';
              iSendData2[1]='A';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4);  
              
              //flg_Connected =0;
              //flg_PlayReady=0;              
           }  
       
         break;
        
      case 0x02:   //��������״̬����02 
         
          if(RX_data2[1]==0x00 && RX_data2[2]==0x00) //״̬:  �绰�ѹҶ�
         { 
            //������DVD: IF
            iSendData2[0]='I';
            iSendData2[1]='F';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
            
            
            //������DVD: IB
            iSendData2[0]='I';
            iSendData2[1]='B';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
         }
         
         
         if(RX_data2[1]==0x00 && RX_data2[2]==0x03) //״̬: ��̖��
         { 
            //������DVD: IC
            iSendData2[0]='I';
            iSendData2[1]='C';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
            
            if ( (lflg_DVDCMD == ATCMD_CW) || (lflg_DVDCMD == ATCMD_CH) )
            {
               //������DVD: IR xxxxx  (����xxxxxΪ�绰����, �����仯)
               iSendData2[0]='I';
               iSendData2[1]='R';
               //memcpy( &iSendData2[2],&iTelNo,iRXNum2-6);                           
               memcpy( &iSendData2[2],&iTelNo, iTelLen);   
            
               iSendData2[iTelLen+2]=0x0D;
               iSendData2[iTelLen+3]=0x0A;

               iSendNum2= iTelLen+4 ;  
               SoftUart_PutBytes(iSendData2,iSendNum2); 
            
               if (lflg_DVDCMD == ATCMD_CW)
               {
                  lflg_DVDCMD = DVDCMD00;  //�ó�ֵ  
               }
               else
               {
                  iCH_Times++;
                  if(iCH_Times==2)
                  {
                     lflg_DVDCMD = DVDCMD00;  //�ó�ֵ
                     iCH_Times=0;
                  }
                }
               
            }
            else //if ( lflg_DVDCMD == DVDCMD00  )
            {
               //������DVD: IR
               iSendData2[0]='I';
               iSendData2[1]='R';
               iSendData2[2]=0x0D;
               iSendData2[3]=0x0A;
               SoftUart_PutBytes(iSendData2,4); 
            }
          
         }               
         
         if(RX_data2[1]==0x00 && RX_data2[2]==0x04) //״̬: ͨ����
         { 
            //������DVD: IG  (����xxxxxΪ�绰����, �����仯)
            iSendData2[0]='I';
            iSendData2[1]='G';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);  
         }
         
         break;
         
         
      case 0x17:  // //��������״̬����17    --�ֻ�����
         
              //����������ʾ  -- ����2�������Ǵ�01 05 �Ƶ�����
              //������DVD: IV                  
              iSendData2[0]='I';
              iSendData2[1]='V';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4);  
              
              
              //HFP���ӳɹ�
              //������DVD: IB                  
              iSendData2[0]='I';
              iSendData2[1]='B';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4); 
              
              
         //�����ֻ����� MX0 xxxxx
         iNameLen=iRXNum2-2;
         if(iNameLen>8)
            iNameLen=8;        
         
         iSendData2[0]='M';
         iSendData2[1]='X';
         iSendData2[2]=RX_data2[1]+0x30;
         memset( &iSendData2[3],'1',22); 
         
         memcpy( &iSendData2[3],&RX_data2[2],iNameLen);                 
         memcpy( &iSendData2[15],&RX_data2[2],iNameLen);   
         iSendData2[23]=0x0D;
         iSendData2[24]=0x0A;   
         
         SoftUart_PutBytes(iSendData2,25); 
         

         //HFP���ӳɹ�
         //������DVD: IB                  
         iSendData2[0]='I';
         iSendData2[1]='B';
         iSendData2[2]=0x0D;
         iSendData2[3]=0x0A;
         SoftUart_PutBytes(iSendData2,4); 

         flg_PlayReady=1;
         
         break;
      
      case 0x0C:   //��������״̬����0C     
         
         //if( (RX_data2[1]==0x04) && (iHF_Times<3) ) //״̬: ��������״̬
         //{ 
         //   //�յ�����������Ϣ��, �ٷ����ݸ�����, ��ȡ�豸���Ƶ�
         //   Uart1_PutBytes(CMDTEXT1,7);  //����               
         //   Uart1_PutBytes(CMDTEXT2,7);  //A2DP�������               
         //   Uart1_PutBytes(CMDTEXT3,21); //�豸����: bluetooth + 7 x 00                
         //}
         
         if(RX_data2[1]==0x04 && f_McuStart1==0) //״̬: ��������״̬
         { 
            f_McuStart1=1;
         }
        
         
         break;
         
      default: break;  
      
   }         
   
   
}

