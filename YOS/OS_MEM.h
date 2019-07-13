/*********************************************************************************************************
**				                              HGOS(YOS)
**
**                                  (c) Copyright 2012-2015, Yang Wensen
**                                           All Rights Reserved
**
**                                                  V1.04
*********************************************************************************************************/
#ifndef OS_MEM_H
#define OS_MEM_H
//********************************************************************************************************
typedef struct // MEMORY CONTROL BLOCK
{
	void   *FreeList;//Pointer to list of free memory blocks
    OS_MEM_BLK_SIZE_t  BlkSize;//Size (in bytes) of each memory block
}OS_MEM_t;
//********************************************************************************************************
extern uint8 OSMemCreate (OS_MEM_t *pmem, void *addr, OS_MEM_BLKS_t nblks, OS_MEM_BLK_SIZE_t blksize);
extern uint8 OSMemGet(OS_MEM_t *pmem, void **blkAddr);//返回空闲块的起始地址
extern uint8 OSMemPut(OS_MEM_t  *pmem, void *pblk);
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
