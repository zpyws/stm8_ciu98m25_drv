/*********************************************************************************************************
**				                              HGOS(YOS)
**
**                                  (c) Copyright 2012-2015, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
#ifndef OS_RING_H
#define OS_RING_H
//********************************************************************************************************
typedef struct
{
	uint8 *Queue;
	OS_RING8_SIZE_t Size;	//本消息队列容纳的最大消息数
	OS_RING8_SIZE_t Msgs;	//本消息队列当前的消息条数
	OS_RING8_SIZE_t In;		//数据入列偏移
	OS_RING8_SIZE_t Out;	//数据出列偏移

	OS_WAIT_LIST_t WaitList;
}OS_RING8_t;
//********************************************************************************************************
extern uint8 OSRing8Create(OS_RING8_t *pQ, uint8 *queue, OS_RING8_SIZE_t size);//建立消息队列
extern uint8 OSRing8Post(OS_RING8_t *pQ, uint8 dat);//pQ通过哪个队列发送，dat为要入列的数据
extern uint8 OSRing8IntPost(OS_RING8_t *pQ, uint8 dat);//pQ通过哪个队列发送，dat为要入列的数据
extern uint8 OSRing8Pend(OS_RING8_t *pQ, OS_TICK_t tout, uint8 *dat);//pmail从哪个队列收消息，ppmsg消息指针要保存到哪,timeout为等待消息的超时时间
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
