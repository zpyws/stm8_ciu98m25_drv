#include "common_zpyws.h"
//******************************************************************************************************************************
//******************************************************************************************************************************
#if 0
static sint8 uart_rx_data_resolve(uint8 *p, uint8 len)
{
	FrameStruct_t *ptr;

	if(ModbusRxLen<FRAME_SIZE_MIN)return(-1);
	ptr = (FrameStruct_t *)(p);
	if( check_device_type_match(ptr->Type) < 0 )return(-2);     //�豸���ͼ���
//	if(ptr->Addr!=MY_DEV_ADDRESS)return(-3);                    //�ӻ���ַ����
	if( CalcFrameChecksum(p, len-MODBUS_CRC_SIZE) != p[len-1])return(-4);
//==============================================================================
	LED1_ON();//�ҷ������е�ʱ��һ�µƣ��˳�����ʱ���
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
extern void UartRxDataProcess(uint8 *buff, uint8 len)
{
	DIS_UART_RX_INT();
//=======================================================================
	Uart1Send((uint8 *)Uart1RxBuff,Uart1RxPtr);
//	uart_rx_data_resolve(buff, len);
//=======================================================================
	Uart1RxPtr = 0;
	EN_UART_RX_INT();
}
//******************************************************************************************************************************
