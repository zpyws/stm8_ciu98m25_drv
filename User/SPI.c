#include "common_zpyws.h"
//**********************function prototype**********************************************************************
#define USE_SOFT_SPI		0//使用模拟SPI方式
#define SPI_BPS				SPI_BPS_PCLK_PS_128
//******内部私有宏***********************************************************************************************************
//2013-02-26 by zpyws
#define SPI_BPS_PCLK_PS_2	0//SPI时钟为外设时钟的2分频
#define SPI_BPS_PCLK_PS_4	1//SPI时钟为外设时钟的4分频
#define SPI_BPS_PCLK_PS_8	2//SPI时钟为外设时钟的8分频
#define SPI_BPS_PCLK_PS_16	3//SPI时钟为外设时钟的16分频
#define SPI_BPS_PCLK_PS_32	4//SPI时钟为外设时钟的32分频
#define SPI_BPS_PCLK_PS_64	5//SPI时钟为外设时钟的64分频
#define SPI_BPS_PCLK_PS_128	6//SPI时钟为外设时钟的128分频
#define SPI_BPS_PCLK_PS_256	7//SPI时钟为外设时钟的256分频

#define BR0               3//BR[2:0]: Baud rate control
//*************SPI读写底层程序****************************************************************************************************
static void SPI_IOInit(void)
{
	IO_OUT(PC, 5);
	IO_MODE_PP(PC, 5);	//push-pull
	IO_CLR(PC, 5);			

	IO_OUT(PC, 6);
	IO_MODE_PP(PC, 6);	//push-pull
	IO_SET(PC, 6);			

	IO_IN(PC, 7);
	IO_MODE_PU(PC, 7);//使能上位电阻
}

#if USE_SOFT_SPI==0
extern void SPI_Init(void)
{
	SPI_IOInit();

	SBF(CLK->PCKENR1, CLK_PCKENR1_SPI);//使能外设时钟
//================================================================================
	SPI->CR1 = CC(SPI_CR1_LSBFIRST)|CC(SPI_CR1_SPE)|(SPI_BPS<<BR0)|(SPI_CR1_MSTR)|CC(SPI_CR1_CPOL)|(SPI_CR1_CPHA);//MSB first,禁能SPI，速率为时钟二分频，当主机,空闲时钟线为低，第一个时钟跳变沿锁存数据
	SPI->CR2 = CC(SPI_CR2_BDM)|CC(SPI_CR2_BDOE)|CC(SPI_CR2_CRCEN)|CC(SPI_CR2_CRCNEXT)|CC(SPI_CR2_RXONLY)|(SPI_CR2_SSM)|(SPI_CR2_SSI);//两线制,,禁能CRC,,非只接收模式,软件方式管理从机，主机模式
//	SPI_CRCPR = 0x07;//SPI CRC polynomial register The CRC polynomial (0x07) is the reset value of this register. You can configure an other polynomial as required for your application
//	SPI_ICR = CC(TXIE)|CC(RXIE)|CC(ERRIE)|CC(WKIE);//发送空中断，接收不空中断，出错中断，唤醒中断
	SBF(SPI->CR1,SPI_CR1_SPE);//使能SPI
}
//********************************************************************************************
extern uint8 SPI_TransferByte(uint8 byte)
{
	while( GBF(SPI->SR,SPI_SR_TXE)==0 );//等待SPI发送缓冲区为空
	SPI->DR = byte;
	while( GBF(SPI->SR,SPI_SR_RXNE)==0 );//等待SPI接收缓冲区不为空.程序一运行就卡在这里
	return(SPI->DR);
}
#endif
//********************************************************************************************
#if USE_SOFT_SPI > 0
//=================================================
#define SPI_SCK_PORT		PC
#define SPI_SCK_PIN			5

#define SPI_MOSI_PORT		PC
#define SPI_MOSI_PIN		6

#define SPI_MISO_PORT		PD	//PC
#define SPI_MISO_PIN		2	//7
//=================================================
extern void SPI_Init(void)
{
	IO_OUT(SPI_SCK_PORT, SPI_SCK_PIN);
	IO_MODE_PP(SPI_SCK_PORT, SPI_SCK_PIN);	//push-pull
	IO_CLR(SPI_SCK_PORT, SPI_SCK_PIN);			

	IO_OUT(SPI_MOSI_PORT, SPI_MOSI_PIN);
	IO_MODE_PP(SPI_MOSI_PORT, SPI_MOSI_PIN);	//push-pull
	IO_SET(SPI_MOSI_PORT, SPI_MOSI_PIN);			

	IO_IN(SPI_MISO_PORT, SPI_MISO_PIN);
	IO_MODE_PU(SPI_MISO_PORT, SPI_MISO_PIN);//使能上位电阻
}
//********************************************************************************************
extern uint8 SPI_TransferByte(uint8 dat)//时钟速率658KHz
{
	uint8 i;
   	for(i=8; i>0; i--)   // output 8-bit
   	{
		if(dat&0x80)IO_SET(SPI_MOSI_PORT, SPI_MOSI_PIN);
		else IO_CLR(SPI_MOSI_PORT, SPI_MOSI_PIN);
		dat <<= 1;
		IO_SET(SPI_SCK_PORT, SPI_SCK_PIN);
		if( IO_RD(SPI_MISO_PORT, SPI_MISO_PIN) )dat++;
		IO_CLR(SPI_SCK_PORT, SPI_SCK_PIN);
   	}
    return(dat);           		  // return read byte
}
#endif
//********************************************************************************************

