#include "common_zpyws.h"
//******************************************************************************************************************************
extern void InitLED(void)
{
	IO_OUT(LED1_PORT, LED1_PIN);//设置为输出口
	IO_MODE_PP(LED1_PORT, LED1_PIN);//设置为推挽输出
//	CBI(LED1_CR2,LED1_IDX);//设置为2MHz低速IO
	LED1_OFF();
//================================================
	IO_OUT(LED2_PORT, LED2_PIN);//设置为输出口
	IO_MODE_PP(LED2_PORT, LED2_PIN);//设置为推挽输出
//	CBI(LED1_CR2,LED1_IDX);//设置为2MHz低速IO
	LED2_OFF();
//================================================
//	IO_OUT(LED2R_DDR,LED2R_IDX);//设置为输出口
//	SBI(LED2R_CR1,LED2R_IDX);//设置为推挽输出
//	CBI(LED2R_CR2,LED2R_IDX);//设置为2MHz低速IO
//	LED2R_OFF();
//================================================
//	IO_OUT(LED3_PORT, LED3_PIN);//设置为输出口
//	IO_MODE_PP(LED3_PORT, LED3_PIN);//设置为推挽输出
//
//	IO_OUT(LED4_PORT, LED4_PIN);//设置为输出口
//	IO_MODE_PP(LED4_PORT, LED4_PIN);//设置为推挽输出
//
//	IO_OUT(LED5_PORT, LED5_PIN);//设置为输出口
//	IO_MODE_PP(LED5_PORT, LED5_PIN);//设置为推挽输出
//
//	IO_OUT(LED6_PORT, LED6_PIN);//设置为输出口
//	IO_MODE_PP(LED6_PORT, LED6_PIN);//设置为推挽输出
}
//******************************************************************************************************************************
