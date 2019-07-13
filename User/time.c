#include "common_zpyws.h"
//******************************************************************************************************************************
YOS_RTC_t YOS_RTC = {0,0,0,0};
//******************************************************************************************************************************
//OS上电时间计数
extern void YOS_RTCTick(void)
{
//==时钟走时=====================================================================
	if(++YOS_RTC.SEC<60)return;
	YOS_RTC.SEC = 0;
	if(++YOS_RTC.MIN<60)return;
	YOS_RTC.MIN = 0;
	if(++YOS_RTC.HOUR<24)return;
	YOS_RTC.HOUR = 0;
	++YOS_RTC.DAY;
}
//******************************************************************************************************************************
//打印系统运行时间
//2015-07-30  by zpyws
extern void OSShowTime(void)
{
	uint8 len,str[5];

	OSSemPend( &SemUart1Tx, 0 );

	UART1_PRINT_STRING_RAW("YOS UPTIME:");

	len = SprintUint16AsDecimal(YOS_RTC.DAY, str);
	Uart1PutRaw(str, len);
	UART1_PRINT_STRING_RAW("天");

	Uart1PutUint8AsDecimal(YOS_RTC.HOUR);
	UART1_PRINT_STRING_RAW("时");

	Uart1PutUint8AsDecimal(YOS_RTC.MIN);
	UART1_PRINT_STRING_RAW("分");

	Uart1PutUint8AsDecimal(YOS_RTC.SEC);
	UART1_PRINT_STRING_RAW("秒\r\n");

	OSSemPost(&SemUart1Tx);//释放资源
}
//******************************************************************************************************************************
