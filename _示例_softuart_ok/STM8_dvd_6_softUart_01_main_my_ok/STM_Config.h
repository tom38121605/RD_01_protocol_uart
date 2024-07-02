#ifndef __STM_CONFIG_H
#define __STM_CONFIG_H


//============= 主控芯片的头文件 =====================
//#include <iostm8s208r8.h>
#include <iostm8s003f3.h>

#include <stdbool.h>
#include <intrinsics.h>


//=============自定义主控芯片的头文件 =====================
#include "stm8s_IC.h"


//============= c语言库文件 =====================
#include <string.h>

//============= 公共模块头文件 =====================
#include "Public.h"
#include "Delay_16M.h"


//============= 功能模块头文件 =====================
#include "Clock.h"
#include "LedIO.h"
#include "ExIntIO.h"

//#include "App.h"
#include "Flash.h"
#include "Timer1.h"

#include "Uart1.h"
//#include "Uart3.h"
#include "SoftUart.h"


//#include ""
//#include ""
//#include ""
//#include ""



#endif