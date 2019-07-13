//*********系统头文件****************************************************
#include "HGOS.h"
#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208)||\
	defined(STM8S105)//2014-03-28  BY ZPYWS
	#include "STM8S.h"
#elif defined(STM8L101)//2013-08-27  BY ZPYWS
	#include "STM8L10x.h"
#elif defined(STM8L152)//2013-08-27  BY ZPYWS
	#include "STM8L15x.h"
#else
	#error "Unknow CPU! By zpyws."
#endif
#include "STM8Lib.h"
//******************************************************************************************************************************
#define F_CPU                   (16000000UL)//CPU时钟
#define F_PCLK                  (16000000UL)//外设时钟
//*********用户头文件****************************************************
#include "LED.h"
#include "Uart.h"
#include "TIM4.h"
#include "zpyws.h"
#include "WDT.h"
#include "time.h"
#include "uart_app.h"
//******************************************************************************************************************************
