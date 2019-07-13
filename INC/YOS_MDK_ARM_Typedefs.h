#ifndef YOS_ARM_MDK_TYPEDEFS_H
#define YOS_ARM_MDK_TYPEDEFS_H
//2014-07-08  15:57 ����
//******************************************************************************************************************************
#ifdef __CC_ARM	//Always set to 1 for the ARM compiler, even when you specify the --thumb option.
	#define ARCH_ARM
	#define _BYTE_ORDER_		0//0->С�˸�ʽ	1->��˸�ʽ
#endif
//******************************************************************************************************************************
#ifdef __CC_ARM	//Always set to 1 for the ARM compiler, even when you specify the --thumb option.
	typedef unsigned char  	BOOL;
	typedef unsigned char  	bool;
	typedef unsigned char  	boolean;
	
	typedef unsigned char  	uint8;                                  
	typedef signed char    	sint8;                                  
	typedef signed char    	int8;                                   
	
	typedef unsigned short 	uint16;                                 
	typedef signed short   	int16;                                  
	typedef signed short   	sint16;                                 
	
	typedef unsigned long  	uint32;                                 
	typedef signed long  	int32;                                  
	typedef signed long  	sint32;    
	
	typedef unsigned long long	uint64;
	typedef signed long long	sint64;

	typedef float			fl32;
	typedef double			fl64;
#endif
//******************************************************************************************************************************
#ifdef __CC_ARM	//Always set to 1 for the ARM compiler, even when you specify the --thumb option.
	typedef unsigned int	size_t;//2013-03-7 by zpyws
#endif
//******************************************************************************************************************************
#ifdef __CC_ARM	//Always set to 1 for the ARM compiler, even when you specify the --thumb option.
	#define ROM					const
	#define ISR(IntHandler)		void IntHandler(void)//2012-08-15 by zpyws
	#define __TASK				__declspec(noreturn)
	#define __ALIGN(bytes)      __align(bytes)//�ֽڶ���
	#define __INLINE            __inline//��������
	#define __ASM            	__asm   //asm keyword for ARM Compiler
	#define __PACKED			__packed//ѹ���洢
//	#define __RESET()			do{*((volatile uint32 *)0xE000ED0C) = 0x05fa0000|0x00000004;}while(0)  //Cortex-M3�����λ 2013-06-23 by zpyws
#endif
//*****Nuvoton M051*************************************************************************************************************************
#ifdef M051
	#define __RESET()			do{UnlockCPUReg();SYS->IPRSTC1 |= SYS_IPRSTC1_CHIP_RST;}while(0)  //M051�����λ 2014-07-11 by zpyws
#endif

#if defined(M051)
	// Nuvoton M051 IO�ڲ�����
	// 2014-07-09  by zpyws
	
	//��ĳһIO������Ϊ����ģʽ  by zpyws
	#define _IO_IN(port,pin)     		BF_CLR(port##->PMD, 3UL<<((pin)<<1))						//PxPMD = 00
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//��ĳһIO������Ϊ���ģʽ  by zpyws
	#define _IO_OUT(port,pin)     		BF_MOD(port->PMD, 3UL<<((pin)<<1), 1UL<<((pin)<<1))		//Px_PMD = 01
	#define IO_OUT(port,pin)      		_IO_OUT(port,pin)
	
	//��ĳһ���������Ϊ����(���)ģʽ  by zpyws
	#define _IO_MODE_PP(port,pin)     	BF_MOD(port##->PMD, 3UL<<((pin)<<1), 1UL<<((pin)<<1))	//Px_PMD = 01
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//��ĳһ���������Ϊ��©(���)ģʽ  by zpyws
	#define _IO_MODE_OD(port,pin)     	BF_MOD(port##->PMD, 3UL<<((pin)<<1), 2UL<<((pin)<<1))	//Px_PMD = 10
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ  by zpyws
	#define _IO_MODE_FL(port,pin)     	BF_CLR(port##->PMD, 3UL<<((pin)<<1))						//PxPMD = 00
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ  by zpyws
	#define _IO_MODE_PU(port,pin)     	do{IO_SET(port,pin);BF_SET(port##->PMD, 3UL<<((pin)<<1));}while(0)	//Px_PMD = 11
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//��ĳһ���������ߵ�ƽ  by zpyws
	#define _IO_SET(port,pin)     	port##->DOUT |= (1<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//��ĳһ���������͵�ƽ  by zpyws
	#define _IO_CLR(port,pin)     	port##->DOUT &= ~(1<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
	#define _IO_TOG(port,pin)     	port##->DOUT ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IO_RD(port,pin)		( port##->PIN & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
	#define _IO_FLP(port,pin)     	port##->DOUT ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IO_GET(port,pin)		( port##->PIN & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
//******************************************************************************************
	//����bit-mask��֧�ֶ�IOͬʱ����
	
	//��ĳһIO������Ϊ����ģʽ 2013-03-27 by zpyws
// 	#define _IOS_IN(port,pins)       	port##->DDR &= ~(pins)//set bits to input
// 	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//��ĳһIO������Ϊ���ģʽ 2013-03-27 by zpyws
// 	#define _IOS_OUT(port,pins)     	port##->DDR |= (pins)
// 	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//��ĳһ���������Ϊ����(���)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_PP(port,pins)     port##->CR1 |= (pins)
// 	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//��ĳһ���������Ϊ��©(���)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_OD(port,pins)     port##->CR1 &= ~(pins)
// 	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_FL(port,pins)     port##->CR1 &= ~(pins)
// 	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
// 	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//��ĳһ���������ߵ�ƽ  by zpyws
	#define _IOS_SET(port,pins)     	port##_DOUT |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//��ĳһ���������͵�ƽ  by zpyws
	#define _IOS_CLR(port,pins)     	port##_DOUT &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
	#define _IOS_FLP(port,pins)     	port##_DOUT ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_RD(port,pins)			( port##_PIN & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//�޸�ĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_MOD(port,pins,val)		port##_DOUT = (port##_DOUT & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//���ĳ��IO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_PUT(port,pins,val)		port##_DOUT = (port##_DOUT & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//��ȡĳ��IO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_GET(port,pins)			( port##_PIN & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//******ĳһ��˿ڲ�����************************************************************************************
	//���ĳһ��IO�ڵ����ŵ�ƽֵ by zpyws
	#define _PORT_PUT(port,val)			port##_DOUT = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//��ȡĳһ��IO�ڵ����ŵ�ƽֵ by zpyws
	#define _PORT_GET(port)				port##_PIN
	#define PORT_GET(port)				_PORT_GET(port)
#endif
//*****STM32F030*************************************************************************************************************************
#if defined(STM32F030)
	// STM32F0 IO�ڲ�����
	// 2014-07-29  by zpyws
	//For STM32
	#define 	PA		GPIOA
	#define 	PB		GPIOB
	#define 	PC		GPIOC
	#define 	PD		GPIOD
	#define 	PE		GPIOE
	#define 	PF		GPIOF
	
	//��ĳһIO������Ϊ����ģʽ  by zpyws
	#define _IO_IN(port,pin)     		BF_CLR(port##->MODER, 3UL<<((pin)<<1))						//GPIOx_MODER = 00
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//��ĳһIO������Ϊ���ģʽ  by zpyws
	#define _IO_OUT(port,pin)     		BF_MOD(port##->MODER, 3UL<<((pin)<<1), 1UL<<((pin)<<1))		//GPIOx_MODER = 01
	#define IO_OUT(port,pin)      		_IO_OUT(port,pin)
	
	//��ĳһIO������ΪAlternate function mode  by zpyws
	#define _IO_MODE_AF(port,pin)     	BF_MOD(port##->MODER, 3UL<<((pin)<<1), 2UL<<((pin)<<1))		//GPIOx_MODER = 10
	#define IO_MODE_AF(port,pin)      	_IO_MODE_AF(port,pin)
	
	//��ĳһIO������ΪAnalog mode  by zpyws
	#define _IO_ANALOG(port,pin)     	BF_SET(port##->MODER, 3UL<<((pin)<<1))						//GPIOx_MODER = 11
	#define IO_ANALOG(port,pin)      	_IO_ANALOG(port,pin)
	
	//��ĳһIO������ΪAlternate function mode  by zpyws
	#define _IO_AF_CFG(port,pin,function)	do{IO_MODE_AF(port,pin);BF_MOD( port->AFR[pin>>3], 15ul << ((pin&7ul)<<2), ((uint32)function) << ((pin&7ul)<<2) );}while(0)
	#define IO_AF_CFG(port,pin,function)    _IO_AF_CFG(port,pin,function)
	
	//����IO�������(STM32����)
	#define IO_SPD_LOW(port,pin)		BF_CLR(port##->OSPEEDR, 3UL<<((pin)<<1))						// I/O output speed		
	#define IO_SPD_MID(port,pin)		BF_MOD(port##->OSPEEDR, 3UL<<((pin)<<1), 1UL<<((pin)<<1))	// I/O output speed		
	#define IO_SPD_HIGH(port,pin)		BF_SET(port##->OSPEEDR, 3UL<<((pin)<<1))						// I/O output speed	
	
	//��ĳһ���������Ϊ����(���)ģʽ  by zpyws
	#define _IO_MODE_PP(port,pin)     	CBI(port##->OTYPER, pin)	
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//��ĳһ���������Ϊ��©(���)ģʽ  by zpyws
	#define _IO_MODE_OD(port,pin)     	SBI(port##->OTYPER, pin)
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)


	//��ĳһ���������Ϊ����(����)ģʽ  by zpyws
	#define _IO_MODE_FL(port,pin)     	BF_CLR(port##->PUPDR, 3UL<<((pin)<<1))					
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ  by zpyws
	#define _IO_MODE_PU(port,pin)     	BF_MOD(port##->PUPDR, 3UL<<((pin)<<1), 1UL<<((pin)<<1))
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ  by zpyws
	#define _IO_MODE_PD(port,pin)     	BF_MOD(port##->PUPDR, 3UL<<((pin)<<1), 2UL<<((pin)<<1))
	#define IO_MODE_PD(port,pin)      	_IO_MODE_PD(port,pin)
	
	//��ĳһ���������ߵ�ƽ  by zpyws
	#define _IO_SET(port,pin)		port##->BSRR = (1UL<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//��ĳһ���������͵�ƽ  by zpyws
	#define _IO_CLR(port,pin)     	port##->BRR = (1UL<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
 	#define _IO_TOG(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
	#define _IO_FLP(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IO_RD(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IO_GET(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
//******************************************************************************************
	//����bit-mask��֧�ֶ�IOͬʱ����
	
	//��ĳһIO������Ϊ����ģʽ 2013-03-27 by zpyws
	#define _IOS_IN(port,pins)       	GPIO_PinsInput(port, pins)//set bits to input
	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//��ĳһIO������Ϊ���ģʽ 2013-03-27 by zpyws
	#define _IOS_OUT(port,pins)     	GPIO_PinsOutput(port, pins)
	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//��ĳһ���������Ϊ����(���)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_PP(port,pins)     BF_CLR(port##->OTYPER, pins)
	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//��ĳһ���������Ϊ��©(���)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_OD(port,pins)     BF_SET(port##->OTYPER, pins)
	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_FL(port,pins)     BF_CLR(port##->PUPDR, )
// 	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
// 	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
// 	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//��ĳһ���������ߵ�ƽ  by zpyws
	#define _IOS_SET(port,pins)     	port##->ODR |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//��ĳһ���������͵�ƽ  by zpyws
	#define _IOS_CLR(port,pins)     	port##->ODR &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//ȡ�����ĳһ����ڵĵ�ƽ  by zpyws
	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_RD(port,pins)			( port##->IDR & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//�޸�ĳһIO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_MOD(port,pins,val)		BF_MOD(port##->ODR, pins, ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//���ĳ��IO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_PUT(port,pins,val)		BF_MOD(port##->ODR, pins, ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//��ȡĳ��IO�ڵ����ŵ�ƽֵ  by zpyws
	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//******ĳһ��˿ڲ�����************************************************************************************
	//���ĳһ��IO�ڵ����ŵ�ƽֵ by zpyws
	#define _PORT_PUT(port,val)			port##->ODR = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//��ȡĳһ��IO�ڵ����ŵ�ƽֵ by zpyws
	#define _PORT_GET(port)				port##->PIN
	#define PORT_GET(port)				_PORT_GET(port)
#endif
////*****STM32F103*************************************************************************************************************************
//#if defined(STM32F103)
//	//ͨ��GPIO�궨��by zpyws 2013-04-14
//	//For STM32
//	#define 	PA		GPIOA
//	#define 	PB		GPIOB
//	#define 	PC		GPIOC
//	#define 	PD		GPIOD
//	#define 	PE		GPIOE
//	#define 	PF		GPIOF
//	//������ֻ֧�ֵ�IO����
//	//by zpyws 2012-12-27
//	//2015-06-03  by zpyws
//	#define IO_IN(port,pin)			BF_CLR( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )		//2015-06-03  by zpyws

//	//2015-06-03  by zpyws
//	#define IO_OUT(port,pin)		BF_SET( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )						// I/O output speed	

////	#define IO_IN(port,pin)			GPIOPinDir(port, 1UL<<(pin), 0)//set bits to input
////	#define IO_OUT(port,pin)		GPIOPinDir(port, 1UL<<(pin), 1)//set bits to output
//	#define IO_SET(port,pin)		port##->BSRR = (1UL<<(pin))//IO����ߵ�ƽ(bits��Ϊ����ڵĻ�ֵ��ͬʱ���ƶ��IO���)BY ZPYWS 2011-08-30
//	#define IO_CLR(port,pin)		port##->BRR = (1UL<<(pin))//IO����͵�ƽ(bits��Ϊ����ڵĻ�ֵ��ͬʱ���ƶ��IO���) BY ZPYWS 2011-08-30
//	#define IO_TOG(port,pin)     	port##->ODR ^= (1UL<<(pin))//clear bits
//	#define IO_FLP(port,pin)     	port##->ODR ^= (1UL<<(pin))//clear bits
//	#define IO_RD(port,pin)      	((port##->IDR)&(1UL<<(pin)))//�����ŵ������ƽBy zpyws 2012-10-29

//	//����IO�������(STM32����)		//2015-06-03  by zpyws
//	#define IO_SPD_LOW(port,pin)		BF_MOD( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2), 2UL<<((pin>>3)<<2) )	// I/O output speed		
//	#define IO_SPD_MID(port,pin)		BF_MOD( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2), 1UL<<((pin>>3)<<2) )	// I/O output speed		
//	#define IO_SPD_HIGH(port,pin)		BF_SET( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )						// I/O output speed	

//	//��ĳһIO������ΪAlternate function mode  by zpyws
//	#define IO_MODE_AFIO(port,pin)     	SBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+3) )		

//	//����ΪGPIO���		2015-06-03  by zpyws
//	#define IO_MODE_GPIO(port,pin)     	CBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+3) )		

//	//IO������ģʽ���� 2013-04-13 by zpyws
//	#define IO_MODE_PU(port,pin)		do{GPIOPinMode(port,1UL<<(pin),2);port##->ODR |=(1UL<<(pin));}while(0)//��������
//	#define IO_MODE_PD(port,pin)      	do{GPIOPinMode(port,(1UL<<(pin),2);port##->ODR &= ~(1UL<<(pin));}while(0)//��������
//	#define IO_MODE_FL(port,pin)      	GPIOPinMode(port,(1UL<<(pin),1)//��������
//	#define IO_MODE_AN(port,pin)      	GPIOPinMode(port,(1UL<<(pin),0)//ģ������
//	
//	//IO�����ģʽ���� 2013-04-13 by zpyws
//	#define IO_MODE_PP(port,pin)     	CBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+2) )		
//	#define IO_MODE_OD(port,pin)     	SBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+2) )		
////	#define IO_MODE_PP(port,pin)			GPIOPinMode(port, 1UL<<(pin), 0)//����ʽ���
////	#define IO_MODE_OD(port,pin)			GPIOPinMode(port, 1UL<<(pin), 1)//��©���
//	
//	//����bit-mask��֧�ֶ�IOͬʱ����
//	#define IOS_IN(port,pins)       GPIOPinDir(port, pins, 0)//set bits to input
//	#define IOS_OUT(port,pins)      GPIOPinDir(port, pins, 1)//set bits to output
//	#define IOS_SET(port,bits)		port##->BSRR = (bits)//IO����ߵ�ƽ(bits��Ϊ����ڵĻ�ֵ��ͬʱ���ƶ��IO���)BY ZPYWS 2011-08-30
//	#define IOS_CLR(port,bits)		port##->BRR = (bits)//IO����͵�ƽ(bits��Ϊ����ڵĻ�ֵ��ͬʱ���ƶ��IO���) BY ZPYWS 2011-08-30
//	#define IOS_TOG(port,bits)     	port##->ODR ^= (bits)//clear bits
//	#define IOS_RD(port,bits)      	((port##->IDR)&(bits))//�����ŵ������ƽBy zpyws 2012-10-29
//	//IO������ģʽ���� 2013-04-13 by zpyws
//	#define IOS_MODE_PU(port,pins)      	do{GPIOPinMode(port,pins,2);port##->ODR |= (pins);}while(0)//��������
//	#define IOS_MODE_PD(port,pins)      	do{GPIOPinMode(port,pins,2);port##->ODR &= ~(pins);}while(0)//��������
//	#define IOS_MODE_FL(port,pins)      	GPIOPinMode(port,pins,1)//��������
//	#define IOS_MODE_AN(port,pins)      	GPIOPinMode(port,pins,0)//ģ������
//	//IO�����ģʽ���� 2013-04-13 by zpyws
//	#define IOS_MODE_PP(port,pins)			GPIOPinMode(port,pins,0)//����ʽ���
//	#define IOS_MODE_OD(port,pins)			GPIOPinMode(port,pins,1)//��©���
//	//ȡ�����ĳһ����ڵĵ�ƽ 2013-03-27 by zpyws
//	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
//	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
//	//�޸�ĳһIO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
//	#define _IOS_MOD(port,pins,val)		port##->ODR = (port##->ODR & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
//	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
//	//���ĳ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
//	#define _IOS_PUT(port,pins,val)		port##->ODR = (port##->ODR & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
//	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
//	//��ȡĳ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
//	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
//	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//#endif
//*****LPC17xx*************************************************************************************************************************
#if defined(LPC17xx)
	#define IO_IN(ddr,bits)       ddr->DIR &= ~(bits)//set bits to output
	#define IO_OUT(ddr,bits)      ddr->DIR |= (bits)//set bits to input

	#define IO_SET(port,bits)     port##->SET = (bits)//IO����ߵ�ƽBY ZPYWS 2011-08-30
	#define IO_CLR(port,bits)     port##->CLR = (bits)//IO����͵�ƽBY ZPYWS 2011-08-30
	#define IO_TOG(port,bits)     port##->PIN ^= (bits)//clear bits
	#define IO_RD(port,bits)      ((port##->PIN)&(bits))//�����ŵ������ƽBy zpyws 2012-10-29
#endif
//******************************************************************************************************************************
//For NRF51
#include "YOSDriverMacro.h"
//******************************************************************************************************************************
#endif
