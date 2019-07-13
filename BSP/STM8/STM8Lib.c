#include "common_zpyws.h"
//******************************************************************************
//修改日志	by zpyws
//2013-08-27  09:12 本文件STM8体系内移植无需修改(需要在Preprocessor设置CPU型号)，目前支持STM8S103,STM8L101,STM8L152
//2013-08-27  15:48 本文件STM8体系内移植无需修改(需要在Preprocessor设置CPU型号)，
//					目前支持STM8S103,STM8L101,STM8L152,STM8S207,STM8S208,STM8S105
//******************************************************************************
//pclk_div对16MHz HSI时钟进行分频得到。
//cpu_div对pclk时钟分频得到
extern void SetHsiDiv(uint8 pclk_div, uint8 cpu_div)
{
	//STM8S103,STM8L101,STM8L152,STM8S105共用
	CLK->CKDIVR &= ~(3<<HSI_DIV);//清零位域
	CLK->CKDIVR |= pclk_div;

#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208) ||\
	defined(STM8S105)//2014-03-28  BY ZPYWS
	CLK->CKDIVR &= ~(7<<CPU_DIV);//清零位域
	CLK->CKDIVR |= cpu_div;
#endif
}
//******************************************************************************
extern void delay_ms(uint16 t)
{
	uint16 i;

	while(t--)
	{
	#if F_CPU==16000000UL
		for(i=0;i<2660;i++)//在16M时延时1ms
		{
			NOP();
		}
	#endif
	}
}
//******************************************************************************
extern void delay_us(uint8 t)
{
	while(t--)
	{
		NOP();NOP();
		NOP();NOP();
		NOP();NOP();
		NOP();NOP();
	}
}
//******************************************************************************
extern void delay(uint16 t)
{
	while(t--)
	{
	}
}
//******************************************************************************
//关闭所有外设时钟，系统复位后，STM8S默认所有外设时钟都是打开的
//2013-02-01  by zpyws
extern void InitPeripheralClock(void)
{
#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208) ||\
	defined(STM8S105)//2013-08-26  BY ZPYWS
	CLK->PCKENR1 = 0x00 | (CLK_PCKENR1_TIM2);//关闭所有外设时钟，系统复位后，STM8S默认所有外设时钟都是打开的
	CLK->PCKENR2 = 0x00;//关闭所有外设时钟，系统复位后，STM8S默认所有外设时钟都是打开的

#elif defined(STM8L101)//2013-08-26  BY ZPYWS
	CLK->PCKENR = 0x00 | (CLK_PCKENR_TIM2);//关闭除了Timer2以外的所有外设的时钟供应

#elif defined(STM8L152)//2013-08-26  BY ZPYWS
	CLK->PCKENR1 = 0x00 | (CLK_PCKENR1_TIM2);//关闭除了Timer2以外的所有外设的时钟供应
	CLK->PCKENR2 = 0x00;//关闭所有外设的时钟供应
//	CLK_PCKENR3 = 0x00;//关闭所有外设的时钟供应
#endif
}
//******************************************************************************
