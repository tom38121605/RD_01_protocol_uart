//只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量, 如: lflg_DVDCMD = ATCMD_MC; 
//蓝牙处理DVD的指令后, 置初值处理, 如: lflg_DVDCMD=oxFFFF;  

//注意本工程如把timer1.c和ExIntIO.c整合在softUart.c中, 则这2个文件一定要remove出本工程


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


//MCU 开机3句
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
         
      
   //设置主时钟 
   Clock_HSI_Ini();  
  
   //__disable_interrupt(); 
   
   
   //模拟串口初始化
   SoftUart_Init(); 
   
   
   //设置PD4为推挽快速输出, 初始低电平
   PD_DDR|=(1<<4);   // 设置数据方向寄存器 1--输出，0--输入 
   PD_CR1|=(1<<4);   // 设置推挽输出 
   PD_CR2|=(1<<4);   // 设置输出频率 1--10M(Fast)，0--2M
   PD_ODR&=~(1<<4);   // 设置初始电平为低电平 
  

   //设置PC3为带上拉输入, 屏蔽外部中断  
   PC_DDR&=~(0<<3);   // 设置数据方向寄存器 1--输出，0--输入
   PC_CR1|=(1<<3);    // 设置带上拉电阻输入   
   PC_CR2&=~(1<<3);   // 使能外部中断      
   
   //串口初始化, 设置波特率
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
   
   //输出INT波形 420ms高 + 9 * 160ms(5低4高) + 高
   PD_ODR|=(1<<4); //高电平 
   Delay_nms(420);       
   PD_ODR&=~(1<<4); //低电平 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //高电平 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //低电平 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //高电平 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //低电平 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //高电平 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //低电平 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //高电平 
   Delay_nms(160);       
   PD_ODR&=~(1<<4); //低电平 
   Delay_nms(160);
   
   PD_ODR|=(1<<4); //高电平    

   
   while(1)  
   {   //test 5.0us //3.0us 
      
      //test count time
      PD_ODR^=(1<<4);   
      
      
      //scan softuart
      SoftUart_Receive();        
            
      //模拟串口收到DVD消息的处理
      if (flg_Reced==1)   
      {  
         DoWith_SoftUart();            
         flg_Reced=0;      
      }            
      
      //Uart1收到蓝牙消息的处理
      if (flg_Received==1)  
      {//数据包: AA 00 03 02 00 04 F7  到本模块的数据包: 02 00 04  (命令+参数)
         
         DoWith_Uart1();
         flg_Received=0;        
      }  
     
      // MCU开机发送数据出来
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
         //收到蓝牙启动信息后, 再发数据给蓝牙, 提取设备名称等
         Uart1_PutBytes(CMDTEXT1,7);  //断线               
         Uart1_PutBytes(CMDTEXT2,7);  //A2DP连结断线               
         Uart1_PutBytes(CMDTEXT3,21); //设备名称: bluetooth + 7 x 00  
         
         f_McuStart1=2;
      }  
      
      
      //等待处理AT#MC指令的完成
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
      
          
      //发送3条AA 00 03 02 00 16 E5 指令到蓝牙
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
      
               if(flg_MG<1) //根据需要<1,2,3等(在AT#MG处理中相应修改flg_MG=1,2,3)
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
               
                  if(iHF_Times==3) f_McuStart5=1;  //开机过程结束 
               }
               
            }
         } 
         
      }      
      
        
      //播放引脚检查
      if (flg_PlayReady==1)
      {
         
         flg_PlayIO_New = ( PC_IDR & (1<<3) );
         
         if( flg_PlayIO_New >  flg_PlayIO_Old ) //变高
         {     
            //发送至DVD: MB                  
            iOutData[0]='M';
            iOutData[1]='B';
            iOutData[2]=0x0D;
            iOutData[3]=0x0A;
            SoftUart_PutBytes(iOutData,4); 
            
            //flg_Playing=1;
            
            flg_PlayIO_Old=flg_PlayIO_New;
         }
         else if( flg_PlayIO_New <  flg_PlayIO_Old ) //变低
         {
            //发送至DVD: MA                  
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


//模拟串口接收DVD数据处理
void DoWith_SoftUart()
{ //格式: AT#CW10086 0D 0A
   uint16 iATCmd;
   uint8 iSendData[SOFTRX_SIZE]; 
   uint16 iSendNum;
   uint8 i;
   uint16 iTempSum;
   
   //test
   //SoftUart_PutBytes(iRecData2,iRecNum2); 

   iATCmd = (uint16)(iRecData2[3]*256+iRecData2[4]);  //如: CW
   switch (iATCmd)
   {
      case ATCMD_CA:    //配对
      
         lflg_DVDCMD = ATCMD_CA;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         lflg_STM8CMD= 0x0050;
      
         //发送到蓝牙: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x50;   //lflg_DVDCMD低           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);  
      
         break;
         
      
      case ATCMD_CB:    //取消配对
      
         lflg_DVDCMD = ATCMD_CB;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         lflg_STM8CMD= 0x0050;
      
         //发送到蓝牙: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x50;   //lflg_DVDCMD低           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);  
      
         break;
      
      case ATCMD_CD:    //断开与手机的蓝牙连接
      
         //lflg_DVDCMD = ATCMD_CD;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         lflg_STM8CMD= 0x0017;
      
         //发送到蓝牙: AA 00 03 02 00 17 E4
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x17;   //lflg_DVDCMD低           
         iSendData[6]=0xE4;               
         Uart1_PutBytes(iSendData,7); 
      
      
         //发送到蓝牙: AA 00 03 02 00 50 AB
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x50;   //lflg_DVDCMD低           
         iSendData[6]=0xAB;               
         Uart1_PutBytes(iSendData,7);       
      
         break;
         
      case ATCMD_CG:    //挂断
         
         //lflg_DVDCMD = ATCMD_CG;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         //lflg_STM8CMD= 0x0002;
      
         //发送到蓝牙: AA 00 03 02 00 02 F9
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x02;   //lflg_DVDCMD低           
         iSendData[6]=0xF9;               
         Uart1_PutBytes(iSendData,7); 
      
      
         //发送到蓝牙: AA 00 03 02 00 06 F5
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x06;   //lflg_DVDCMD低           
         iSendData[6]=0xF5;               
         Uart1_PutBytes(iSendData,7);       
      
         break;       
      
      case ATCMD_CH:    //重拨电话号码
      
         lflg_DVDCMD = ATCMD_CH;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         lflg_STM8CMD= 0x000C;
         
         //发送到蓝牙: AA 00 03 02 00 0C EF
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;      
         iSendData[4]=0x00;   //lflg_DVDCMD高             
         iSendData[5]=0x0C;   //lflg_DVDCMD低           
         iSendData[6]=0xEF;               
         Uart1_PutBytes(iSendData,7); 
      
         break;      
         
      case ATCMD_CW:    //电话拨号
      
         lflg_DVDCMD = ATCMD_CW;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         
         iTelLen=iRecNum2-7;

         //发送到蓝牙: AA 00 长度 00 00 xxxxx 电话号码
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
      
         iSendData[iSendNum-1]= (uint8)( ~((uint8)iTempSum) +1 );  //取得校验和
         
         Uart1_PutBytes(iSendData,iSendNum);
      
         break;

      case ATCMD_CY:  //查询HFP连接当前的状态   MG0 -- ready
      
         if(f_McuStart5==0)
         {
            //发送至DVD: MG
            iSendData[0]='M';
            iSendData[1]='G';
            iSendData[2]='0';
            iSendData[3]=0x0D;               
            iSendData[4]=0x0A;               
            SoftUart_PutBytes(iSendData,5);
         }
         else
         {
            //发送至DVD: MG3 
            iSendData[0]='M';
            iSendData[1]='G';
            iSendData[2]='3';
            iSendData[3]=0x0D;               
            iSendData[4]=0x0A;               
            SoftUart_PutBytes(iSendData,5);
         }

         break;   
         
      
      case ATCMD_MA: //---- 播放/暂停AV source歌曲, 作用于A2DP连接基础上     
     
         //lflg_DVDCMD = ATCMD_MC;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         //lflg_STM8CMD= 0x0032;
         
         //发送到蓝牙: AA 00 03 02 00 32 C9
         iSendData[0]=0xAA; 
         iSendData[1]=0x00; 
         iSendData[2]=0X03; 
         
         iSendData[3]=0X02; 
         iSendData[4]=0x00;  //lflg_DVDCMD高             
         iSendData[5]=0x32;  //lflg_DVDCMD低           
         iSendData[6]=0xC9;               
         Uart1_PutBytes(iSendData,7); 
         
      
         break;    
      
         
      case ATCMD_MC: // 播放/暂停AV source歌曲, 作用于A2DP连接基础上   

         //if (f_McuStart2==0) 
         if (f_McuStart5==0) 
         {
             //lflg_DVDCMD = ATCMD_MC;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
            lflg_STM8CMD= 0x0032;
      
            //发送到蓝牙: AA 00 03 02 00 32 C9
            iSendData[0]=0xAA;
            iSendData[1]=0x00;
            iSendData[2]=0X03;
         
            iSendData[3]=0X02;         
            iSendData[4]=0x00;  //lflg_DVDCMD高             
            iSendData[5]=0x32;  //lflg_DVDCMD低           
            iSendData[6]=0xC9;               
            Uart1_PutBytes(iSendData,7);           
         }
         else   //-- in use
         {                       
            Delay_nms(250);
            Delay_nms(250);

            f_PlayIO = PC_IDR & (1<<3);            
            if( f_PlayIO==0 ) return;  //低电平退出

            //lflg_DVDCMD = ATCMD_MC;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
            lflg_STM8CMD= 0x0032;
      
            //发送到蓝牙: AA 00 03 02 00 32 C9
            iSendData[0]=0xAA;
            iSendData[1]=0x00;
            iSendData[2]=0X03;
         
            iSendData[3]=0X02;         
            iSendData[4]=0x00;  //lflg_DVDCMD高             
            iSendData[5]=0x32;  //lflg_DVDCMD低           
            iSendData[6]=0xC9;               
            Uart1_PutBytes(iSendData,7);            
         }         
      
         break;   

        
      case ATCMD_MD: // 播放/暂停AV source歌曲, 作用于A2DP连接基础上               
      
         //lflg_DVDCMD = ATCMD_MC;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         //lflg_STM8CMD= 0x0032;
         
         //发送到蓝牙: AA 00 03 02 00 34 C7
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;         
         iSendData[4]=0x00;  //lflg_DVDCMD高             
         iSendData[5]=0x34;  //lflg_DVDCMD低           
         iSendData[6]=0xC7;               
         Uart1_PutBytes(iSendData,7);
      
         break;     
      
      case ATCMD_ME: // 播放/暂停AV source歌曲, 作用于A2DP连接基础上               
      
         //lflg_DVDCMD = ATCMD_MC;  //只有DVD的命令需经MCU发送指令到蓝牙才需赋值lflg_DVDCMD变量
         //lflg_STM8CMD= 0x0032;
      
         //发送到蓝牙: AA 00 03 02 00 35 C6
         iSendData[0]=0xAA;
         iSendData[1]=0x00;
         iSendData[2]=0X03;
         
         iSendData[3]=0X02;
         iSendData[4]=0x00;  //lflg_DVDCMD高             
         iSendData[5]=0x35;  //lflg_DVDCMD低           
         iSendData[6]=0xC6;               
         Uart1_PutBytes(iSendData,7);
         break;     
    
      
      case ATCMD_MF: //应答MF指令: 0 -- 不自动接听来电, 1 -- 上电自动连接已匹配的蓝牙设备
      
         //发送至DVD: MF01
         iSendData[0]='M';
         iSendData[1]='F';
         iSendData[2]='0';
         iSendData[3]='1';
         iSendData[4]=0x0D;               
         iSendData[5]=0x0A;               
         SoftUart_PutBytes(iSendData,6);
      
         //发送至DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);
      
         break;   
         
      
      case ATCMD_MG: 
         
         //发送至DVD: OK 
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

         //发送至DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      case ATCMD_MV: 

         //发送至DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      case ATCMD_MW: 
         
         //发送至DVD: MW20121218 
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

         //发送至DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
  
      default: 
      
         //发送至DVD: OK 
         iSendData[0]='O';
         iSendData[1]='K';
         iSendData[2]=0x0D;               
         iSendData[3]=0x0A;  
         SoftUart_PutBytes(iSendData,4);

         break;   
       
   }
   
}


//串口Uart1接收蓝牙数据处理
void DoWith_Uart1(void)
{  //数据包: AA 00 03 02 00 04 F7  到本模块的数据包: 02 00 04  (命令+参数)

   //uint16 iATCmd;
   uint8 iSendData2[SOFTRX_SIZE]; 
   uint16 iSendNum2;
   uint8 iNameLen;
   
   
   //test
   //Uart1_PutBytes(RX_data2,iRXNum2);  
   
   switch (RX_data2[0])
   {
      case 0x00:   //蓝牙返回状态命令00
         
         if(RX_data2[1]==0x02) //状态: 命令号为0x02的成功返回
         {                
            switch (lflg_STM8CMD)
            {
               case 0x0032:  //ATCMD_MC   
                  
                  //if(f_McuStart2 == 0 )  //开机
                  if(f_McuStart5 == 0 )  //开机
                  {
                     //发送至DVD: OK                  
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
                     ; //(空)
                  }
                  lflg_DVDCMD=DVDCMD00;  // 蓝牙处理DVD的指令后, 置初值处理
                   
                  break;  
                  
                  
               case 0x0016:  ////連結HF連線返回
                  
                  //if(lflg_DVDCMD == DVDCMD00 )
                  if(iHF_Times == 1 )  //开机
                  {
                     //发送至DVD: IA                  
                     iSendData2[0]='I';
                     iSendData2[1]='A';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     //发送至DVD: IV                  
                     iSendData2[0]='I';
                     iSendData2[1]='V';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4); 
                  }
                  else
                  {
                     //发送至DVD: IV                     
                     iSendData2[0]='I';
                     iSendData2[1]='V';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);                      
                  }
                                          
                  //lflg_STM8CMD = STM8CMD00;  //repeat
                  lflg_DVDCMD=DVDCMD00;  // 蓝牙处理DVD的指令后, 置初值处理
                  break;    
                  
                  
               case 0x0050:  //配对状态返回
                  
                  if(lflg_DVDCMD == ATCMD_CA )
                  {
                     //发送至DVD: II                  
                     iSendData2[0]='I';
                     iSendData2[1]='I';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     lflg_DVDCMD=DVDCMD00;  // 蓝牙处理DVD的指令后, 置初值处理
                  } 
                  else if(lflg_DVDCMD == ATCMD_CB )
                  {
                     //发送至DVD: IJ                  
                     iSendData2[0]='I';
                     iSendData2[1]='J';
                     iSendData2[2]=0x0D;
                     iSendData2[3]=0x0A;
                     SoftUart_PutBytes(iSendData2,4);  
                     
                     lflg_DVDCMD=DVDCMD00;  // 蓝牙处理DVD的指令后, 置初值处理
                  }
                  
                  break;   
               /*   
               case 0x000C:  //ATCMD_CH
                  
                  //发送至DVD: OK                  
                  iSendData2[0]='O';
                  iSendData2[1]='K';
                  iSendData2[2]=0x0D;
                  iSendData2[3]=0x0A;
                  SoftUart_PutBytes(iSendData2,4);  

                  iCH_Times++;
                  if(iCH_Times==2)
                  {
                     lflg_DVDCMD = DVDCMD00;  //置初值
                     iCH_Times=0;
                  }
                   
                  break;       
                  
               default: break; 
               */
                  
            }  //switch (lflg_STM8CMD)              
            
            lflg_STM8CMD = STM8CMD00;
             
         } //if(RX_data2[1]==0x02)     
         


         if(RX_data2[1]==0x05) //状态: 命令号为0x05的成功返回
         { //发送开机4句, 设备名称等
            
            //发送至DVD: IS                  
            iSendData2[0]='I';
            iSendData2[1]='S';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;
            SoftUart_PutBytes(iSendData2,4);  
            
            //发送至DVD: IA                  
            iSendData2[0]='I';
            iSendData2[1]='A';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;                  
            SoftUart_PutBytes(iSendData2,4);  
            
            //发送至DVD: zemy                  
            iSendData2[0]='z';
            iSendData2[1]='e';
            iSendData2[2]='m';
            iSendData2[3]='y';
            iSendData2[4]=0x0D;
            iSendData2[5]=0x0A;
            SoftUart_PutBytes(iSendData2,6);  
           
            //发送至DVD: Bluetooth
            memcpy( iSendData2,&CMDTEXT3[4],16);  
            iSendData2[16]=0x0D;
            iSendData2[17]=0x0A;
            SoftUart_PutBytes(iSendData2,18);                     
         }
         
         break;

      case 0x01:   //蓝牙返回状态命令01      

           if(RX_data2[1]==0x05) //状态: HF已连线
           {
              ;
              
              //-----------------------------------------
              ////正在连接提示  -- 移至0x17命令
              ////发送至DVD: IV                  
              //iSendData2[0]='I';
              //iSendData2[1]='V';
              //iSendData2[2]=0x0D;
              //iSendData2[3]=0x0A;
              //SoftUart_PutBytes(iSendData2,4);  
              
              ////Delay_10us();
              
              ////HFP连接成功
              ////发送至DVD: IB                  
              //iSendData2[0]='I';
              //iSendData2[1]=0x42; //'B'
              //iSendData2[2]=0x0D;
              //iSendData2[3]=0x0A;
              //SoftUart_PutBytes(iSendData2,4);  
             //-------------------------------------------
              
              
              
              //flg_Connected =1;
              
              //Delay_10us();
              
           }  
       
           if(RX_data2[1]==0x07) //状态: HF已断线
           {
              //HFP连接断开提示
              //发送至DVD: IA                  
              iSendData2[0]='I';
              iSendData2[1]='A';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4);  
              
              //flg_Connected =0;
              //flg_PlayReady=0;              
           }  
       
         break;
        
      case 0x02:   //蓝牙返回状态命令02 
         
          if(RX_data2[1]==0x00 && RX_data2[2]==0x00) //状态:  电话已挂断
         { 
            //发送至DVD: IF
            iSendData2[0]='I';
            iSendData2[1]='F';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
            
            
            //发送至DVD: IB
            iSendData2[0]='I';
            iSendData2[1]='B';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
         }
         
         
         if(RX_data2[1]==0x00 && RX_data2[2]==0x03) //状态: 撥號中
         { 
            //发送至DVD: IC
            iSendData2[0]='I';
            iSendData2[1]='C';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);    
            
            if ( (lflg_DVDCMD == ATCMD_CW) || (lflg_DVDCMD == ATCMD_CH) )
            {
               //发送至DVD: IR xxxxx  (其中xxxxx为电话号码, 具体会变化)
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
                  lflg_DVDCMD = DVDCMD00;  //置初值  
               }
               else
               {
                  iCH_Times++;
                  if(iCH_Times==2)
                  {
                     lflg_DVDCMD = DVDCMD00;  //置初值
                     iCH_Times=0;
                  }
                }
               
            }
            else //if ( lflg_DVDCMD == DVDCMD00  )
            {
               //发送至DVD: IR
               iSendData2[0]='I';
               iSendData2[1]='R';
               iSendData2[2]=0x0D;
               iSendData2[3]=0x0A;
               SoftUart_PutBytes(iSendData2,4); 
            }
          
         }               
         
         if(RX_data2[1]==0x00 && RX_data2[2]==0x04) //状态: 通话中
         { 
            //发送至DVD: IG  (其中xxxxx为电话号码, 具体会变化)
            iSendData2[0]='I';
            iSendData2[1]='G';
            iSendData2[2]=0x0D;
            iSendData2[3]=0x0A;

            //iSendNum2= 4 ;  
            SoftUart_PutBytes(iSendData2,4);  
         }
         
         break;
         
         
      case 0x17:  // //蓝牙返回状态命令17    --手机名称
         
              //正在连接提示  -- 下面2个命令是从01 05 移到这里
              //发送至DVD: IV                  
              iSendData2[0]='I';
              iSendData2[1]='V';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4);  
              
              
              //HFP连接成功
              //发送至DVD: IB                  
              iSendData2[0]='I';
              iSendData2[1]='B';
              iSendData2[2]=0x0D;
              iSendData2[3]=0x0A;
              SoftUart_PutBytes(iSendData2,4); 
              
              
         //发送手机名称 MX0 xxxxx
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
         

         //HFP连接成功
         //发送至DVD: IB                  
         iSendData2[0]='I';
         iSendData2[1]='B';
         iSendData2[2]=0x0D;
         iSendData2[3]=0x0A;
         SoftUart_PutBytes(iSendData2,4); 

         flg_PlayReady=1;
         
         break;
      
      case 0x0C:   //蓝牙返回状态命令0C     
         
         //if( (RX_data2[1]==0x04) && (iHF_Times<3) ) //状态: 电量满格状态
         //{ 
         //   //收到蓝牙启动信息后, 再发数据给蓝牙, 提取设备名称等
         //   Uart1_PutBytes(CMDTEXT1,7);  //断线               
         //   Uart1_PutBytes(CMDTEXT2,7);  //A2DP连结断线               
         //   Uart1_PutBytes(CMDTEXT3,21); //设备名称: bluetooth + 7 x 00                
         //}
         
         if(RX_data2[1]==0x04 && f_McuStart1==0) //状态: 电量满格状态
         { 
            f_McuStart1=1;
         }
        
         
         break;
         
      default: break;  
      
   }         
   
   
}

