#include "common_zpyws.h"
#include "ciu98m25.h"
/************************************************************************************************************
2013-03-05  17:00 完成YOS FOR STM8L152C6T6版本的移植
2013-03-07  11:41 YOS内存管理函数和邮箱功能测试ro-code=4976 ro-data=747 rw-data=1039
2013-08-27  11:13 YOS-130822B内核，ST官方头文件，所有文件基本STM8之间移植无需修改code=4805 const=730 data=1060
2014-03-29  13:24 内核131023A，STM8接口140329A，此为STM8S105样本程序code=5450 const-654 data=989
2014-04-22  10:03 STM8S103+YOS-STM8S103-V150421A debug版code=5078 const=740 data=916
2014-04-22  10:06 STM8S103+YOS-STM8S103-V150421A release版code=4035 const=740 data=916
************************************************************************************************************/
#define UART_PRINT_BOOT_INFO        0
#define UART_PRINT_OS_RUN_TIME		0

#define OS_TICK_FROM_TIM4
//******************************************************************************************************************************
//OS_STK_t TaskAStack[150];
//OS_STK_t TaskBStack[80];
//OS_STK_t TaskCStack[100];
OS_STK_t TaskUart1Stack[90];
OS_STK_t TaskStartStack[80];
//******************************************************************************************************************************
static void OSCPUInit(void)//配置系统运行频率，SysTick中断间隔等
{
	InitPeripheralClock();
	SetHsiDiv(HSI_DIV_1, CPU_DIV_1);//16MHz fmaster
#if defined(OS_TICK_FROM_TIM4)//系统时钟来自TIM4
	InitTimer4(7, (1000000UL/OS_TICKS_PER_SEC)>>3);//PS=2^7=128分频，125*8=1000uS中断一次
#else
	InitTimer2(4, 1000000UL/OS_TICKS_PER_SEC);//16分频，定时10ms
#endif

#if OS_CPU_STAT_EN > 0
	OSCPUStatInit();//统计CPU全速运行时的性能
#endif
}
//******************************************************************************************************************************
static void Initial(void)
{
	OSCPUInit();
	InitLED();
	InitUart1(115200);
#if UART_PRINT_BOOT_INFO > 0
//  	UART1_PRINT_STRING("YOS For STM8S103 Starting。。。\r\n");
  	UART1_PRINT_STRING("YOS Version: ");
  	UART1_PRINT_STRING(OS_VERSION);
  	UART1_PRINT_STRING("  By zpyws \r\n");

  	UART1_PRINT_STRING("YOS Port Version: ");
  	UART1_PRINT_STRING(OS_PORT_VERSION);
  	UART1_PRINT_STRING("  By zpyws \r\n");
    
  	UART1_PRINT_STRING("Copyright[后港电子]All Rights Reserved\r\n");
  	UART1_PRINT_STRING("http://shop107972111.taobao.com/\r\n");
#endif
}
//******************************************************************************************************************************
#if OS_CPU_STAT_EN > 0
static void PrintCPUUsage(void)
{
	OSSemPend( &SemUart1Tx, 0 );

	UART1_PRINT_STRING_RAW("CPU使用率为");

	Uart1PutUint8AsDecimal(OSCPUUsage);
	UART1_PRINT_STRING_RAW(".");
	Uart1PutUint8AsDecimal(OSCPUUsageExt);
	UART1_PRINT_STRING_RAW("%\r\n");

	OSSemPost(&SemUart1Tx);//释放资源
}
#endif
//******************************************************************************************************************************
#if OS_STK_CHK_EN > 0
static void PrintStackUsage(void)
{
	uint8 i;
	OS_STK_DATA_t StkDat;
	uint8 str[5];
	uint8 len;
	
	
	OSSemPend( &SemUart1Tx, 0 );

	UART1_PRINT_STRING_RAW("******************************************\r\n");
	for(i=0; i<=OS_MAX_TASKS; i++)
	{
		if( OSTaskStkChk(i, &StkDat) != OS_NO_ERR )continue;//读取任务的堆栈使用情况
//-------------------------------------------------------		
		UART1_PRINT_STRING_RAW("Task");
		Uart1PutUint8AsDecimal(i);
		UART1_PRINT_STRING_RAW(":");
			
	 	len = SprintUint16AsDecimal( StkDat.OSUsed, str );//输出为ASCII的总个数
		Uart1PutRaw(str,len);
		UART1_PRINT_STRING_RAW(" BytesUsed,");
		
	 	len = SprintUint16AsDecimal( StkDat.OSFree, str );//输出为ASCII的总个数
		Uart1PutRaw(str,len);
		UART1_PRINT_STRING_RAW(" BytesFree");
		UART1_PRINT_STRING_RAW("\r\n");
//-------------------------------------------------------		
	}
	UART1_PRINT_STRING_RAW("******************************************\r\n");

	OSSemPost(&SemUart1Tx);//释放资源
}
#endif
//******************************************************************************************************************************
#if 0
ROM uint8 test[] = "$GPGGA,095813.000,2431.6875,N,11811.1214,E,1,8,0.95,100.4,M,12.1,M,,*5F\r\n";

static __TASK void TaskA(void *para)
{
	while(1)
	{
//		Uart1Send((uint8 *)test,sizeof(test)-1);
		OSTimeDly(OS_TICKS_PER_SEC/1);
	}
}
//************************************************************************************************************
static __TASK void TaskB(void *para)
{
	while(1)
	{
        OSTimeDly(OS_TICKS_PER_SEC/50);	
	}
}
#endif
//************************************************************************************************************
//__TASK void TaskC(void *para)
//{
////	WDT_Init();
//	while(1)
//	{
//		OSTimeDly(OS_TICKS_PER_SEC/2);	
////		WDT_Feed();
//		LED1_TOG();
//	}
//}
//************************************************************************************************************
__TASK void TaskUart1(void *para)
{
	while(1)
	{
		OSSemPend(&SemUart1RxOver, 0);//无限等待
		UartRxDataProcess(Uart1RxBuff, Uart1RxPtr);
		Uart1RxPtr = 0;
	}
}
//************************************************************************************************************
static __TASK void TaskStart(void *para)
{
    uint8 timeCnt = 0;

	Initial();
    ciu98m25_init();
    
    OS_TASK_CREATE(TaskUart1, YOS_NULL, TaskUart1Stack, 0);
//========用户相关初始化==========================================
//	OS_TASK_CREATE(TaskA, YOS_NULL, TaskAStack, 1);	
//	OS_TASK_CREATE(TaskB, YOS_NULL, TaskBStack, 2);
//	OS_TASK_CREATE(TaskC, YOS_NULL, TaskCStack, 3);

	InitWDT();
	while(1)
	{
		OSTimeDly(OS_TICKS_PER_SEC/2);	
		FeedWDT();
        if(timeCnt++ & 1)
        {
			YOS_RTCTick();
        #if UART_PRINT_OS_RUN_TIME > 0
            OSShowTime();
        #endif
        #if OS_CPU_STAT_EN > 0
            PrintCPUUsage();//打印CPU使用率
        #endif
        #if OS_STK_CHK_EN > 0
            PrintStackUsage();
        #endif
        }
        LED1_TOG();
	}
}
//************************************************************************************************************
int main(void)
{
	OSInit();
	OS_TASK_CREATE(TaskStart, YOS_NULL, TaskStartStack, 4);
	OSStart();
	return(0);
}
//************************************************************************************************************

