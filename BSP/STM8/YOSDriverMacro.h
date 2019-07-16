#ifndef YOS_IAR_STM8_TYPEDEFS_H
#define YOS_IAR_STM8_TYPEDEFS_H
//2014-07-08  16:56 建立
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	#define ARCH_STM8
	#define _BYTE_ORDER_		1//0->小端格式	1->大端格式
	#define _BIG_ENDIAN
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	typedef unsigned char  BOOL;
	typedef unsigned char  bool;
	typedef unsigned char  boolean;
	// typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
	
	typedef unsigned char  uint8;                                   /* 定义可移植的无符号8位整数关键字            */
	typedef signed char    sint8;                                    /* 定义可移植的有符号8位整数关键字            */
	typedef signed char    int8;                                    /* 定义可移植的有符号8位整数关键字            */
	
	typedef unsigned short uint16;                                  /* 定义可移植的无符号16位整数关键字           */
	typedef signed short   int16;                                   /* 定义可移植的有符号16位整数关键字           */
	typedef signed short   sint16;                                   /* 定义可移植的有符号16位整数关键字           */
	
	typedef unsigned long  uint32;                                  /* 定义可移植的无符号32位整数关键字           */
	typedef signed   long  int32;                                   /* 定义可移植的有符号32位整数关键字           */
	typedef signed   long  sint32;                                   /* 定义可移植的有符号32位整数关键字           */

    typedef float           fl32;

	typedef uint16 			ysize_t;//2013-03-7 by zpyws
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//bAn integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	typedef uint16 			size_t;//2013-03-7 by zpyws
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	#define ROM                 const
	#define __TASK				__task         		
	//#define ISR(IntHandler)     void IntHandler(void)//2012-08-15 by zpyws
	//#define __ALIGN(bytes)      __align(bytes)//字节对齐
	//#define __INLINE            __inline//内联函数
	#define __PACKED			//压缩存储
	#define _RESET()         WWDG->CR = 0x80//复位2013-02-22 by zpyws
//==================================================================================================
	#ifndef SEI
		#define SEI()                asm("rim")
	#endif
	
	#ifndef CLI
		#define CLI()                asm("sim")
	#endif
	
	#ifndef NOP
		#define NOP()                asm("nop")
	#endif
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	//port-related macros for stm8s
	//DEFAULT: OPEN DRAIN OUTPUT
	//set Px_CR1 and clear Px_CR2 to turn to push_pull output
	
	//将某一IO口设置为输入模式 2012-12-25 by zpyws
	#define _IO_IN(port,pin)     		port##->DDR &= ~(1<<(pin))
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//将某一IO口设置为输出模式 2012-12-25 by zpyws
	#define _IO_OUT(port,pin)     	port##->DDR |= (1<<(pin))
	#define IO_OUT(port,pin)      	_IO_OUT(port,pin)
	
	//将某一输出口设置为推挽(输出)模式 2012-12-25 by zpyws
	#define _IO_MODE_PP(port,pin)     	port##->CR1 |= (1<<(pin))
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//将某一输出口设置为开漏(输出)模式 2012-12-25 by zpyws
	#define _IO_MODE_OD(port,pin)     	port##->CR1 &= ~(1<<(pin))
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)
	
	//将某一输入口设置为浮空(输入)模式 2012-12-25 by zpyws
	#define _IO_MODE_FL(port,pin)     	port##->CR1 &= ~(1<<(pin))
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//将某一输入口设置为上拉(输入)模式 2012-12-25 by zpyws
	#define _IO_MODE_PU(port,pin)     	port##->CR1 |= (1<<(pin))
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//将某一输入口设置外部中断输入脚 2012-12-25 by zpyws
	#define _IO_INT_EN(port,pin)        port##->CR2 |= (1<<(pin))
	#define IO_INT_EN(port,pin)         _IO_INT_EN(port,pin)
	
	
	//将某一输入口禁用外部中断输入脚 2012-12-25 by zpyws
	#define _IO_INT_DIS(port,pin)       port##_CR2 &= ~(1<<(pin))
	#define IO_INT_DIS(port,pin)        _IO_INT_DIS(port,pin)

	//将某一输出口输出高电平 2012-12-25 by zpyws
	#define _IO_SET(port,pin)     	port##->ODR |= (1<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//将某一输出口输出低电平 2012-12-25 by zpyws
	#define _IO_CLR(port,pin)     	port##->ODR &= ~(1<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//取反输出某一输出口的电平 2012-12-25 by zpyws
	#define _IO_TOG(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//读取某一IO口的引脚电平值 2012-12-25 by zpyws
	#define _IO_RD(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//取反输出某一输出口的电平 2012-12-25 by zpyws
	#define _IO_FLP(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//读取某一IO口的引脚电平值 2012-12-25 by zpyws
	#define _IO_GET(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	//不带bit-mask，支持多IO同时操作
	
	//将某一IO口设置为输入模式 2013-03-27 by zpyws
	#define _IOS_IN(port,pins)       	port##->DDR &= ~(pins)//set bits to input
	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//将某一IO口设置为输出模式 2013-03-27 by zpyws
	#define _IOS_OUT(port,pins)     	port##->DDR |= (pins)
	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//将某一输出口设置为推挽(输出)模式 2013-03-27 by zpyws
	#define _IOS_MODE_PP(port,pins)     port##->CR1 |= (pins)
	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//将某一输出口设置为开漏(输出)模式 2013-03-27 by zpyws
	#define _IOS_MODE_OD(port,pins)     port##->CR1 &= ~(pins)
	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//将某一输入口设置为浮空(输入)模式 2013-03-27 by zpyws
	#define _IOS_MODE_FL(port,pins)     port##->CR1 &= ~(pins)
	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//将某一输入口设置为上拉(输入)模式 2013-03-27 by zpyws
	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//将某一输出口输出高电平 2013-03-27 by zpyws
	#define _IOS_SET(port,pins)     	port##->ODR |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//将某一输出口输出低电平 2013-03-27 by zpyws
	#define _IOS_CLR(port,pins)     	port##->ODR &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//取反输出某一输出口的电平 2013-03-27 by zpyws
	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//读取某一IO口的引脚电平值 2013-03-27 by zpyws
	#define _IOS_RD(port,pins)			( port##->IDR & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//修改某一IO口的引脚电平值 2013-03-27 by zpyws
	#define _IOS_MOD(port,pins,val)		port##->ODR = (port##_ODR & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//输出某几IO口的引脚电平值 2013-03-27 by zpyws
	#define _IOS_PUT(port,pins,val)		port##->ODR = (port##_ODR & ~(pins)) | ((pins)&(val))//位域修改 by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//读取某几IO口的引脚电平值 2013-03-27 by zpyws
	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
#endif
//******某一组端口操作宏************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	//输出某一组IO口的引脚电平值 2013-03-27 by zpyws
	#define _PORT_PUT(port,val)			port##->ODR = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//读取某一组IO口的引脚电平值 2013-03-27 by zpyws
	#define _PORT_GET(port)				port##->IDR
	#define PORT_GET(port)				_PORT_GET(port)
#endif
//******************************************************************************************************************************
#endif
