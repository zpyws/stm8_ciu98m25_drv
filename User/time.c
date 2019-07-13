#include "common_zpyws.h"
//******************************************************************************************************************************
YOS_RTC_t YOS_RTC = {0,0,0,0};
//******************************************************************************************************************************
//OS�ϵ�ʱ�����
extern void YOS_RTCTick(void)
{
//==ʱ����ʱ=====================================================================
	if(++YOS_RTC.SEC<60)return;
	YOS_RTC.SEC = 0;
	if(++YOS_RTC.MIN<60)return;
	YOS_RTC.MIN = 0;
	if(++YOS_RTC.HOUR<24)return;
	YOS_RTC.HOUR = 0;
	++YOS_RTC.DAY;
}
//******************************************************************************************************************************
//��ӡϵͳ����ʱ��
//2015-07-30  by zpyws
extern void OSShowTime(void)
{
	uint8 len,str[5];

	OSSemPend( &SemUart1Tx, 0 );

	UART1_PRINT_STRING_RAW("YOS UPTIME:");

	len = SprintUint16AsDecimal(YOS_RTC.DAY, str);
	Uart1PutRaw(str, len);
	UART1_PRINT_STRING_RAW("��");

	Uart1PutUint8AsDecimal(YOS_RTC.HOUR);
	UART1_PRINT_STRING_RAW("ʱ");

	Uart1PutUint8AsDecimal(YOS_RTC.MIN);
	UART1_PRINT_STRING_RAW("��");

	Uart1PutUint8AsDecimal(YOS_RTC.SEC);
	UART1_PRINT_STRING_RAW("��\r\n");

	OSSemPost(&SemUart1Tx);//�ͷ���Դ
}
//******************************************************************************************************************************
