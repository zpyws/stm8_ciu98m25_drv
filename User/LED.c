#include "common_zpyws.h"
//******************************************************************************************************************************
extern void InitLED(void)
{
	IO_OUT(LED1_PORT, LED1_PIN);//����Ϊ�����
	IO_MODE_PP(LED1_PORT, LED1_PIN);//����Ϊ�������
//	CBI(LED1_CR2,LED1_IDX);//����Ϊ2MHz����IO
	LED1_OFF();
//================================================
	IO_OUT(LED2_PORT, LED2_PIN);//����Ϊ�����
	IO_MODE_PP(LED2_PORT, LED2_PIN);//����Ϊ�������
//	CBI(LED1_CR2,LED1_IDX);//����Ϊ2MHz����IO
	LED2_OFF();
//================================================
//	IO_OUT(LED2R_DDR,LED2R_IDX);//����Ϊ�����
//	SBI(LED2R_CR1,LED2R_IDX);//����Ϊ�������
//	CBI(LED2R_CR2,LED2R_IDX);//����Ϊ2MHz����IO
//	LED2R_OFF();
//================================================
//	IO_OUT(LED3_PORT, LED3_PIN);//����Ϊ�����
//	IO_MODE_PP(LED3_PORT, LED3_PIN);//����Ϊ�������
//
//	IO_OUT(LED4_PORT, LED4_PIN);//����Ϊ�����
//	IO_MODE_PP(LED4_PORT, LED4_PIN);//����Ϊ�������
//
//	IO_OUT(LED5_PORT, LED5_PIN);//����Ϊ�����
//	IO_MODE_PP(LED5_PORT, LED5_PIN);//����Ϊ�������
//
//	IO_OUT(LED6_PORT, LED6_PIN);//����Ϊ�����
//	IO_MODE_PP(LED6_PORT, LED6_PIN);//����Ϊ�������
}
//******************************************************************************************************************************
