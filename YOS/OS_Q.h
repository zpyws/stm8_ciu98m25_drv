/*********************************************************************************************************
**				                              HGOS(YOS)
**
**                                  (c) Copyright 2012-2015, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
#ifndef OS_Q_H
#define OS_Q_H
//********************************************************************************************************
typedef struct
{
	void           **Queue;  //消息队列起始地址
    OS_Q_SIZE_t    Size;	  //消息队列可存储的消息总数
	OS_Q_SIZE_t    In;//Pointer to where next message will be inserted in the Q//当前队列中最先进去的那条消息相对于消息缓冲起始地址的偏移量
	OS_Q_SIZE_t    Out;//Pointer to where next message will be extracted from the Q
    OS_Q_SIZE_t    Msgs;   //消息队列当前的消息数

	OS_WAIT_LIST_t WaitList;
} OS_Q_t;
//********************************************************************************************************
extern uint8 OSQCreate(OS_Q_t *pQ, void **queue, OS_Q_SIZE_t size);//建立消息队列
#define OS_Q_CREATE(pq,queue) 	OSQCreate(pq, queue, ARRAY_SIZE(queue))//2013-06-09 by zpyws;	
extern uint8 OSQPost(OS_Q_t *pQ,void *msg);//pmail通过哪个队列发送，msg为消息指针
extern uint8 OSQPend(OS_Q_t *pQ,OS_TICK_t tou,void **ppmsg);//pmail从哪个队列收消息，ppmsg消息指针要保存到哪,timeout为等待消息的超时时间
#define OSQIntPost(pQ,msg)		OSQPost(pQ,msg)//pmail通过哪个队列发送，msg为消息指针
extern uint8 OSQPostFront(OS_Q_t *pQ,void *msg);//pmail通过哪个队列发送，msg为消息指针
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
