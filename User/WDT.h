#ifndef WDT_H
#define WDT_H
//*************************************************************
#define FEED_WDT()     FeedWDT()//�忴�Ź�
//*************************************************************
extern void InitWDT(void);//timeout = 1.02S
extern void FeedWDT(void);
//*************************************************************
#endif
