#include "common_zpyws.h"
#include "ciu98m25.h"
//******************************************************************************************************************************
#if 0
static sint8 uart_rx_data_resolve(uint8 *p, uint8 len)
{
	FrameStruct_t *ptr;

	if(ModbusRxLen<FRAME_SIZE_MIN)return(-1);
	ptr = (FrameStruct_t *)(p);
	if( check_device_type_match(ptr->Type) < 0 )return(-2);     //设备类型检验
//	if(ptr->Addr!=MY_DEV_ADDRESS)return(-3);                    //从机地址检验
	if( CalcFrameChecksum(p, len-MODBUS_CRC_SIZE) != p[len-1])return(-4);
//==============================================================================
	LED1_ON();//我方被呼叫到时闪一下灯，退出函数时灭灯
	switch(ptr->Cmd)
	{
		case CMD_READ: cmd_read(ptr, len);break;
		case CMD_WRITE:cmd_write(ptr, len);break;
		case CMD_ABOUT:cmd_about(ptr, len);break;
		case CMD_REBOOT:cmd_reboot(ptr, len);break;
		default:break;
	}
	LED1_OFF();
//==============================================================================
	return(0);
}
#endif
//****************************************************************************************************************************
static uint8 spu_rx_buff[253];
extern void UartRxDataProcess(uint8 *buff, uint16 len)
{
  	sint16 result;
	
	DIS_UART_RX_INT();
//=======================================================================
//	uart_rx_data_resolve(buff, len);
	
	result = ciu98m25_transfer(Uart1RxBuff, Uart1RxPtr, spu_rx_buff, sizeof(spu_rx_buff));
	
	if(result<0)UART1_PRINT_STRING("[Y]ciu98m25_transfer failed\r\n");
	else
	{
	  	Uart1Send(spu_rx_buff, result);
	}
//=======================================================================
	Uart1RxPtr = 0;
	EN_UART_RX_INT();
}
//******************************************************************************************************************************
