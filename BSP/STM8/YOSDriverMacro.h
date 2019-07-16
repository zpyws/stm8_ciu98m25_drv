#ifndef YOS_IAR_STM8_TYPEDEFS_H
#define YOS_IAR_STM8_TYPEDEFS_H
//2014-07-08  16:56 ����
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	#define ARCH_STM8
	#define _BYTE_ORDER_		1//0->С�˸�ʽ	1->��˸�ʽ
	#define _BIG_ENDIAN
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	typedef unsigned char  BOOL;
	typedef unsigned char  bool;
	typedef unsigned char  boolean;
	// typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
	
	typedef unsigned char  uint8;                                   /* �������ֲ���޷���8λ�����ؼ���            */
	typedef signed char    sint8;                                    /* �������ֲ���з���8λ�����ؼ���            */
	typedef signed char    int8;                                    /* �������ֲ���з���8λ�����ؼ���            */
	
	typedef unsigned short uint16;                                  /* �������ֲ���޷���16λ�����ؼ���           */
	typedef signed short   int16;                                   /* �������ֲ���з���16λ�����ؼ���           */
	typedef signed short   sint16;                                   /* �������ֲ���з���16λ�����ؼ���           */
	
	typedef unsigned long  uint32;                                  /* �������ֲ���޷���32λ�����ؼ���           */
	typedef signed   long  int32;                                   /* �������ֲ���з���32λ�����ؼ���           */
	typedef signed   long  sint32;                                   /* �������ֲ���з���32λ�����ؼ���           */

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
	//#define __ALIGN(bytes)      __align(bytes)//�ֽڶ���
	//#define __INLINE            __inline//��������
	#define __PACKED			//ѹ���洢
	#define _RESET()         WWDG->CR = 0x80//��λ2013-02-22 by zpyws
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
	
	//��ĳһIO������Ϊ����ģʽ 2012-12-25 by zpyws
	#define _IO_IN(port,pin)     		port##->DDR &= ~(1<<(pin))
	#define IO_IN(port,pin)      		_IO_IN(port,pin)
	
	//��ĳһIO������Ϊ���ģʽ 2012-12-25 by zpyws
	#define _IO_OUT(port,pin)     	port##->DDR |= (1<<(pin))
	#define IO_OUT(port,pin)      	_IO_OUT(port,pin)
	
	//��ĳһ���������Ϊ����(���)ģʽ 2012-12-25 by zpyws
	#define _IO_MODE_PP(port,pin)     	port##->CR1 |= (1<<(pin))
	#define IO_MODE_PP(port,pin)      	_IO_MODE_PP(port,pin)
	
	//��ĳһ���������Ϊ��©(���)ģʽ 2012-12-25 by zpyws
	#define _IO_MODE_OD(port,pin)     	port##->CR1 &= ~(1<<(pin))
	#define IO_MODE_OD(port,pin)      	_IO_MODE_OD(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2012-12-25 by zpyws
	#define _IO_MODE_FL(port,pin)     	port##->CR1 &= ~(1<<(pin))
	#define IO_MODE_FL(port,pin)      	_IO_MODE_FL(port,pin)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2012-12-25 by zpyws
	#define _IO_MODE_PU(port,pin)     	port##->CR1 |= (1<<(pin))
	#define IO_MODE_PU(port,pin)      	_IO_MODE_PU(port,pin)
	
	//��ĳһ����������ⲿ�ж������ 2012-12-25 by zpyws
	#define _IO_INT_EN(port,pin)        port##->CR2 |= (1<<(pin))
	#define IO_INT_EN(port,pin)         _IO_INT_EN(port,pin)
	
	
	//��ĳһ����ڽ����ⲿ�ж������ 2012-12-25 by zpyws
	#define _IO_INT_DIS(port,pin)       port##_CR2 &= ~(1<<(pin))
	#define IO_INT_DIS(port,pin)        _IO_INT_DIS(port,pin)

	//��ĳһ���������ߵ�ƽ 2012-12-25 by zpyws
	#define _IO_SET(port,pin)     	port##->ODR |= (1<<(pin))
	#define IO_SET(port,pin)      	_IO_SET(port,pin)
	
	//��ĳһ���������͵�ƽ 2012-12-25 by zpyws
	#define _IO_CLR(port,pin)     	port##->ODR &= ~(1<<(pin))
	#define IO_CLR(port,pin)      	_IO_CLR(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ 2012-12-25 by zpyws
	#define _IO_TOG(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_TOG(port,pin)      	_IO_TOG(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ 2012-12-25 by zpyws
	#define _IO_RD(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_RD(port,pin)			_IO_RD(port,pin)
	
	//ȡ�����ĳһ����ڵĵ�ƽ 2012-12-25 by zpyws
	#define _IO_FLP(port,pin)     	port##->ODR ^= (1<<(pin))
	#define IO_FLP(port,pin)      	_IO_FLP(port,pin)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ 2012-12-25 by zpyws
	#define _IO_GET(port,pin)		( port##->IDR & (1<<(pin)) )
	#define IO_GET(port,pin)		_IO_GET(port,pin)
#endif
//******************************************************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	//����bit-mask��֧�ֶ�IOͬʱ����
	
	//��ĳһIO������Ϊ����ģʽ 2013-03-27 by zpyws
	#define _IOS_IN(port,pins)       	port##->DDR &= ~(pins)//set bits to input
	#define IOS_IN(port,pins)      		_IOS_IN(port,pins)
	
	//��ĳһIO������Ϊ���ģʽ 2013-03-27 by zpyws
	#define _IOS_OUT(port,pins)     	port##->DDR |= (pins)
	#define IOS_OUT(port,pins)      	_IOS_OUT(port,pins)
	
	//��ĳһ���������Ϊ����(���)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_PP(port,pins)     port##->CR1 |= (pins)
	#define IOS_MODE_PP(port,pins)      _IOS_MODE_PP(port,pins)
	
	//��ĳһ���������Ϊ��©(���)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_OD(port,pins)     port##->CR1 &= ~(pins)
	#define IOS_MODE_OD(port,pins)      _IOS_MODE_OD(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_FL(port,pins)     port##->CR1 &= ~(pins)
	#define IOS_MODE_FL(port,pins)      _IOS_MODE_FL(port,pins)
	
	//��ĳһ���������Ϊ����(����)ģʽ 2013-03-27 by zpyws
	#define _IOS_MODE_PU(port,pins)    	port##->CR1 |= (pins)
	#define IOS_MODE_PU(port,pins)      _IOS_MODE_PU(port,pins)
	
	//��ĳһ���������ߵ�ƽ 2013-03-27 by zpyws
	#define _IOS_SET(port,pins)     	port##->ODR |= (pins)
	#define IOS_SET(port,pins)      	_IOS_SET(port,pins)
	
	//��ĳһ���������͵�ƽ 2013-03-27 by zpyws
	#define _IOS_CLR(port,pins)     	port##->ODR &= ~(pins)
	#define IOS_CLR(port,pins)      	_IOS_CLR(port,pins)
	
	//ȡ�����ĳһ����ڵĵ�ƽ 2013-03-27 by zpyws
	#define _IOS_FLP(port,pins)     	port##->ODR ^= (pins)
	#define IOS_FLP(port,pins)      	_IOS_FLP(port,pins)
	
	//��ȡĳһIO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _IOS_RD(port,pins)			( port##->IDR & (pins) )
	#define IOS_RD(port,pins)			_IOS_RD(port,pins)
	
	//�޸�ĳһIO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _IOS_MOD(port,pins,val)		port##->ODR = (port##_ODR & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_MOD(port,pins,val)		_IOS_MOD(port,pins,val)
	
	//���ĳ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _IOS_PUT(port,pins,val)		port##->ODR = (port##_ODR & ~(pins)) | ((pins)&(val))//λ���޸� by zpyws 2013-03-05
	#define IOS_PUT(port,pins,val)		_IOS_PUT(port,pins,val)
	
	//��ȡĳ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _IOS_GET(port,pins)			( port##->IDR & (pins) )
	#define IOS_GET(port,pins)			_IOS_GET(port,pins)
#endif
//******ĳһ��˿ڲ�����************************************************************************************
#ifdef __ICCSTM8__//An integer that is set to  1  when the code is compiled with the IAR C/C++ Compiler for STM8
	//���ĳһ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _PORT_PUT(port,val)			port##->ODR = val
	#define PORT_PUT(port,val)			_PORT_PUT(port,val)
	
	//��ȡĳһ��IO�ڵ����ŵ�ƽֵ 2013-03-27 by zpyws
	#define _PORT_GET(port)				port##->IDR
	#define PORT_GET(port)				_PORT_GET(port)
#endif
//******************************************************************************************************************************
#endif
