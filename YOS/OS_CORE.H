/*********************************************************************************************************
**				                              HGOS(YOS)
**
**                                  (c) Copyright 2012-2015, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
#ifndef OS_CORE_H
#define OS_CORE_H
//*********************************************************
typedef enum// OS_ERR
{
	OS_NO_ERR,
	OS_ERR,
	OS_TIMEOUT,
	OS_SEM_OVF,
	OS_ERR_SEM_NULL,
	OS_ERR_PMAIL_NULL,
	OS_ERR_PQ_NULL,
	OS_ERR_STM_NULL,
	OS_ERR_POST_NULL_PTR,
	OS_ERR_INVALID_PTR,

	OS_MBOX_FULL,
	OS_Q_FULL,
	OS_STM_FULL,
	OS_STM_EMPTY,//流队列为空
	
	OS_ERR_PMEM_NULL,
	OS_MEM_INVALID_SIZE,
	OS_MEM_INVALID_BLKS,
	OS_MEM_NO_FREE_BLKS,
	
	OS_PRIO_INVALID,
	OS_TASK_NOT_EXIST,
}OS_ERR_TYPE;//操作系统错误类型
//************************************************************************************************************
typedef struct		//OS的等待任务表
{
    uint8          OSEventGrp;
    uint8		   OSEventMap[2];
}OS_WAIT_LIST_t;
//=================================================================================
#if OS_STK_CHK_EN > 0
typedef struct
{
    OS_STK_SIZE_t  OSFree;                    /* Number of free bytes on the stack */
    OS_STK_SIZE_t  OSUsed;                    /* Number of bytes used on the stack */
}OS_STK_DATA_t;
#endif
//************************************************************************************************************
#if OS_CPU_STAT_EN > 0
	extern volatile int8 OSCPUUsage;               /* Percentage of CPU used                          */
	extern volatile uint8 OSCPUUsageExt;//CPU使用率百分比的的小数部分(两位)
#endif
//******************************************************************************************************************************
extern void OSInit(void);
extern void OSStart(void);
extern void OSTimeDly (OS_TICK_t ticks);
extern void OSTimeTick(void);
extern void OSIntEnter(void);
extern void OSIntExit(void);//退出中断时调用，查找最高优先级任务，必要时执行任务切换2012-08-30 by zpyws
extern void OSTaskCreate( void (*Task)(void *), void *para, OS_STK_t *pStack, uint8 prio );//创建任务

#if OS_STK_CHK_EN > 0
	extern void OSTaskCreateExt( void (*Task)(void *), void *para, OS_STK_t *pStack, uint8 prio, OS_STK_SIZE_t stkSize );
	extern uint8 OSTaskStkChk (uint8 prio, OS_STK_DATA_t *pdat);
#endif

extern OS_TICK_CNTS_t  OSTimeGet(void);
extern void OSTimeSet(OS_TICK_CNTS_t ticks);

extern void OSSchedLock(void);
extern void OSSchedUnlock (void);

#if OS_CPU_STAT_EN > 0
	extern void OSCPUStatInit(void);
#endif
//***************************************************************************************************************************************
//任务建立函数统一API宏定义(向上向下堆栈增长，使用或不使用堆栈检测功能均有统一的API)
//by zpyws 2012-11-20
#if OS_STK_GROWTH > 0//向下增长型堆栈
	#if OS_STK_CHK_EN > 0//使能堆栈检测功能时
		#define OS_TASK_CREATE(task,para,stack,prio)     OSTaskCreateExt( (void(*)(void *))task, para, &stack[ARRAY_SIZE(stack)-1], prio, ARRAY_SIZE(stack) )
	#else //不使用堆栈检测功能
		#define OS_TASK_CREATE(task,para,stack,prio) 	OSTaskCreate((void(*)(void *))task, para, &stack[ARRAY_SIZE(stack)-1], prio)//2012-09-6 by zpyws;	
	#endif
#else //向上增长型堆栈
	#if OS_STK_CHK_EN > 0//使能堆栈检测功能时
		#define OS_TASK_CREATE(task,stack,prio)     OSTaskCreateExt( (void(*)(void *))task, para, &stack[0], prio, ARRAY_SIZE(stack) )
	#else //不使用堆栈检测功能
		#define OS_TASK_CREATE(task,para,stack,prio) 	OSTaskCreate((void(*)(void*))task, para, &stack[0], prio)//2012-09-6 by zpyws;	
	#endif
#endif
//***************************************************************************************************************************************
#endif
