/*********************************************************************************************************
**				                              HGOS for Cortex-M3
**
**                                  (c) Copyright 2012-2012, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
/*********************************************************************************************************
2013-09-13  09:41 ���ļ�����
*********************************************************************************************************/
//*******HGOS�в���Ķ���***********************************************************************************************************************
#define OS_TICKS_PER_MS         OS_TICKS_PER_SEC/1000	//ÿ�����tick��
#define OS_TICKS_MS(ms)         ((ms*OS_TICKS_PER_MS==0) ? 1 : ms*OS_TICKS_PER_MS)

#ifndef NULL
	#define NULL  				0
#endif

#define	YOS_NULL					((void*)0)
//******************************************************************************************************************************
typedef uint32          OS_TICK_CNTS_t;//ϵͳ�δ��ۼ����Ŀ���
//******************************************************************************************************************************