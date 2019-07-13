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
	void           **Queue;  //��Ϣ������ʼ��ַ
    OS_Q_SIZE_t    Size;	  //��Ϣ���пɴ洢����Ϣ����
	OS_Q_SIZE_t    In;//Pointer to where next message will be inserted in the Q//��ǰ���������Ƚ�ȥ��������Ϣ�������Ϣ������ʼ��ַ��ƫ����
	OS_Q_SIZE_t    Out;//Pointer to where next message will be extracted from the Q
    OS_Q_SIZE_t    Msgs;   //��Ϣ���е�ǰ����Ϣ��

	OS_WAIT_LIST_t WaitList;
} OS_Q_t;
//********************************************************************************************************
extern uint8 OSQCreate(OS_Q_t *pQ, void **queue, OS_Q_SIZE_t size);//������Ϣ����
#define OS_Q_CREATE(pq,queue) 	OSQCreate(pq, queue, ARRAY_SIZE(queue))//2013-06-09 by zpyws;	
extern uint8 OSQPost(OS_Q_t *pQ,void *msg);//pmailͨ���ĸ����з��ͣ�msgΪ��Ϣָ��
extern uint8 OSQPend(OS_Q_t *pQ,OS_TICK_t tou,void **ppmsg);//pmail���ĸ���������Ϣ��ppmsg��Ϣָ��Ҫ���浽��,timeoutΪ�ȴ���Ϣ�ĳ�ʱʱ��
#define OSQIntPost(pQ,msg)		OSQPost(pQ,msg)//pmailͨ���ĸ����з��ͣ�msgΪ��Ϣָ��
extern uint8 OSQPostFront(OS_Q_t *pQ,void *msg);//pmailͨ���ĸ����з��ͣ�msgΪ��Ϣָ��
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
