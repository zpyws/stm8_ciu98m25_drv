#include "common_zpyws.h"
//******************************************************************************************************************************
//修改日志　by zpyws
//2013-08-27  09:37 STM8体系内移植不需要修改本文件，目前支持STM8S103,STM8L101,STM8L152
//2013-08-27  15:50 STM8体系内移植不需要修改本文件，目前支持STM8S103,STM8L101,STM8L152,STM8S207,STM8S208
//2014-03-29  12:11 STM8体系内移植不需要修改本文件，目前支持STM8S103,STM8L101,STM8L152,STM8S207,STM8S208,STM8S105
//******************************************************************************************************************************
#if defined(STM8S103) || defined(STM8L101) || defined(STM8L152) ||\
	defined(STM8S207) || defined(STM8S208) || defined(STM8S105)//2013-08-27  BY ZPYWS
//******************************************************************************************************************************
#define IWDG_KEY_EBABLE       0xcc
#define IWDG_KEY_REFRESH      0xaa
#define IWDG_KEY_ACCESS       0x55

#define PR0               0//PR[2:0]: Prescaler divider

extern void InitWDT(void)
{
	IWDG->KR = IWDG_KEY_EBABLE;//必须先启动看门狗后才能配置否则会有奇怪的现象
	IWDG->KR = IWDG_KEY_ACCESS;//解除IWDG_PR and IWDG_RLR的写保护
	IWDG->PR = 6 << PR0;//256分频，在38K RC时看门狗超时时间1724.63ms时长
	IWDG->RLR = 0xFF;//重载寄存器
	IWDG->KR = IWDG_KEY_REFRESH;//写入后恢复到写保护状态
}
//******************************************************************************************************************************
extern void FeedWDT(void)
{
	IWDG->KR = IWDG_KEY_REFRESH;//清看门狗
}
//******************************************************************************************************************************
#endif