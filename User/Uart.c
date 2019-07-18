#include "common_zpyws.h"
//*****************************************************************************
//修改日志	by zpyws
//STM8L152串口驱动程序(基于STM8L101修改) 2013-03-05 by zpyws
//2013-08-27  10:35 本文件STM8体系内移植无需修改(需要在Preprocessor设置CPU型号)，目前支持STM8L101,STM8L152
//2013-08-27  10:53 本文件STM8体系内移植无需修改(需要在Preprocessor设置CPU型号)，目前支持STM8S103,STM8L101,STM8L152
//2013-08-27  16:17 本文件STM8体系内移植无需修改(需要在Preprocessor设置CPU型号)，目前支持STM8S103,STM8L101,STM8L152,STM8S207,STM8S208
//*****************************************************************************
#define UART_TX_USE_INT         1//设置为1表示用中断方式发送
//===========Uart0=================================================
OS_SEM_t SemUart1Tx;//串口1发送信号量
OS_SEM_t SemUart1TxInt;//发送中断的标志
OS_SEM_t SemUart1RxOver;//串口1一帧数据已接收完成(接收超时)

uint8 Uart1RxBuff[480];
uint16 Uart1RxPtr = 0;//接收指针

uint8 Uart1TxBuff[16];
uint8 Uart1TxPtr = 0;//发送指针
uint8 Uart1TxLen = 0;//要发送的数据长度
//*****************************************************************************
#define OK        0
#define ERR       1

#if defined(STM8S103) || defined(STM8S207) || defined(STM8S208) ||\
	defined(STM8S105)//2014-03-28  BY ZPYWS
	#define CPU_STM8Sxxx
#endif
//*****************************************************************************
#if defined(CPU_STM8Sxxx)
extern void InitUart1(uint32 baudrate)
{
	uint16 div;

	UART1->CR1 = 0x00;//为防止二次配置时出错
	UART1->CR2 = 0x00;//为防止二次配置时出错
//========================================================================================================
#if defined(STM8S103)
	SBF(CLK->PCKENR1, CLK_PCKENR1_UART2);//打开外设时钟
#else
	SBF(CLK->PCKENR1, CLK_PCKENR1_UART1);//打开外设时钟
#endif
	div = F_PCLK / baudrate;//分频系数

	if( (F_PCLK % baudrate) >= (baudrate/2) )div++;//四舍五入,此句编译生成161个RO-code
//========================================================================================================
	UART1->BRR2 = (uint8)(div&0x000f) + (((uint8)(div>>8)) & 0xf0);
	UART1->BRR1 = (uint8)(div>>4);
	UART1->CR1 = CC(UART1_CR1_R8)|CC(UART1_CR1_T8)|CC(UART1_CR1_UARTD)|CC(UART1_CR1_M)|CC(UART1_CR1_WAKE)|CC(UART1_CR1_PCEN)|CC(UART1_CR1_PS)|CC(UART1_CR1_PIEN);//，，使能UART，8位数据,无校验,,奇偶检验中断关闭
	UART1->CR2 = CC(UART1_CR2_TIEN)|CC(UART1_CR2_TCIEN)|(UART1_CR2_RIEN)|(UART1_CR2_ILIEN)|(UART1_CR2_TEN)|(UART1_CR2_REN)|CC(UART1_CR2_RWU)|CC(UART1_CR2_SBK);//禁止发送中断,禁发送完成中断,使能接收中断,使用空闲中断,允许发送，允许接收,接收器激活，,
//========================================================================================================
	OSSemCreate(&SemUart1Tx, 1);
	OSSemCreate(&SemUart1RxOver, 0);
}
#endif
//*****************************************************************************
#if defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
extern void InitUart1(uint32 baudrate)
{
	uint16 div;

//========================================================================================================
#if defined(STM8L101)
	//配置发送脚PC3
	IO_OUT(PC,3);		//对于STML101，需要配置IO口才能发送。这点与STMS103不同
	IO_MODE_PP(PC,3);

	//配置接收脚PC2
	IO_MODE_PU(PC,2);

	SBF(CLK->PCKENR, CLK_PCKENR_USART);//打开外设时钟
//========================================================================================================
#elif defined(STM8L152)
	BF_MOD( SYSCFG->RMPCR1, (3<<4), (2<<4) );//串口引脚映射10: USART1_TX on PC5 and USART1_RX on PC6

	//配置发送脚PC5
	IO_OUT(PC,5);		//对于STML152，需要配置IO口才能发送。这点与STMS103不同
	IO_MODE_PP(PC,5);

//	//配置接收脚PC6
	IO_IN(PC,6);		//对于STML152，需要配置IO口才能发送。这点与STMS103不同
	IO_MODE_PU(PC,6);

	SBF(CLK->PCKENR1, CLK_PCKENR1_USART1);//打开外设时钟
#endif
//========================================================================================================
	div = F_PCLK / baudrate;//分频系数

	if( (F_PCLK % baudrate) >= (baudrate/2) )div++;//四舍五入,此句编译生成161个RO-code
//========================================================================================================
	USART1->BRR2 = (uint8)(div&0x000f) + (((uint8)(div>>8)) & 0xf0);
	USART1->BRR1 = (uint8)(div>>4);
	USART1->CR1 = CC(USART_CR1_R8)|CC(USART_CR1_T8)|CC(USART_CR1_USARTD)|CC(USART_CR1_M)|CC(USART_CR1_WAKE)|CC(USART_CR1_PCEN)|CC(USART_CR1_PS)|CC(USART_CR1_PIEN);//，，使能UART，8位数据,无校验,,奇偶检验中断关闭
	USART1->CR2 = CC(USART_CR2_TIEN)|CC(USART_CR2_TCIEN)|(USART_CR2_RIEN)|(USART_CR2_ILIEN)|(USART_CR2_TEN)|(USART_CR2_REN)|CC(USART_CR2_RWU)|CC(USART_CR2_SBK);//禁止发送中断,禁发送完成中断,使能接收中断,使用空闲中断,允许发送，允许接收,接收器激活，,
//========================================================================================================
	OSSemCreate(&SemUart1Tx, 1);
	OSSemCreate(&SemUart1RxOver, 0);
}
#endif
//*****************************************************************************
//extern void Uart1PrintString(uint8 * str)
//{
//	if( OSSemPend( &SemUart1Tx, 200 )==OS_NO_ERR )
//	{
//		while(*str)
//		{
//			WAIT_UART_TX_IDLE();
//			SBUF = *str++;
//		}
//		OSSemPost(&SemUart1Tx);//释放资源
//	}
//}
//********************************************************************************************
#if UART_TX_USE_INT > 0
#if defined(CPU_STM8Sxxx)
//2013-01-31 by zpyws
//此函数是所有要发送的数据位全部发完才退出
extern uint8 Uart1PutRaw(uint8 *buff,uint16 len)
{
	uint8 send_len;

	if(len==0)return(0);
	len--;			//最后一字节做特殊处理
	if(len==0)		//最后一字节做特殊处理
	{
		Uart1TxLen = 0;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
		goto U1_PUT_RAW_1;
	}
//===========================================================================================================
U1_PUT_RAW_0:
//	OSSemCreate(&SemUart1TxInt, 0);//发送前强制设定为0
	if(len>sizeof(Uart1TxBuff))send_len = sizeof(Uart1TxBuff);//一次发不完，分多包发送
	else send_len = len;//可以一次性发完(最后一帧)
	MemCpy((uint8 *)Uart1TxBuff, buff, send_len);
	Uart1TxPtr = 0;
	Uart1TxLen = send_len;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
	SBF(UART1->CR2, UART1_CR2_TIEN);//使能UART_TDR空中断
//===========================================================================================================
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//超时设置为0时为无限等待
	{
//		LED1_ON();
		return(1);//返回错误
	}
//	OSSemPend(&SemUart1TxInt, 0);//超时设置为0时为无限等待
	len -= send_len;//计算还剩多少字节没发
	buff += send_len;//新的数据偏移要改
	if(len)goto U1_PUT_RAW_0;//数据还没发完
//===========================================================================================================
U1_PUT_RAW_1://最后一个字节做特殊处理
//	OSSemCreate(&SemUart1TxInt, 0);//发送前强制设定为0
	CBF(UART1->SR, UART1_SR_TC);//打开中断前清除UART_TC中断标志位
	UART1->DR = *buff;//取出最后一个字节
	SBF(UART1->CR2, UART1_CR2_TCIEN);//Transmission complete interrupt enable包括移位寄存器里的数据也发送完成
//	OSSemPend(&SemUart1TxInt, 0);//超时设置为0时为无限等待
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//超时设置为0时为无限等待
	{
//		LED1_ON();
		return(2);//返回错误
	}
	return(0);
}
#endif
//********************************************************************************************
//2013-01-31 by zpyws
//此函数是所有要发送的数据位全部发完才退出
#if defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
extern uint8 Uart1PutRaw(uint8 *buff,uint8 len)
{
	uint8 send_len;

	if(len==0)return(0);
	len--;			//最后一字节做特殊处理
	if(len==0)		//最后一字节做特殊处理
	{
		Uart1TxLen = 0;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
		goto U1_PUT_RAW_1;
	}
//===========================================================================================================
U1_PUT_RAW_0:
//	OSSemCreate(&SemUart1TxInt, 0);//发送前强制设定为0
	if(len>sizeof(Uart1TxBuff))send_len = sizeof(Uart1TxBuff);//一次发不完，分多包发送
	else send_len = len;//可以一次性发完(最后一帧)
	MemCpy((uint8 *)Uart1TxBuff, buff, send_len);
	Uart1TxPtr = 0;
	Uart1TxLen = send_len;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
	SBF(USART1->CR2, USART_CR2_TIEN);//使能UART_TDR空中断
//===========================================================================================================
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//超时设置为0时为无限等待
	{
//		LED1_ON();
		return(1);//返回错误
	}
//	OSSemPend(&SemUart1TxInt, 0);//超时设置为0时为无限等待
	len -= send_len;//计算还剩多少字节没发
	buff += send_len;//新的数据偏移要改
	if(len)goto U1_PUT_RAW_0;//数据还没发完
//===========================================================================================================
U1_PUT_RAW_1://最后一个字节做特殊处理
//	OSSemCreate(&SemUart1TxInt, 0);//发送前强制设定为0
	CBF(USART1->SR, USART_SR_TC);//打开中断前清除UART_TC中断标志位
	USART1->DR = *buff;//取出最后一个字节
	SBF(USART1->CR2, USART_CR2_TCIEN);//Transmission complete interrupt enable包括移位寄存器里的数据也发送完成
//	OSSemPend(&SemUart1TxInt, 0);//超时设置为0时为无限等待
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//超时设置为0时为无限等待
	{
//		LED1_ON();
		return(2);//返回错误
	}
	return(0);
}
#endif
//********************************************************************************************
#else
#if defined(CPU_STM8Sxxx) || defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
extern uint8 Uart1PutRaw(uint8 *buff,uint8 len)
{
	while(len--)
	{
		WAIT_UART_TX_IDLE();
		USART_DR = *buff++;
	}
	return(0);
}
#endif
#endif
//********************************************************************************************
//extern void Uart1PutUint8AsDecimal(uint8 dat)
//{
//	WAIT_UART_TX_IDLE();SBUF = HEX2ASCII[ dat/10 ];
//	WAIT_UART_TX_IDLE();SBUF = HEX2ASCII[ dat%10 ];
//}
//********************************************************************************************
//2013-01-31 by zpyws
extern void Uart1PutUint8AsDecimal(uint8 dat)
{
	uint8 temp[2];
	
	temp[0] = TAB_HEX_NUM_ASCII[ dat/10 ];
	temp[1] = TAB_HEX_NUM_ASCII[ dat%10 ];
	Uart1PutRaw(temp, 2);
}
//********************************************************************************************
//extern boolean Uart1Send(uint8 *buff,uint8 len)
//{
//	if( OSSemPend( &SemUart1Tx, 200 )==OS_NO_ERR )
//	{
//		while(len--)
//		{
//			WAIT_UART_TX_IDLE();
//			SBUF = *buff++;
//		}
//		UART_WAIT_FRAME_SENT();
//		OSSemPost(&SemUart1Tx);//释放资源
//		return(OK);
//	}
//	return(ERR);
//}
//********************************************************************************************
//2013-01-31 by zpyws
extern boolean Uart1Send(uint8 *buff,uint16 len)
{
	if( OSSemPend( &SemUart1Tx, OS_TICKS_PER_SEC*5 )==OS_NO_ERR )
	{
		if( Uart1PutRaw(buff, len) )
		{
			OSSemPost(&SemUart1Tx);//释放资源
			return(OS_TIMEOUT);
		}

		OSSemPost(&SemUart1Tx);//释放资源
		return(OK);
	}
	return(OS_TIMEOUT);
}
//********************************************************************************************
#if defined(CPU_STM8Sxxx)
ISR(UART1_R_OR_vector)
{
	uint8 temp;

	OSIntEnter();
//======================================================================================================================
	if( GBF(UART1->SR,UART1_SR_RXNE) )//接收器不为空
	{
		if( Uart1RxPtr<sizeof(Uart1RxBuff) )Uart1RxBuff[Uart1RxPtr] = UART1->DR;//接收数据	
		else CBF(UART1->SR,UART1_SR_RXNE);//清除中断标志位RXNE有两种方法：读SBUF或直接清RXNE位
		Uart1RxPtr++;//在MCU处理接收数据程序时就以此变量来得知接收到的数据长度
	}
	else if( GBF(UART1->SR,UART1_SR_IDLE) )//总线空闲中断The IDLE bit will not be set again until the RXNE bit has been set itself
	{
        temp = UART1->SR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = UART1->DR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = temp;//to supress complier warning
		OSSemIntPost(&SemUart1RxOver);//通知前台程序一帧串口数据接收结束	
	}
//======================================================================================================================
	OSIntExit();
}
#endif
//********************************************************************************************
#if defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
ISR(USART_R_OR_vector)
{
	uint8 temp;

	OSIntEnter();
//======================================================================================================================
	if( GBF(USART1->SR, USART_SR_RXNE) )//接收器不为空
	{
		if( Uart1RxPtr<sizeof(Uart1RxBuff) )Uart1RxBuff[Uart1RxPtr] = USART1->DR;//接收数据	
		else CBF(USART1->SR, USART_SR_RXNE);//清除中断标志位RXNE有两种方法：读SBUF或直接清RXNE位
		Uart1RxPtr++;//在MCU处理接收数据程序时就以此变量来得知接收到的数据长度
	}
	else if( GBF(USART1->SR, USART_SR_IDLE) )//总线空闲中断The IDLE bit will not be set again until the RXNE bit has been set itself
	{
        temp = USART1->SR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = USART1->DR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = temp;//to supress complier warning
		OSSemIntPost(&SemUart1RxOver);//通知前台程序一帧串口数据接收结束	
	}
//======================================================================================================================
	OSIntExit();
}
#endif
//*****************************************************************************
//2013-01-31 by zpyws
#if defined(CPU_STM8Sxxx)
ISR(UART1_T_TXE_vector)
{
	OSIntEnter();
//======================================================================================================================
	//如果空中断有打开
//	if( TBI(UART1_CR2, TIEN) && TBI(UART1_SR,TXE) )//Transmit data register empty
	if( GBF(UART1->CR2, UART1_CR2_TIEN) )//Transmit data register empty
	{
		if(Uart1TxPtr>=Uart1TxLen)//发送完成了
		{
			CBF(UART1->CR2, UART1_CR2_TIEN);//禁能UART_TDR空中断
			Uart1TxLen = 0;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
			OSSemIntPost(&SemUart1TxInt);
		}
		else UART1->DR = Uart1TxBuff[Uart1TxPtr++];//TXE is cleared by a write to the UART_DR register
	}
//	if( TBI(UART1_SR,UART_TC) )//Transmission completeinterrupt包括移位寄存器里的数据也发送完成
	else		//否则就是发送完成中断
	{
		CBF(UART1->CR2, UART1_CR2_TCIEN);//禁能UART_TC中断
		CBF(UART1->SR, UART1_SR_TC);//清除UART_TC中断
		OSSemIntPost(&SemUart1TxInt);
	}
//======================================================================================================================
	OSIntExit();
}
#endif
//*****************************************************************************
//2013-01-31 by zpyws
#if defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
ISR(USART_T_TXE_vector)
{
	OSIntEnter();
//======================================================================================================================
	//如果空中断有打开
//	if( TBI(UART1_CR2, TIEN) && TBI(UART1_SR,TXE) )//Transmit data register empty
	if( GBF(USART1->CR2, USART_CR2_TIEN) )//Transmit data register empty
	{
		if(Uart1TxPtr>=Uart1TxLen)//发送完成了
		{
			CBF(USART1->CR2, USART_CR2_TIEN);//禁能UART_TDR空中断
			Uart1TxLen = 0;//发送前可先检测此变量是否为0，如为0，则说明可以发数据，否则串口发送被占用
			OSSemIntPost(&SemUart1TxInt);
		}
		else USART1->DR = Uart1TxBuff[Uart1TxPtr++];//TXE is cleared by a write to the UART_DR register
	}
//	if( TBI(UART1_SR,UART_TC) )//Transmission completeinterrupt包括移位寄存器里的数据也发送完成
	else		//否则就是发送完成中断
	{
		CBF(USART1->CR2, USART_CR2_TCIEN);//禁能UART_TC中断
		CBF(USART1->SR, USART_SR_TC);//清除UART_TC中断
		OSSemIntPost(&SemUart1TxInt);
	}
//======================================================================================================================
	OSIntExit();
}
#endif
//*****************************************************************************
