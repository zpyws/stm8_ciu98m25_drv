#include "common_zpyws.h"
//******************************************************************************
//�޸���־	by zpyws
//2013-08-27  09:12 ���ļ�STM8��ϵ����ֲ�����޸�(��Ҫ��Preprocessor����CPU�ͺ�)��Ŀǰ֧��STM8S103,STM8L101,STM8L152
//2013-08-27  15:48 ���ļ�STM8��ϵ����ֲ�����޸�(��Ҫ��Preprocessor����CPU�ͺ�)��
//					Ŀǰ֧��STM8S103,STM8L101,STM8L152,STM8S207,STM8S208,STM8S105
//******************************************************************************
//pclk_div��16MHz HSIʱ�ӽ��з�Ƶ�õ���
//cpu_div��pclkʱ�ӷ�Ƶ�õ�
extern void SetHsiDiv(uint8 pclk_div, uint8 cpu_div)
{
	//STM8S103,STM8L101,STM8L152,STM8S105����
	CLK->CKDIVR &= ~(3<<HSI_DIV);//����λ��
	CLK->CKDIVR |= pclk_div;

#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208) ||\
	defined(STM8S105)//2014-03-28  BY ZPYWS
	CLK->CKDIVR &= ~(7<<CPU_DIV);//����λ��
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
		for(i=0;i<2660;i++)//��16Mʱ��ʱ1ms
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
//�ر���������ʱ�ӣ�ϵͳ��λ��STM8SĬ����������ʱ�Ӷ��Ǵ򿪵�
//2013-02-01  by zpyws
extern void InitPeripheralClock(void)
{
#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208) ||\
	defined(STM8S105)//2013-08-26  BY ZPYWS
	CLK->PCKENR1 = 0x00 | (CLK_PCKENR1_TIM2);//�ر���������ʱ�ӣ�ϵͳ��λ��STM8SĬ����������ʱ�Ӷ��Ǵ򿪵�
	CLK->PCKENR2 = 0x00;//�ر���������ʱ�ӣ�ϵͳ��λ��STM8SĬ����������ʱ�Ӷ��Ǵ򿪵�

#elif defined(STM8L101)//2013-08-26  BY ZPYWS
	CLK->PCKENR = 0x00 | (CLK_PCKENR_TIM2);//�رճ���Timer2��������������ʱ�ӹ�Ӧ

#elif defined(STM8L152)//2013-08-26  BY ZPYWS
	CLK->PCKENR1 = 0x00 | (CLK_PCKENR1_TIM2);//�رճ���Timer2��������������ʱ�ӹ�Ӧ
	CLK->PCKENR2 = 0x00;//�ر����������ʱ�ӹ�Ӧ
//	CLK_PCKENR3 = 0x00;//�ر����������ʱ�ӹ�Ӧ
#endif
}
//******************************************************************************
