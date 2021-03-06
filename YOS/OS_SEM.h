/*********************************************************************************************************
**				                              HGOS(YOS)
**
**                                  (c) Copyright 2012-2015, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
#ifndef OS_SEM_H
#define OS_SEM_H
//********************************************************************************************************
typedef struct
{
	OS_SEM_CNT_t   OSEventCnt;//信号量计数器
	OS_WAIT_LIST_t WaitList;
}OS_SEM_t;
//********************************************************************************************************
extern uint8 OSSemCreate(OS_SEM_t *p_sem,uint8 cnt);//p_sem要初始化的信号量，cnt为信号量的初始计数值
extern uint8 OSSemPend(OS_SEM_t *p_sem,OS_TICK_t time_out);//p_sem等待信号量，index为信号量的索引值,timeout为等待信号量的超时时间
extern uint8 OSSemPost(OS_SEM_t * p_sem);//p_sem发送信号量
#define OSSemIntPost(s)		OSSemPost(s)//p_sem发送信号量
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
