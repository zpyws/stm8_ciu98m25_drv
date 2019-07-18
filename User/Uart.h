#ifndef UART_USER_H
#define UART_USER_H
//*************************************************************
extern void InitUart1(uint32 baudrate);//��ʽ��8N1
extern boolean Uart1Send(uint8 *buff,uint16 len);
//extern void Uart1PrintString(uint8 * str);
////extern void SendToPC32(int32 dat);
extern uint8 Uart1PutRaw(uint8 *buff,uint16 len);
extern void Uart1PutUint8AsDecimal(uint8 dat);
//*************************************************************
//extern uint8 ROM HEX2ASCII[];
extern OS_SEM_t SemUart1Tx;
extern OS_SEM_t SemUart1RxOver;//����1һ֡�����ѽ������(���ճ�ʱ)
extern uint8 Uart1RxBuff[480];
extern uint16 Uart1RxPtr;//���ڷ��ͺͽ��չ��õĻ���ָ��
//*************************************************************
#define SBUF                     UART1->DR//51��ʽ�ĺ궨��
#define WAIT_UART_TX_IDLE()      while(!GBF(UART1->SR,UART_SR_TXE))//�ȴ����ڿ��Է���
#define UART1_SEND_BYTE(byte)    WAIT_UART_TX_IDLE();SBUF = byte
#define UART_WAIT_FRAME_SENT()   while(!TBI(UART1_SR,UART_TC))//If a frame transmission is complete(after the stop bit)and the TXE bit is set,the TC bit is SET.

#define DIS_UART_RX_INT()     CBF(UART1->CR2,UART1_CR2_RIEN)
#define EN_UART_RX_INT()      SBF(UART1->CR2,UART1_CR2_RIEN)

#define UART1_PRINT_STRING(str)  Uart1Send(str,sizeof(str)-1)//2012-11-27 by zpyws
#define UART1_PRINT_STRING_RAW(str)  Uart1PutRaw(str,sizeof(str)-1)//2012-11-27 by zpyws
//*************************************************************
#endif
