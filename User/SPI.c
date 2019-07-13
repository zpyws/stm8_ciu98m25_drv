#include "common_zpyws.h"
//**********************function prototype**********************************************************************
#define USE_SOFT_SPI		0//ʹ��ģ��SPI��ʽ
#define SPI_BPS				SPI_BPS_PCLK_PS_128
//******�ڲ�˽�к�***********************************************************************************************************
//2013-02-26 by zpyws
#define SPI_BPS_PCLK_PS_2	0//SPIʱ��Ϊ����ʱ�ӵ�2��Ƶ
#define SPI_BPS_PCLK_PS_4	1//SPIʱ��Ϊ����ʱ�ӵ�4��Ƶ
#define SPI_BPS_PCLK_PS_8	2//SPIʱ��Ϊ����ʱ�ӵ�8��Ƶ
#define SPI_BPS_PCLK_PS_16	3//SPIʱ��Ϊ����ʱ�ӵ�16��Ƶ
#define SPI_BPS_PCLK_PS_32	4//SPIʱ��Ϊ����ʱ�ӵ�32��Ƶ
#define SPI_BPS_PCLK_PS_64	5//SPIʱ��Ϊ����ʱ�ӵ�64��Ƶ
#define SPI_BPS_PCLK_PS_128	6//SPIʱ��Ϊ����ʱ�ӵ�128��Ƶ
#define SPI_BPS_PCLK_PS_256	7//SPIʱ��Ϊ����ʱ�ӵ�256��Ƶ

#define BR0               3//BR[2:0]: Baud rate control
//*************SPI��д�ײ����****************************************************************************************************
static void SPI_IOInit(void)
{
	IO_OUT(PC, 5);
	IO_MODE_PP(PC, 5);	//push-pull
	IO_CLR(PC, 5);			

	IO_OUT(PC, 6);
	IO_MODE_PP(PC, 6);	//push-pull
	IO_SET(PC, 6);			

	IO_IN(PC, 7);
	IO_MODE_PU(PC, 7);//ʹ����λ����
}

#if USE_SOFT_SPI==0
extern void SPI_Init(void)
{
	SPI_IOInit();

	SBF(CLK->PCKENR1, CLK_PCKENR1_SPI);//ʹ������ʱ��
//================================================================================
	SPI->CR1 = CC(SPI_CR1_LSBFIRST)|CC(SPI_CR1_SPE)|(SPI_BPS<<BR0)|(SPI_CR1_MSTR)|CC(SPI_CR1_CPOL)|(SPI_CR1_CPHA);//MSB first,����SPI������Ϊʱ�Ӷ���Ƶ��������,����ʱ����Ϊ�ͣ���һ��ʱ����������������
	SPI->CR2 = CC(SPI_CR2_BDM)|CC(SPI_CR2_BDOE)|CC(SPI_CR2_CRCEN)|CC(SPI_CR2_CRCNEXT)|CC(SPI_CR2_RXONLY)|(SPI_CR2_SSM)|(SPI_CR2_SSI);//������,,����CRC,,��ֻ����ģʽ,�����ʽ����ӻ�������ģʽ
//	SPI_CRCPR = 0x07;//SPI CRC polynomial register The CRC polynomial (0x07) is the reset value of this register. You can configure an other polynomial as required for your application
//	SPI_ICR = CC(TXIE)|CC(RXIE)|CC(ERRIE)|CC(WKIE);//���Ϳ��жϣ����ղ����жϣ������жϣ������ж�
	SBF(SPI->CR1,SPI_CR1_SPE);//ʹ��SPI
}
//********************************************************************************************
extern uint8 SPI_TransferByte(uint8 byte)
{
	while( GBF(SPI->SR,SPI_SR_TXE)==0 );//�ȴ�SPI���ͻ�����Ϊ��
	SPI->DR = byte;
	while( GBF(SPI->SR,SPI_SR_RXNE)==0 );//�ȴ�SPI���ջ�������Ϊ��.����һ���оͿ�������
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
	IO_MODE_PU(SPI_MISO_PORT, SPI_MISO_PIN);//ʹ����λ����
}
//********************************************************************************************
extern uint8 SPI_TransferByte(uint8 dat)//ʱ������658KHz
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

