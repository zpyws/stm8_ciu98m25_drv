#ifndef TIME_H
#define TIME_H
//***************************************************************************
typedef struct
{
	uint8 SEC;
	uint8 MIN;
	uint8 HOUR;
	uint16 DAY;
}YOS_RTC_t;

extern YOS_RTC_t YOS_RTC;
//***************************************************************************
extern void YOS_RTCTick(void);
extern void OSShowTime(void);
//***************************************************************************
#endif
