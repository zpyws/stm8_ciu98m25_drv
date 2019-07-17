//create by yangwensen@20190714

#include "common_zpyws.h"
#include "SPI.h"
//***********************************************************************************************************
#define EN_SPU_DEBUG				0
#define EN_SPU_TEST					0
//***********************************************************************************************************
#define CIU98M25_SPI_INIT()         SPI_Init()
#define CIU98M25_SPI_TRANSFER(a)    SPI_TransferByte(a)
#define CIU98M25_SPI_SEND(a,b)    	spi_burst_send(a,b)
#define CIU98M25_SPI_RECV(a,b)    	spi_burst_recv(a,b)

#define CIU98M25_CS_PORT			PA
#define CIU98M25_CS_PIN				3

#define CIU98M25_BUSY_PORT          PD
#define CIU98M25_BUSY_PIN           4

#define CIU98M25_SLEEP_PORT         PD
#define CIU98M25_SLEEP_PIN          3

#define CIU98M25_CS_ASSERT()		IO_CLR(CIU98M25_CS_PORT,CIU98M25_CS_PIN)
#define CIU98M25_CS_DEASSERT()		IO_SET(CIU98M25_CS_PORT,CIU98M25_CS_PIN)
#define IS_CIU98M25_BUSY()          (IO_RD(CIU98M25_BUSY_PORT, CIU98M25_BUSY_PIN))

#define CIU98M25_WRITE_TIMEOUT		1000
//***********************************************************************************************************
static OS_SEM_t sem_ciu98m25_ready;	//ciu98m25 has received mcu's data or ciu98m25 has data to send.
//***********************************************************************************************************
#if EN_SPU_DEBUG
	static void print_error_code(uint8 *str, uint8 strlen, sint8 err);
	#define PRINT_ERROR_CODE(str,err)		print_error_code(str,sizeof(str)-1,err)
	#define CIU98M25_PRINT_STRING(a)		UART1_PRINT_STRING(a)
#else
	#define PRINT_ERROR_CODE(str,err)	
	#define CIU98M25_PRINT_STRING(a)			
#endif
//***********************************************************************************************************
static void ciu98m25_io_init(void)
{
  	OS_CPU_t cpusr;
	
	IO_OUT(CIU98M25_CS_PORT, CIU98M25_CS_PIN);
	IO_MODE_PP(CIU98M25_CS_PORT, CIU98M25_CS_PIN);
  	CIU98M25_CS_DEASSERT();
	
    IO_IN(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
    IO_MODE_PU(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
//===============================================================================================    
    IO_IN(CIU98M25_BUSY_PORT, CIU98M25_BUSY_PIN);
    IO_MODE_PU(CIU98M25_BUSY_PORT, CIU98M25_BUSY_PIN);
    
    OS_ENTER_CRITICAL();//These bits can only be written when I1 and I0 in the CCR register are both set to 1 (level 3).
	EXTI->CR1 = ( EXTI->CR1 &(~EXTI_CR1_PDIS) ) | (2<<6);//下降沿中断these bits can only be written when I1 and I0 in the CCR register are both set to 1 (level 3).
    OS_EXIT_CRITICAL();
    
    IO_INT_EN(CIU98M25_BUSY_PORT, CIU98M25_BUSY_PIN);//使能外部中断功能
//===============================================================================================    
	OSSemCreate(&sem_ciu98m25_ready, 0);
}
//******************************************************************************************************************************
ISR(EXTID_vector)
{
	OSIntEnter();
//======================================================================================================================
    if( !IS_CIU98M25_BUSY() )
	{
	    OSSemIntPost(&sem_ciu98m25_ready);
	}
//======================================================================================================================
	OSIntExit();
}
//************************************************************************************************************
extern sint8 ciu98m25_init(void)
{
    CIU98M25_SPI_INIT();
    ciu98m25_io_init();
    
    return 0;
}
//************************************************************************************************************
//by yangwensen@20190716
static uint8 calc_check_code(uint8 *buff, uint16 len)
{
  	uint8 check_code = 0;
	
  	while(len--)
	{
	  	check_code ^= *buff++;
	}
	return ~check_code;
}
//************************************************************************************************************
//by yangwensen@20190717
static void spi_burst_send(uint8 *buff, uint8 len)
{
 	while(len--)
	{
	  	CIU98M25_SPI_TRANSFER(*buff++);
	}
}
//************************************************************************************************************
//by yangwensen@20190717
static void spi_burst_recv(uint8 *buff, uint8 len)
{
 	while(len--)
	{
	  	*buff++ = CIU98M25_SPI_TRANSFER(0xff);
	}
}
//************************************************************************************************************
static sint8 ciu98m25_write(uint8 *buff, uint16 len)
{
	uint8 check_code;
	
	//send sync
	CIU98M25_CS_ASSERT();
	CIU98M25_SPI_TRANSFER(0xaa);
	CIU98M25_SPI_TRANSFER(0x55);
	CIU98M25_CS_DEASSERT();

	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -2;
	}
//==============================================================================
	//send length
	CIU98M25_CS_ASSERT();
	CIU98M25_SPI_TRANSFER(len>>8);
	CIU98M25_SPI_TRANSFER(len&0x00ff);

	check_code = calc_check_code(buff, len);
	
	if(len<=13)		//first pack = last pack
	{
		goto SEND_LAST_PACK;
	}
	
	CIU98M25_SPI_SEND(buff, 14);
	CIU98M25_CS_DEASSERT();
	buff += 14;
	len -= 14;
	
	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -3;
	}
//==============================================================================
	//middle full packet(16 bytes)
	while(len>=16)
	{
		CIU98M25_CS_ASSERT();
		CIU98M25_SPI_SEND(buff, 16);
		CIU98M25_CS_DEASSERT();
		buff += 16;
		len -= 16;
	  	
		OSSemCreate(&sem_ciu98m25_ready, 0);
		if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
		{
			return -4;
		}
	}
//==============================================================================	
	//send last pack data(less than 16 bytes)
SEND_LAST_PACK:
	CIU98M25_CS_ASSERT();
	CIU98M25_SPI_SEND(buff, len);
	CIU98M25_SPI_TRANSFER(check_code);
	CIU98M25_CS_DEASSERT();
  
	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -5;
	}
//==============================================================================
	return 0;
}
//************************************************************************************************************
//by yangwensen@20190715
static sint16 ciu98m25_read(uint8 *rx_buff, uint16 buff_len)
{
  	uint8 sync[2];
	uint16 expect_len;
	uint8 check_code;
	uint8 *buff;
	
	if(!rx_buff)return -1;
	buff = rx_buff;
	
	//receive sync
	CIU98M25_CS_ASSERT();
	sync[0] = CIU98M25_SPI_TRANSFER(0xff);
	sync[1] = CIU98M25_SPI_TRANSFER(0xff);
	CIU98M25_CS_DEASSERT();
	
	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -2;
	}
	
	if(sync[0]!=0xaa)return -3;
	if(sync[1]!=0x55)return -4;
//==============================================================================
	//receive length
	CIU98M25_CS_ASSERT();
	sync[0] = CIU98M25_SPI_TRANSFER(0xff);
	sync[1] = CIU98M25_SPI_TRANSFER(0xff);

	expect_len = (((uint16)sync[0])<<8) | sync[1];
	if(expect_len > buff_len)return -5;
//==============================================================================
	if(expect_len<=13)		//first pack = last pack
	{
		goto RECV_LAST_PACK;
	}
	
	CIU98M25_SPI_RECV(buff, 14);
	CIU98M25_CS_DEASSERT();
	buff += 14;
	expect_len -= 14;
	
	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -6;
	}
//==============================================================================
	//middle full packet(16 bytes)
	while(expect_len>=16)
	{
		CIU98M25_CS_ASSERT();
		CIU98M25_SPI_RECV(buff, 16);
		CIU98M25_CS_DEASSERT();
		buff += 16;
		expect_len -= 16;
	  	
		OSSemCreate(&sem_ciu98m25_ready, 0);
		if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
		{
			return -7;
		}
	}
//==============================================================================
	//receive last pack data(less than 16 bytes)
RECV_LAST_PACK:
	CIU98M25_CS_ASSERT();
	CIU98M25_SPI_RECV(buff, expect_len);
	check_code = CIU98M25_SPI_TRANSFER(0xff);
	CIU98M25_CS_DEASSERT();
  
	OSSemCreate(&sem_ciu98m25_ready, 0);
	if( OSSemPend(&sem_ciu98m25_ready, CIU98M25_WRITE_TIMEOUT)!=OS_NO_ERR )
	{
		return -8;
	}
//==============================================================================
	//verify received data
	expect_len = (((uint16)sync[0])<<8) | sync[1];
	if(check_code != calc_check_code(rx_buff,expect_len) )return -9;
//==============================================================================
  	return expect_len;
}
//************************************************************************************************************
//by yangwensen@20190715
extern sint16 ciu98m25_transfer(uint8 *tbuff, uint16 tlen, uint8 *rbuff, uint16 rlen)
{
  	sint8 result;
	sint16 read_len;
	
//    if( IS_CIU98M25_BUSY() )return -1;
//==============================================================================	
	IO_OUT(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
	IO_MODE_PP(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
	IO_CLR(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
	
	OSTimeDly(1);
//==============================================================================
	result = ciu98m25_write(tbuff, tlen);
	if(result < 0)
	{
		IO_SET(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
		PRINT_ERROR_CODE("[Y]ciu98m25_transfer_wr", result);
		return -2;
	}
//==============================================================================
	read_len = ciu98m25_read(rbuff, rlen);
	if(read_len < 0)
	{
		CIU98M25_CS_DEASSERT();
		IO_SET(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
		PRINT_ERROR_CODE("[Y]ciu98m25_transfer_rd", read_len);
		return -2;
	}
//==============================================================================
	IO_SET(CIU98M25_SLEEP_PORT, CIU98M25_SLEEP_PIN);
	CIU98M25_PRINT_STRING("[Y]ciu98m25_transfer ok\r\n");
	
	return read_len;
}
//************************************************************************************************************
#if EN_SPU_DEBUG
static void print_error_code(uint8 *str, uint8 strlen, sint8 err)
{
  	err = -err;
	
	OSSemPend( &SemUart1Tx, 0 );

	Uart1PutRaw(str, strlen);
	
	UART1_PRINT_STRING_RAW(" = [-");
	Uart1PutUint8AsDecimal(err);
	UART1_PRINT_STRING_RAW("]\r\n");

	OSSemPost(&SemUart1Tx);//释放资源
}
#endif
//************************************************************************************************************
#if EN_SPU_TEST
//by yangwensen@20190715
uint8 spu_rx_buff[255];
extern void ciu98m25_test(void)
{
	uint8 t[] = {0x00, 0xa4, 0x04, 0x00, 0x00};
	sint16 len;
	
	len = ciu98m25_transfer(t, sizeof(t), spu_rx_buff, sizeof(spu_rx_buff));
	if(len<0)PRINT_ERROR_CODE("[Y]ciu98m25_transfer failed", len);
	else PrintHexArray(spu_rx_buff, len);
	
}
#endif
//************************************************************************************************************
