#include "common_zpyws.h"
//*****************************************************************************
//�޸���־	by zpyws
//STM8L152������������(����STM8L101�޸�) 2013-03-05 by zpyws
//2013-08-27  10:35 ���ļ�STM8��ϵ����ֲ�����޸�(��Ҫ��Preprocessor����CPU�ͺ�)��Ŀǰ֧��STM8L101,STM8L152
//2013-08-27  10:53 ���ļ�STM8��ϵ����ֲ�����޸�(��Ҫ��Preprocessor����CPU�ͺ�)��Ŀǰ֧��STM8S103,STM8L101,STM8L152
//2013-08-27  16:17 ���ļ�STM8��ϵ����ֲ�����޸�(��Ҫ��Preprocessor����CPU�ͺ�)��Ŀǰ֧��STM8S103,STM8L101,STM8L152,STM8S207,STM8S208
//*****************************************************************************
#define UART_TX_USE_INT         1//����Ϊ1��ʾ���жϷ�ʽ����
//===========Uart0=================================================
OS_SEM_t SemUart1Tx;//����1�����ź���
OS_SEM_t SemUart1TxInt;//�����жϵı�־
OS_SEM_t SemUart1RxOver;//����1һ֡�����ѽ������(���ճ�ʱ)

uint8 Uart1RxBuff[480];
uint16 Uart1RxPtr = 0;//����ָ��

uint8 Uart1TxBuff[16];
uint8 Uart1TxPtr = 0;//����ָ��
uint8 Uart1TxLen = 0;//Ҫ���͵����ݳ���
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

	UART1->CR1 = 0x00;//Ϊ��ֹ��������ʱ����
	UART1->CR2 = 0x00;//Ϊ��ֹ��������ʱ����
//========================================================================================================
#if defined(STM8S103)
	SBF(CLK->PCKENR1, CLK_PCKENR1_UART2);//������ʱ��
#else
	SBF(CLK->PCKENR1, CLK_PCKENR1_UART1);//������ʱ��
#endif
	div = F_PCLK / baudrate;//��Ƶϵ��

	if( (F_PCLK % baudrate) >= (baudrate/2) )div++;//��������,�˾��������161��RO-code
//========================================================================================================
	UART1->BRR2 = (uint8)(div&0x000f) + (((uint8)(div>>8)) & 0xf0);
	UART1->BRR1 = (uint8)(div>>4);
	UART1->CR1 = CC(UART1_CR1_R8)|CC(UART1_CR1_T8)|CC(UART1_CR1_UARTD)|CC(UART1_CR1_M)|CC(UART1_CR1_WAKE)|CC(UART1_CR1_PCEN)|CC(UART1_CR1_PS)|CC(UART1_CR1_PIEN);//����ʹ��UART��8λ����,��У��,,��ż�����жϹر�
	UART1->CR2 = CC(UART1_CR2_TIEN)|CC(UART1_CR2_TCIEN)|(UART1_CR2_RIEN)|(UART1_CR2_ILIEN)|(UART1_CR2_TEN)|(UART1_CR2_REN)|CC(UART1_CR2_RWU)|CC(UART1_CR2_SBK);//��ֹ�����ж�,����������ж�,ʹ�ܽ����ж�,ʹ�ÿ����ж�,�����ͣ��������,���������,
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
	//���÷��ͽ�PC3
	IO_OUT(PC,3);		//����STML101����Ҫ����IO�ڲ��ܷ��͡������STMS103��ͬ
	IO_MODE_PP(PC,3);

	//���ý��ս�PC2
	IO_MODE_PU(PC,2);

	SBF(CLK->PCKENR, CLK_PCKENR_USART);//������ʱ��
//========================================================================================================
#elif defined(STM8L152)
	BF_MOD( SYSCFG->RMPCR1, (3<<4), (2<<4) );//��������ӳ��10: USART1_TX on PC5 and USART1_RX on PC6

	//���÷��ͽ�PC5
	IO_OUT(PC,5);		//����STML152����Ҫ����IO�ڲ��ܷ��͡������STMS103��ͬ
	IO_MODE_PP(PC,5);

//	//���ý��ս�PC6
	IO_IN(PC,6);		//����STML152����Ҫ����IO�ڲ��ܷ��͡������STMS103��ͬ
	IO_MODE_PU(PC,6);

	SBF(CLK->PCKENR1, CLK_PCKENR1_USART1);//������ʱ��
#endif
//========================================================================================================
	div = F_PCLK / baudrate;//��Ƶϵ��

	if( (F_PCLK % baudrate) >= (baudrate/2) )div++;//��������,�˾��������161��RO-code
//========================================================================================================
	USART1->BRR2 = (uint8)(div&0x000f) + (((uint8)(div>>8)) & 0xf0);
	USART1->BRR1 = (uint8)(div>>4);
	USART1->CR1 = CC(USART_CR1_R8)|CC(USART_CR1_T8)|CC(USART_CR1_USARTD)|CC(USART_CR1_M)|CC(USART_CR1_WAKE)|CC(USART_CR1_PCEN)|CC(USART_CR1_PS)|CC(USART_CR1_PIEN);//����ʹ��UART��8λ����,��У��,,��ż�����жϹر�
	USART1->CR2 = CC(USART_CR2_TIEN)|CC(USART_CR2_TCIEN)|(USART_CR2_RIEN)|(USART_CR2_ILIEN)|(USART_CR2_TEN)|(USART_CR2_REN)|CC(USART_CR2_RWU)|CC(USART_CR2_SBK);//��ֹ�����ж�,����������ж�,ʹ�ܽ����ж�,ʹ�ÿ����ж�,�����ͣ��������,���������,
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
//		OSSemPost(&SemUart1Tx);//�ͷ���Դ
//	}
//}
//********************************************************************************************
#if UART_TX_USE_INT > 0
#if defined(CPU_STM8Sxxx)
//2013-01-31 by zpyws
//�˺���������Ҫ���͵�����λȫ��������˳�
extern uint8 Uart1PutRaw(uint8 *buff,uint16 len)
{
	uint8 send_len;

	if(len==0)return(0);
	len--;			//���һ�ֽ������⴦��
	if(len==0)		//���һ�ֽ������⴦��
	{
		Uart1TxLen = 0;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
		goto U1_PUT_RAW_1;
	}
//===========================================================================================================
U1_PUT_RAW_0:
//	OSSemCreate(&SemUart1TxInt, 0);//����ǰǿ���趨Ϊ0
	if(len>sizeof(Uart1TxBuff))send_len = sizeof(Uart1TxBuff);//һ�η����꣬�ֶ������
	else send_len = len;//����һ���Է���(���һ֡)
	MemCpy((uint8 *)Uart1TxBuff, buff, send_len);
	Uart1TxPtr = 0;
	Uart1TxLen = send_len;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
	SBF(UART1->CR2, UART1_CR2_TIEN);//ʹ��UART_TDR���ж�
//===========================================================================================================
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//��ʱ����Ϊ0ʱΪ���޵ȴ�
	{
//		LED1_ON();
		return(1);//���ش���
	}
//	OSSemPend(&SemUart1TxInt, 0);//��ʱ����Ϊ0ʱΪ���޵ȴ�
	len -= send_len;//���㻹ʣ�����ֽ�û��
	buff += send_len;//�µ�����ƫ��Ҫ��
	if(len)goto U1_PUT_RAW_0;//���ݻ�û����
//===========================================================================================================
U1_PUT_RAW_1://���һ���ֽ������⴦��
//	OSSemCreate(&SemUart1TxInt, 0);//����ǰǿ���趨Ϊ0
	CBF(UART1->SR, UART1_SR_TC);//���ж�ǰ���UART_TC�жϱ�־λ
	UART1->DR = *buff;//ȡ�����һ���ֽ�
	SBF(UART1->CR2, UART1_CR2_TCIEN);//Transmission complete interrupt enable������λ�Ĵ����������Ҳ�������
//	OSSemPend(&SemUart1TxInt, 0);//��ʱ����Ϊ0ʱΪ���޵ȴ�
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//��ʱ����Ϊ0ʱΪ���޵ȴ�
	{
//		LED1_ON();
		return(2);//���ش���
	}
	return(0);
}
#endif
//********************************************************************************************
//2013-01-31 by zpyws
//�˺���������Ҫ���͵�����λȫ��������˳�
#if defined(STM8L101) || defined(STM8L152)//2013-08-27  BY ZPYWS
extern uint8 Uart1PutRaw(uint8 *buff,uint8 len)
{
	uint8 send_len;

	if(len==0)return(0);
	len--;			//���һ�ֽ������⴦��
	if(len==0)		//���һ�ֽ������⴦��
	{
		Uart1TxLen = 0;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
		goto U1_PUT_RAW_1;
	}
//===========================================================================================================
U1_PUT_RAW_0:
//	OSSemCreate(&SemUart1TxInt, 0);//����ǰǿ���趨Ϊ0
	if(len>sizeof(Uart1TxBuff))send_len = sizeof(Uart1TxBuff);//һ�η����꣬�ֶ������
	else send_len = len;//����һ���Է���(���һ֡)
	MemCpy((uint8 *)Uart1TxBuff, buff, send_len);
	Uart1TxPtr = 0;
	Uart1TxLen = send_len;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
	SBF(USART1->CR2, USART_CR2_TIEN);//ʹ��UART_TDR���ж�
//===========================================================================================================
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//��ʱ����Ϊ0ʱΪ���޵ȴ�
	{
//		LED1_ON();
		return(1);//���ش���
	}
//	OSSemPend(&SemUart1TxInt, 0);//��ʱ����Ϊ0ʱΪ���޵ȴ�
	len -= send_len;//���㻹ʣ�����ֽ�û��
	buff += send_len;//�µ�����ƫ��Ҫ��
	if(len)goto U1_PUT_RAW_0;//���ݻ�û����
//===========================================================================================================
U1_PUT_RAW_1://���һ���ֽ������⴦��
//	OSSemCreate(&SemUart1TxInt, 0);//����ǰǿ���趨Ϊ0
	CBF(USART1->SR, USART_SR_TC);//���ж�ǰ���UART_TC�жϱ�־λ
	USART1->DR = *buff;//ȡ�����һ���ֽ�
	SBF(USART1->CR2, USART_CR2_TCIEN);//Transmission complete interrupt enable������λ�Ĵ����������Ҳ�������
//	OSSemPend(&SemUart1TxInt, 0);//��ʱ����Ϊ0ʱΪ���޵ȴ�
	if( OSSemPend(&SemUart1TxInt, OS_TICKS_PER_SEC/50)!=OS_NO_ERR )//��ʱ����Ϊ0ʱΪ���޵ȴ�
	{
//		LED1_ON();
		return(2);//���ش���
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
//		OSSemPost(&SemUart1Tx);//�ͷ���Դ
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
			OSSemPost(&SemUart1Tx);//�ͷ���Դ
			return(OS_TIMEOUT);
		}

		OSSemPost(&SemUart1Tx);//�ͷ���Դ
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
	if( GBF(UART1->SR,UART1_SR_RXNE) )//��������Ϊ��
	{
		if( Uart1RxPtr<sizeof(Uart1RxBuff) )Uart1RxBuff[Uart1RxPtr] = UART1->DR;//��������	
		else CBF(UART1->SR,UART1_SR_RXNE);//����жϱ�־λRXNE�����ַ�������SBUF��ֱ����RXNEλ
		Uart1RxPtr++;//��MCU����������ݳ���ʱ���Դ˱�������֪���յ������ݳ���
	}
	else if( GBF(UART1->SR,UART1_SR_IDLE) )//���߿����ж�The IDLE bit will not be set again until the RXNE bit has been set itself
	{
        temp = UART1->SR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = UART1->DR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = temp;//to supress complier warning
		OSSemIntPost(&SemUart1RxOver);//֪ͨǰ̨����һ֡�������ݽ��ս���	
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
	if( GBF(USART1->SR, USART_SR_RXNE) )//��������Ϊ��
	{
		if( Uart1RxPtr<sizeof(Uart1RxBuff) )Uart1RxBuff[Uart1RxPtr] = USART1->DR;//��������	
		else CBF(USART1->SR, USART_SR_RXNE);//����жϱ�־λRXNE�����ַ�������SBUF��ֱ����RXNEλ
		Uart1RxPtr++;//��MCU����������ݳ���ʱ���Դ˱�������֪���յ������ݳ���
	}
	else if( GBF(USART1->SR, USART_SR_IDLE) )//���߿����ж�The IDLE bit will not be set again until the RXNE bit has been set itself
	{
        temp = USART1->SR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = USART1->DR;//It is cleared by a software sequence (a read to the UART_SR register followed by a read to the UART_DR register)
		temp = temp;//to supress complier warning
		OSSemIntPost(&SemUart1RxOver);//֪ͨǰ̨����һ֡�������ݽ��ս���	
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
	//������ж��д�
//	if( TBI(UART1_CR2, TIEN) && TBI(UART1_SR,TXE) )//Transmit data register empty
	if( GBF(UART1->CR2, UART1_CR2_TIEN) )//Transmit data register empty
	{
		if(Uart1TxPtr>=Uart1TxLen)//���������
		{
			CBF(UART1->CR2, UART1_CR2_TIEN);//����UART_TDR���ж�
			Uart1TxLen = 0;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
			OSSemIntPost(&SemUart1TxInt);
		}
		else UART1->DR = Uart1TxBuff[Uart1TxPtr++];//TXE is cleared by a write to the UART_DR register
	}
//	if( TBI(UART1_SR,UART_TC) )//Transmission completeinterrupt������λ�Ĵ����������Ҳ�������
	else		//������Ƿ�������ж�
	{
		CBF(UART1->CR2, UART1_CR2_TCIEN);//����UART_TC�ж�
		CBF(UART1->SR, UART1_SR_TC);//���UART_TC�ж�
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
	//������ж��д�
//	if( TBI(UART1_CR2, TIEN) && TBI(UART1_SR,TXE) )//Transmit data register empty
	if( GBF(USART1->CR2, USART_CR2_TIEN) )//Transmit data register empty
	{
		if(Uart1TxPtr>=Uart1TxLen)//���������
		{
			CBF(USART1->CR2, USART_CR2_TIEN);//����UART_TDR���ж�
			Uart1TxLen = 0;//����ǰ���ȼ��˱����Ƿ�Ϊ0����Ϊ0����˵�����Է����ݣ����򴮿ڷ��ͱ�ռ��
			OSSemIntPost(&SemUart1TxInt);
		}
		else USART1->DR = Uart1TxBuff[Uart1TxPtr++];//TXE is cleared by a write to the UART_DR register
	}
//	if( TBI(UART1_SR,UART_TC) )//Transmission completeinterrupt������λ�Ĵ����������Ҳ�������
	else		//������Ƿ�������ж�
	{
		CBF(USART1->CR2, USART_CR2_TCIEN);//����UART_TC�ж�
		CBF(USART1->SR, USART_SR_TC);//���UART_TC�ж�
		OSSemIntPost(&SemUart1TxInt);
	}
//======================================================================================================================
	OSIntExit();
}
#endif
//*****************************************************************************
