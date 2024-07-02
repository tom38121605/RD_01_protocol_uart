#ifndef __PUBLIC_H
#define __PUBLIC_H



//#define STM8S208       	 
//#define STM8S207       
//#define STM8S007       
//#define STM8AF52Ax    
//#define STM8AF62Ax    
//#define STM8S105       
//#define STM8S005       
//#define STM8AF626x 
//#define STM8S103 
//#define STM8S003 
//#define STM8S903


//=== 以下常用库的引用这里只做参考(keep) ===
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>

#ifndef  MASTER_FREQ
   #define  MASTER_FREQ    (16000000)  //定义外部晶振，以MHz为单位
#endif  

#define	SETBIT(x,y) (x|=(1<<y))      //set bit y in byte x
#define	CLRBIT(x,y) (x&=(~(1<<y)))   //clear bit y in byte x
#define	CHKBIT(x,y) (x&(1<<y))       //check bit y in byte x
#define	REVBIT(x,y) (x^=(1<<y))       //reverse bit y in byte x

typedef unsigned char uint8 ;
typedef unsigned int uint16;
typedef unsigned long uint32;

//typedef unsigned char U_8 ;
//typedef signed char U_8S;
//typedef unsigned int U_16;
//typedef signed int U_16S;
//typedef unsigned long U_32;
//typedef signed long U_32S;

//Typedef float FP_32;
//Typedef double FP_64;

#endif
