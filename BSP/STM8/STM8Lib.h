#ifndef STM8LIB_H
#define STM8LIB_H
//******************************************************************************
#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208)||\
	defined(STM8S105)//2014-03-28  BY ZPYWS
	#define HSI_DIV       3//位域在寄存器内偏移
	#define CPU_DIV      0//位域在寄存器内偏移
#elif defined(STM8L101) || defined(STM8L152)//2013-08-26  BY ZPYWS
	#define HSI_DIV       0//位域在寄存器内偏移
	#define CPU_DIV      0//对于STM8L，不存在CPU_DIV设置位
#endif
//******************************************************************************
#define HSI_DIV_1     (0<<HSI_DIV)//内部16MHz RC振荡器一分频
#define HSI_DIV_2     (1<<HSI_DIV)//内部16MHz RC振荡器一分频
#define HSI_DIV_4     (2<<HSI_DIV)//内部16MHz RC振荡器一分频
#define HSI_DIV_8     (3<<HSI_DIV)//内部16MHz RC振荡器一分频

#define CPU_DIV_1    (0<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_2    (1<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_4    (2<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_8    (3<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_16   (4<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_32   (5<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_64   (6<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
#define CPU_DIV_128  (7<<CPU_DIV)//CPU时钟上频率为对PCLK时钟一分频
//******************************************************************************
extern void SetHsiDiv(uint8 pclk_div, uint8 cpu_div);
extern void InitPeripheralClock(void);

extern void delay_ms(uint16 t);
extern void delay_us(uint8 t);
extern void delay(uint16 t);
//******************************************************************************
#endif