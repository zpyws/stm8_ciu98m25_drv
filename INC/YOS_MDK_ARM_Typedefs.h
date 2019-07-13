#ifndef YOS_ARM_MDK_TYPEDEFS_H
#define YOS_ARM_MDK_TYPEDEFS_H
//2014-07-08  15:57 建立
//******************************************************************************************************************************
#ifdef __CC_ARM	//Always set to 1 for the ARM compiler, even when you specify the --thumb option.
	#define ARCH_ARM
	#define _BYTE_ORDER_		0//0->小端格式	1->大端格式
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
	#define __ALIGN(bytes)      __align(bytes)//字节对齐
	#define __INLINE            __inline//内联函数
	#define __ASM            	__asm   //asm keyword for ARM Compiler
	#define __PACKED			__packed//压缩存储
//	#define __RESET()			do{*((volatile uint32 *)0xE000ED0C) = 0x05fa0000|0x00000004;}while(0)  //Cortex-M3软件复位 2013-06-23 by zpyws
#endif
//*****Nuvoton M051*************************************************************************************************************************
#ifdef M051
	#define __RESET()			do{UnlockCPUReg();SYS->IPRSTC1 |= SYS_IPRSTC1_CHIP_RST;}while(0)  //M051软件复位 2014-07-11 by zpyws
#endif

#if defined(M051)
	// Nuvoton M051 IO口操作宏
	// 2014-07-09  by zpyws
	
	//将某一IO口设置为输入模式  by zpyws
	#define _IO_IN(port,pin)     		BF_CLR(port##->PMD, 3UL<<((pin)<<1))						//PxPMD = 00
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//将某一IO口设置为输出模式  by zpyws
	#define _IO_OUT(port,pin)     		BF_MOD(port->PMD, 3UL<<((pin)<<1), 1UL<<((pin)<<1))		//Px_PMD = 01
	#define IO_OUT(port,pin)      		_IO_OUT(port,pin)
	
	//将某一输出口设置为推挽(输出)模式  by zpyws
	#define _IO_MODE_PP(port,pin)     	BF_MOD(port##->PMD, 3UL<<((pin)<<1), 1UL<<((pin)<<1))	//Px_PMD = 01
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//将某一输出口设置为开漏(输出)模式  by zpyws
	#define _IO_MODE_OD(port,pin)     	BF_MOD(port##->PMD, 3UL<<((pin)<<1), 2UL<<((pin)<<1))	//Px_PMD = 10
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)
	
	//将某一输入口设置为浮空(输入)模式  by zpyws
	#define _IO_MODE_FL(port,pin)     	BF_CLR(port##->PMD, 3UL<<((pin)<<1))						//PxPMD = 00
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//将某一输入口设置为上拉(输入)模式  by zpyws
	#define _IO_MODE_PU(port,pin)     	do{IO_SET(port,pin);BF_SET(port##->PMD, 3UL<<((pin)<<1));}while(0)	//Px_PMD = 11
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//将某一输出口输出高电平  by zpyws
	#define _IO_SET(port,pin)     	port##->DOUT |= (1<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//将某一输出口输出低电平  by zpyws
	#define _IO_CLR(port,pin)     	port##->DOUT &= ~(1<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//取反输出某一输出口的电平  by zpyws
	#define _IO_TOG(port,pin)     	port##->DOUT ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IO_RD(port,pin)		( port##->PIN & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//取反输出某一输出口的电平  by zpyws
	#define _IO_FLP(port,pin)     	port##->DOUT ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IO_GET(port,pin)		( port##->PIN & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
//******************************************************************************************
	//不带bit-mask，支持多IO同时操作
	
	//将某一IO口设置为输入模式 2013-03-27 by zpyws
// 	#define _IOS_IN(port,pins)       	port##->DDR &= ~(pins)//set bits to input
// 	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//将某一IO口设置为输出模式 2013-03-27 by zpyws
// 	#define _IOS_OUT(port,pins)     	port##->DDR |= (pins)
// 	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//将某一输出口设置为推挽(输出)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_PP(port,pins)     port##->CR1 |= (pins)
// 	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//将某一输出口设置为开漏(输出)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_OD(port,pins)     port##->CR1 &= ~(pins)
// 	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//将某一输入口设置为浮空(输入)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_FL(port,pins)     port##->CR1 &= ~(pins)
// 	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//将某一输入口设置为上拉(输入)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
// 	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//将某一输出口输出高电平  by zpyws
	#define _IOS_SET(port,pins)     	port##_DOUT |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//将某一输出口输出低电平  by zpyws
	#define _IOS_CLR(port,pins)     	port##_DOUT &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//取反输出某一输出口的电平  by zpyws
	#define _IOS_FLP(port,pins)     	port##_DOUT ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IOS_RD(port,pins)			( port##_PIN & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//修改某一IO口的引脚电平值  by zpyws
	#define _IOS_MOD(port,pins,val)		port##_DOUT = (port##_DOUT & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//输出某几IO口的引脚电平值  by zpyws
	#define _IOS_PUT(port,pins,val)		port##_DOUT = (port##_DOUT & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//读取某几IO口的引脚电平值  by zpyws
	#define _IOS_GET(port,pins)			( port##_PIN & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//******某一组端口操作宏************************************************************************************
	//输出某一组IO口的引脚电平值 by zpyws
	#define _PORT_PUT(port,val)			port##_DOUT = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//读取某一组IO口的引脚电平值 by zpyws
	#define _PORT_GET(port)				port##_PIN
	#define PORT_GET(port)				_PORT_GET(port)
#endif
//*****STM32F030*************************************************************************************************************************
#if defined(STM32F030)
	// STM32F0 IO口操作宏
	// 2014-07-29  by zpyws
	//For STM32
	#define 	PA		GPIOA
	#define 	PB		GPIOB
	#define 	PC		GPIOC
	#define 	PD		GPIOD
	#define 	PE		GPIOE
	#define 	PF		GPIOF
	
	//将某一IO口设置为输入模式  by zpyws
	#define _IO_IN(port,pin)     		BF_CLR(port##->MODER, 3UL<<((pin)<<1))						//GPIOx_MODER = 00
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//将某一IO口设置为输出模式  by zpyws
	#define _IO_OUT(port,pin)     		BF_MOD(port##->MODER, 3UL<<((pin)<<1), 1UL<<((pin)<<1))		//GPIOx_MODER = 01
	#define IO_OUT(port,pin)      		_IO_OUT(port,pin)
	
	//将某一IO口设置为Alternate function mode  by zpyws
	#define _IO_MODE_AF(port,pin)     	BF_MOD(port##->MODER, 3UL<<((pin)<<1), 2UL<<((pin)<<1))		//GPIOx_MODER = 10
	#define IO_MODE_AF(port,pin)      	_IO_MODE_AF(port,pin)
	
	//将某一IO口设置为Analog mode  by zpyws
	#define _IO_ANALOG(port,pin)     	BF_SET(port##->MODER, 3UL<<((pin)<<1))						//GPIOx_MODER = 11
	#define IO_ANALOG(port,pin)      	_IO_ANALOG(port,pin)
	
	//将某一IO口设置为Alternate function mode  by zpyws
	#define _IO_AF_CFG(port,pin,function)	do{IO_MODE_AF(port,pin);BF_MOD( port->AFR[pin>>3], 15ul << ((pin&7ul)<<2), ((uint32)function) << ((pin&7ul)<<2) );}while(0)
	#define IO_AF_CFG(port,pin,function)    _IO_AF_CFG(port,pin,function)
	
	//设置IO输出速率(STM32特有)
	#define IO_SPD_LOW(port,pin)		BF_CLR(port##->OSPEEDR, 3UL<<((pin)<<1))						// I/O output speed		
	#define IO_SPD_MID(port,pin)		BF_MOD(port##->OSPEEDR, 3UL<<((pin)<<1), 1UL<<((pin)<<1))	// I/O output speed		
	#define IO_SPD_HIGH(port,pin)		BF_SET(port##->OSPEEDR, 3UL<<((pin)<<1))						// I/O output speed	
	
	//将某一输出口设置为推挽(输出)模式  by zpyws
	#define _IO_MODE_PP(port,pin)     	CBI(port##->OTYPER, pin)	
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//将某一输出口设置为开漏(输出)模式  by zpyws
	#define _IO_MODE_OD(port,pin)     	SBI(port##->OTYPER, pin)
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)


	//将某一输入口设置为浮空(输入)模式  by zpyws
	#define _IO_MODE_FL(port,pin)     	BF_CLR(port##->PUPDR, 3UL<<((pin)<<1))					
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//将某一输入口设置为上拉(输入)模式  by zpyws
	#define _IO_MODE_PU(port,pin)     	BF_MOD(port##->PUPDR, 3UL<<((pin)<<1), 1UL<<((pin)<<1))
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//将某一输入口设置为下拉(输入)模式  by zpyws
	#define _IO_MODE_PD(port,pin)     	BF_MOD(port##->PUPDR, 3UL<<((pin)<<1), 2UL<<((pin)<<1))
	#define IO_MODE_PD(port,pin)      	_IO_MODE_PD(port,pin)
	
	//将某一输出口输出高电平  by zpyws
	#define _IO_SET(port,pin)		port##->BSRR = (1UL<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//将某一输出口输出低电平  by zpyws
	#define _IO_CLR(port,pin)     	port##->BRR = (1UL<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//取反输出某一输出口的电平  by zpyws
 	#define _IO_TOG(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//取反输出某一输出口的电平  by zpyws
	#define _IO_FLP(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IO_RD(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IO_GET(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
//******************************************************************************************
	//不带bit-mask，支持多IO同时操作
	
	//将某一IO口设置为输入模式 2013-03-27 by zpyws
	#define _IOS_IN(port,pins)       	GPIO_PinsInput(port, pins)//set bits to input
	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//将某一IO口设置为输出模式 2013-03-27 by zpyws
	#define _IOS_OUT(port,pins)     	GPIO_PinsOutput(port, pins)
	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//将某一输出口设置为推挽(输出)模式 2013-03-27 by zpyws
	#define _IOS_MODE_PP(port,pins)     BF_CLR(port##->OTYPER, pins)
	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//将某一输出口设置为开漏(输出)模式 2013-03-27 by zpyws
	#define _IOS_MODE_OD(port,pins)     BF_SET(port##->OTYPER, pins)
	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//将某一输入口设置为浮空(输入)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_FL(port,pins)     BF_CLR(port##->PUPDR, )
// 	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//将某一输入口设置为上拉(输入)模式 2013-03-27 by zpyws
// 	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
// 	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//将某一输出口输出高电平  by zpyws
	#define _IOS_SET(port,pins)     	port##->ODR |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//将某一输出口输出低电平  by zpyws
	#define _IOS_CLR(port,pins)     	port##->ODR &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//取反输出某一输出口的电平  by zpyws
	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//读取某一IO口的引脚电平值  by zpyws
	#define _IOS_RD(port,pins)			( port##->IDR & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//修改某一IO口的引脚电平值  by zpyws
	#define _IOS_MOD(port,pins,val)		BF_MOD(port##->ODR, pins, ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//输出某几IO口的引脚电平值  by zpyws
	#define _IOS_PUT(port,pins,val)		BF_MOD(port##->ODR, pins, ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//读取某几IO口的引脚电平值  by zpyws
	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//******某一组端口操作宏************************************************************************************
	//输出某一组IO口的引脚电平值 by zpyws
	#define _PORT_PUT(port,val)			port##->ODR = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//读取某一组IO口的引脚电平值 by zpyws
	#define _PORT_GET(port)				port##->PIN
	#define PORT_GET(port)				_PORT_GET(port)
#endif
////*****STM32F103*************************************************************************************************************************
//#if defined(STM32F103)
//	//通用GPIO宏定义by zpyws 2013-04-14
//	//For STM32
//	#define 	PA		GPIOA
//	#define 	PB		GPIOB
//	#define 	PC		GPIOC
//	#define 	PD		GPIOD
//	#define 	PE		GPIOE
//	#define 	PF		GPIOF
//	//本宏组只支持单IO操作
//	//by zpyws 2012-12-27
//	//2015-06-03  by zpyws
//	#define IO_IN(port,pin)			BF_CLR( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )		//2015-06-03  by zpyws

//	//2015-06-03  by zpyws
//	#define IO_OUT(port,pin)		BF_SET( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )						// I/O output speed	

////	#define IO_IN(port,pin)			GPIOPinDir(port, 1UL<<(pin), 0)//set bits to input
////	#define IO_OUT(port,pin)		GPIOPinDir(port, 1UL<<(pin), 1)//set bits to output
//	#define IO_SET(port,pin)		port##->BSRR = (1UL<<(pin))//IO输出高电平(bits可为多个口的或值以同时控制多个IO输出)BY ZPYWS 2011-08-30
//	#define IO_CLR(port,pin)		port##->BRR = (1UL<<(pin))//IO输出低电平(bits可为多个口的或值以同时控制多个IO输出) BY ZPYWS 2011-08-30
//	#define IO_TOG(port,pin)     	port##->ODR ^= (1UL<<(pin))//clear bits
//	#define IO_FLP(port,pin)     	port##->ODR ^= (1UL<<(pin))//clear bits
//	#define IO_RD(port,pin)      	((port##->IDR)&(1UL<<(pin)))//读引脚的输入电平By zpyws 2012-10-29

//	//设置IO输出速率(STM32特有)		//2015-06-03  by zpyws
//	#define IO_SPD_LOW(port,pin)		BF_MOD( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2), 2UL<<((pin>>3)<<2) )	// I/O output speed		
//	#define IO_SPD_MID(port,pin)		BF_MOD( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2), 1UL<<((pin>>3)<<2) )	// I/O output speed		
//	#define IO_SPD_HIGH(port,pin)		BF_SET( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), 3UL<<((pin&7)<<2) )						// I/O output speed	

//	//将某一IO口设置为Alternate function mode  by zpyws
//	#define IO_MODE_AFIO(port,pin)     	SBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+3) )		

//	//设置为GPIO输出		2015-06-03  by zpyws
//	#define IO_MODE_GPIO(port,pin)     	CBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+3) )		

//	//IO口输入模式控制 2013-04-13 by zpyws
//	#define IO_MODE_PU(port,pin)		do{GPIOPinMode(port,1UL<<(pin),2);port##->ODR |=(1UL<<(pin));}while(0)//上拉输入
//	#define IO_MODE_PD(port,pin)      	do{GPIOPinMode(port,(1UL<<(pin),2);port##->ODR &= ~(1UL<<(pin));}while(0)//下拉输入
//	#define IO_MODE_FL(port,pin)      	GPIOPinMode(port,(1UL<<(pin),1)//浮空输入
//	#define IO_MODE_AN(port,pin)      	GPIOPinMode(port,(1UL<<(pin),0)//模拟输入
//	
//	//IO口输出模式控制 2013-04-13 by zpyws
//	#define IO_MODE_PP(port,pin)     	CBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+2) )		
//	#define IO_MODE_OD(port,pin)     	SBI( *((volatile uint32 *)((uint32)(&port##->CRL) + ((pin>>3)<<2))), (((pin&7)<<2)+2) )		
////	#define IO_MODE_PP(port,pin)			GPIOPinMode(port, 1UL<<(pin), 0)//推挽式输出
////	#define IO_MODE_OD(port,pin)			GPIOPinMode(port, 1UL<<(pin), 1)//开漏输出
//	
//	//不带bit-mask，支持多IO同时操作
//	#define IOS_IN(port,pins)       GPIOPinDir(port, pins, 0)//set bits to input
//	#define IOS_OUT(port,pins)      GPIOPinDir(port, pins, 1)//set bits to output
//	#define IOS_SET(port,bits)		port##->BSRR = (bits)//IO输出高电平(bits可为多个口的或值以同时控制多个IO输出)BY ZPYWS 2011-08-30
//	#define IOS_CLR(port,bits)		port##->BRR = (bits)//IO输出低电平(bits可为多个口的或值以同时控制多个IO输出) BY ZPYWS 2011-08-30
//	#define IOS_TOG(port,bits)     	port##->ODR ^= (bits)//clear bits
//	#define IOS_RD(port,bits)      	((port##->IDR)&(bits))//读引脚的输入电平By zpyws 2012-10-29
//	//IO口输入模式控制 2013-04-13 by zpyws
//	#define IOS_MODE_PU(port,pins)      	do{GPIOPinMode(port,pins,2);port##->ODR |= (pins);}while(0)//上拉输入
//	#define IOS_MODE_PD(port,pins)      	do{GPIOPinMode(port,pins,2);port##->ODR &= ~(pins);}while(0)//下拉输入
//	#define IOS_MODE_FL(port,pins)      	GPIOPinMode(port,pins,1)//浮空输入
//	#define IOS_MODE_AN(port,pins)      	GPIOPinMode(port,pins,0)//模拟输入
//	//IO口输出模式控制 2013-04-13 by zpyws
//	#define IOS_MODE_PP(port,pins)			GPIOPinMode(port,pins,0)//推挽式输出
//	#define IOS_MODE_OD(port,pins)			GPIOPinMode(port,pins,1)//开漏输出
//	//取反输出某一输出口的电平 2013-03-27 by zpyws
//	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
//	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
//	//修改某一IO口的引脚电平值 2013-03-27 by zpyws
//	#define _IOS_MOD(port,pins,val)		port##->ODR = (port##->ODR & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
//	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
//	//输出某几IO口的引脚电平值 2013-03-27 by zpyws
//	#define _IOS_PUT(port,pins,val)		port##->ODR = (port##->ODR & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
//	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
//	//读取某几IO口的引脚电平值 2013-03-27 by zpyws
//	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
//	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
//#endif
//*****LPC17xx*************************************************************************************************************************
#if defined(LPC17xx)
	#define IO_IN(ddr,bits)       ddr->DIR &= ~(bits)//set bits to output
	#define IO_OUT(ddr,bits)      ddr->DIR |= (bits)//set bits to input

	#define IO_SET(port,bits)     port##->SET = (bits)//IO输出高电平BY ZPYWS 2011-08-30
	#define IO_CLR(port,bits)     port##->CLR = (bits)//IO输出低电平BY ZPYWS 2011-08-30
	#define IO_TOG(port,bits)     port##->PIN ^= (bits)//clear bits
	#define IO_RD(port,bits)      ((port##->PIN)&(bits))//读引脚的输入电平By zpyws 2012-10-29
#endif
//******************************************************************************************************************************
//For NRF51
#include "YOSDriverMacro.h"
//******************************************************************************************************************************
#endif
