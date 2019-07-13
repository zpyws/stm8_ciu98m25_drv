#ifndef __YOS_TYPEDEFS_H__
#define __YOS_TYPEDEFS_H__

//#include <intrinsics.h>
#include "YOS_MDK_ARM_Typedefs.h"
/****************非移植部分(正常情况不必改动)***********************************************
********************2013-08-22  by zpyws***************************************************
**************************杨文森***********************************************************
******************************************************************************************/
//******CPU大小端存储格式定义************************************************************************************************************************
//2013-08-22  by zpyws
#if !defined(_BYTE_ORDER_)
//#define _BYTE_ORDER_		0//0->小端格式	1->大端格式
	#error "Unknown CPU Byte Order! by zpyws"
#endif
//******************************************************************************************************************************
//from millwood0
#define NOP2()                                {NOP(); NOP();}
#define NOP4()                                {NOP2(); NOP2();}
#define NOP8()                                {NOP4(); NOP4();}
#define NOP16()                               {NOP8(); NOP8();}
//==================================================================================================
//from millwood0
//simple multiples
#define x1(val)                                (val)                                                                //multiply val by 1
#define x2(val)                                (((val) << 1))                                                //multiply val by 2
#define x3(val)                                (x2(val) + (val))                                        //multiply val by 3
#define x4(val)                                (((val) << 2))                                                //multiply val by 4
#define x5(val)                                (x4(val) + (val))                                        //multiply val by 5
#define x6(val)                                (x4(val) + x2(val))                                        //multiply val by 6
#define x7(val)                                (x6(val) + (val))                                        //multiply val by 7
#define x8(val)                                ((val) << 3)                                                //multiply val by 8
#define x9(val)                                (x8(val) + (val))                                        //multiply val by 9

//multiples of 10s
#define x10(val)                        (x8(val) + x2(val))                                        //multiply val by 10
#define x100(val)                        (x10(x10(val)))                                                //multiply val by 100
#define x1000(val)                        (x100(x10(val)))                                        //multiply val by 1000
#define x1k(val)                        x1000(val)                                                        //multiply val by 1000
#define x10k(val)                        (x100(x100(val)))                                        //multiply val by 10000

#define x20(val)                        (x2(x10(val)))
#define x30(val)                        (x3(x10(val)))
#define x40(val)                        (x4(x10(val)))
#define x50(val)                        (x5(x10(val)))
#define x60(val)                        (x6(x10(val)))
#define x70(val)                        (x7(x10(val)))
#define x80(val)                        (x8(x10(val)))
#define x90(val)                        (x9(x10(val)))

//multiples of 100s
#define x200(val)                        (x2(x100(val)))
#define x300(val)                        (x3(x100(val)))
#define x400(val)                        (x4(x100(val)))
#define x500(val)                        (x5(x100(val)))
#define x600(val)                        (x6(x100(val)))
#define x700(val)                        (x7(x100(val)))
#define x800(val)                        (x8(x100(val)))
#define x900(val)                        (x9(x100(val)))

//custom definitions
#define x34(val)                        (x30(val) + x4(val))                                //multiply val by 34
#define x97(val)                        (x90(val) + x7(val))                                //multiply val by 97x
//******************************************************************************************************************************
//标准库函数转换宏 2013-06-07 by zpyws
#define MEMCMP(a,b,c)		memcmp(a,b,c)
#define STRCMP(a,b)			strcmp(a,b)
#define MEMCPY(a,b,c)		memcpy(a,b,c)
#define STRCPY(a,b)			strcpy(a,b)
#define STRNCPY(a,b,c)		strncpy(a,b,c)
#define STRSTR(a,b)			strstr(a,b)
#define	STRLEN(a)			strlen(a)
#define STRCHR(a,b)			strchr(a,b)
#define STRCAT(a,b)			strcat(a,b)
//******************************************************************************************************************************
//******************************************************************************************************************************
#if _BYTE_ORDER_==0	//如果CPU是小端的 2013-08-22 by zpyws
typedef __PACKED union
{
    uint16 Val;
    __PACKED uint8 B[2];
    __PACKED struct
    {
        uint8 LB;
        uint8 HB;
    } byte;
    __PACKED struct
    {
        uint8 b0:1;
        uint8 b1:1;
        uint8 b2:1;
        uint8 b3:1;
        uint8 b4:1;
        uint8 b5:1;
        uint8 b6:1;
        uint8 b7:1;
        uint8 b8:1;
        uint8 b9:1;
        uint8 b10:1;
        uint8 b11:1;
        uint8 b12:1;
        uint8 b13:1;
        uint8 b14:1;
        uint8 b15:1;
    } bits;
} UN16_t;//union 16  2013-06-08 by zpyws

typedef __PACKED union
{
    uint32 Val;
    __PACKED uint16 W[2];//uint16 word value
    __PACKED uint8 B[4];//uint8 byte value
    __PACKED struct
    {
        uint16 LW;
        uint16 HW;
    } word;
    __PACKED struct
    {
        uint8 LB;
        uint8 HB;
        uint8 UB;
        uint8 MB;
    } byte;
    __PACKED struct
    {
        UN16_t low;
        UN16_t high;
    }wordUnion;
    __PACKED struct
    {
        uint8 b0:1;
        uint8 b1:1;
        uint8 b2:1;
        uint8 b3:1;
        uint8 b4:1;
        uint8 b5:1;
        uint8 b6:1;
        uint8 b7:1;
        uint8 b8:1;
        uint8 b9:1;
        uint8 b10:1;
        uint8 b11:1;
        uint8 b12:1;
        uint8 b13:1;
        uint8 b14:1;
        uint8 b15:1;
        uint8 b16:1;
        uint8 b17:1;
        uint8 b18:1;
        uint8 b19:1;
        uint8 b20:1;
        uint8 b21:1;
        uint8 b22:1;
        uint8 b23:1;
        uint8 b24:1;
        uint8 b25:1;
        uint8 b26:1;
        uint8 b27:1;
        uint8 b28:1;
        uint8 b29:1;
        uint8 b30:1;
        uint8 b31:1;
    } bits;
} UN32_t;//union 32  2013-06-07 by zpyws
//******************************************************************************************************************************
#else	//如果CPU是大端的 2013-08-22 by zpyws
typedef __PACKED union
{
    uint16 Val;
    __PACKED uint8 B[2];
    __PACKED struct//对于STM8，为大端格式，高字节在低地址 by zpyws
    {
        uint8 HB;
        uint8 LB;
    } byte;
    __PACKED struct
    {
        uint8 b0:1;
        uint8 b1:1;
        uint8 b2:1;
        uint8 b3:1;
        uint8 b4:1;
        uint8 b5:1;
        uint8 b6:1;
        uint8 b7:1;
        uint8 b8:1;
        uint8 b9:1;
        uint8 b10:1;
        uint8 b11:1;
        uint8 b12:1;
        uint8 b13:1;
        uint8 b14:1;
        uint8 b15:1;
    } bits;
} UN16_t;//union 16  2013-06-08 by zpyws

typedef __PACKED union
{
    uint32 Val;
    __PACKED uint16 W[2];//uint16 word value
    __PACKED uint8 B[4];//uint8 byte value
    __PACKED struct
    {
        uint16 HW;
        uint16 LW;
    } word;
    __PACKED struct
    {
        uint8 MB;
        uint8 UB;
        uint8 HB;
        uint8 LB;
    } byte;
    __PACKED struct
    {
        UN16_t high;
        UN16_t low;
    }wordUnion;
    __PACKED struct
    {
        uint8 b0:1;
        uint8 b1:1;
        uint8 b2:1;
        uint8 b3:1;
        uint8 b4:1;
        uint8 b5:1;
        uint8 b6:1;
        uint8 b7:1;
        uint8 b8:1;
        uint8 b9:1;
        uint8 b10:1;
        uint8 b11:1;
        uint8 b12:1;
        uint8 b13:1;
        uint8 b14:1;
        uint8 b15:1;
        uint8 b16:1;
        uint8 b17:1;
        uint8 b18:1;
        uint8 b19:1;
        uint8 b20:1;
        uint8 b21:1;
        uint8 b22:1;
        uint8 b23:1;
        uint8 b24:1;
        uint8 b25:1;
        uint8 b26:1;
        uint8 b27:1;
        uint8 b28:1;
        uint8 b29:1;
        uint8 b30:1;
        uint8 b31:1;
    } bits;
} UN32_t;//union 32  2013-06-07 by zpyws
#endif
//******************************************************************************************************************************
/********原创by zpyws******************************************************************************
外部使用时，仅需定义一下端口号和引脚号即可，举例如下
#define LED1_IDX    (4)
#define LED1_PORT   LPC_GPIO2

这样的宏定义有如下好处：当需要修改引脚时仅需要简单的修改端口和引脚两处即可
2012-03-30 by zpyws
****************************************************************************************/
#define SBI(X,BIT)     (X) |= (1UL<<(BIT))//已带Bit-Mask
#define CBI(X,BIT)     (X) &= (~(1UL<<(BIT)))//已带Bit-Mask
#define TBI(ADDRESS,BIT)   ((ADDRESS) & (1UL<<(BIT)))//TestBit from LYStudio 磊元

#define SBF(X,BF)       (X) |= (BF)//Bit Field Set by zpyws 2012-10-19
#define CBF(X,BF)       (X) &= ~(BF)//Bit Field Clear by zpyws 2012-10-19
#define GBF(X,BF)       (X&BF)//Bit Field Get  by zpyws 2012-10-19

#define BF_SET(X,BF)       	(X) |= (BF)//Bit Field Set by zpyws 2012-10-19
#define BF_CLR(X,BF)       	(X) &= ~(BF)//Bit Field Clear by zpyws 2012-10-19
#define BF_GET(X,BF)       	(X&BF)//Bit Field Get  by zpyws 2012-10-19
#define BF_MOD(X,BF,val)	X = ((X) & ~(BF)) | (val)//位域修改 by zpyws 2013-03-05
//******************************************************************************************************************************
#define SB(bit)              (1UL<<(bit))
#define CC(bit)              0x00
//******************************************************************************************************************************
//======结构体相关宏================================================================================
#define OFFSETOF(type, field)     ((size_t)&(((type *)0)->field))//结构体成员相对于结构头的偏移量
#define SIZEOF(type,field)        ((size_t)(sizeof(((type *)0)->field)))//结构体成员的占地面积
//======数组相关宏================================================================================
#define ARRAY_SIZE(a)		(sizeof(a)/sizeof(a[0]))//求一维数组的长度
#define _2D_ARRAY0_SIZE(a)	((uint32)(a[1])-(uint32)(a))//求二维数组第一维的长度 2013-07-12  by zpyws
#define _2D_ARRAY1_SIZE(a)	( sizeof(a) / (_2D_ARRAY0_SIZE(a)) )//求二维数组第二维的长度  2013-07-12  by zpyws
//******************************************************************************************************************************
#ifndef TRUE
	#define TRUE		1
#endif

#ifndef FALSE
	#define FALSE		0
#endif
//==================================================================================================
//IAR中断宏 by zpyws
#ifdef __IAR_SYSTEMS_ICC__//to detect whether the code was compiled by a compiler from IAR Systems.
	#define PRAGMA(A)         _Pragma(#A)//2011-10-21 BY ZPYWS
	#define PRAGMA_VECTOR(A)  PRAGMA(vector=A)
	
	#define ISR(A)   PRAGMA_VECTOR(A)\
	__interrupt void SIGNAL_##A##(void)
#endif
//******************************************************************************************
#endif
