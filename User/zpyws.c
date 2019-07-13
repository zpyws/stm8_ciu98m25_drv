#include "common_zpyws.h"
//******************************************************************************************************************************
ROM uint8 TAB_HEX_NUM_ASCII[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
ROM uint8 TAB_CHN_NUM_ASCII[] = "零一二三四五六七八九十";
//******************************************************************************************************************************
ROM uint32 TAB_BIT_MASK32[32] =
{
	(uint32)1<<0,  (uint32)1<<1,  (uint32)1<<2,  (uint32)1<<3,
	(uint32)1<<4,  (uint32)1<<5,  (uint32)1<<6,  (uint32)1<<7,
	(uint32)1<<8,  (uint32)1<<9,  (uint32)1<<10, (uint32)1<<11,
	(uint32)1<<12, (uint32)1<<13, (uint32)1<<14, (uint32)1<<15,
	(uint32)1<<16, (uint32)1<<17, (uint32)1<<18, (uint32)1<<19,
	(uint32)1<<20, (uint32)1<<21, (uint32)1<<22, (uint32)1<<23,
	(uint32)1<<24, (uint32)1<<25, (uint32)1<<26, (uint32)1<<27,
	(uint32)1<<28, (uint32)1<<29, (uint32)1<<30, (uint32)1<<31
};
//******************************************************************************************************************************
ROM uint8 TAB_BIT_MASK8[8] =
{
	(uint8)1<<0,  (uint8)1<<1,  (uint8)1<<2,  (uint8)1<<3,
	(uint8)1<<4,  (uint8)1<<5,  (uint8)1<<6,  (uint8)1<<7
};
//******************************************************************************************************************************
extern void MemCopy(uint8 *source,uint8 *target,uint16 len)//源地址，目标地址和拷贝的长度
{
	uint16 i;

	for( i=0; i<len; i++ )
	{
		*target++ = *source++;
	}
}
//******************************************************************************************************************************
//比较两段内存是否匹配，匹配返回0，不匹配返回1
extern uint8 MemCompare(uint8 *source,uint8 *target,uint16 len)//源地址，目标地址和比较的的长度
{
	uint16 i;

	for( i=0; i<len; i++ )
	{
		if( *target++ != *source++)return(1);
	}
	return(0);
}
//******************************************************************************************************************************
//将16进制数据输出为字符串到某一内存地址中
//num 16位长的数，str将结果输出到
//返回：输出的字符个数
extern uint8 SprintUint16AsDecimal(uint16 num,uint8 *str)
{
	uint8 i;

	i = 0;
	if(num>=10000)goto WAN;
	if(num>=1000)goto QIAN;
	else if(num>=100)goto BAI;
	else if(num>=10)goto SHI;
	else goto GE;

WAN:
	str[i++] = num / 10000;//xxxxx
	num %= 10000;//xxxx
QIAN:	
	str[i++] = num / 1000;
	num %= 1000;//xxx
BAI:
	str[i++] = num / 100;
	num %= 100;//xx
SHI:
	str[i++] = num / 10;
GE:
	str[i++] =  num % 10;//x

	for(num=0; num<i; num++)
	{
		str[num] = TAB_HEX_NUM_ASCII[ str[num] ];
	}
	return(i);
}
//******************************************************************************************************************************
//将16进制数据输出为字符串到某一内存地址中
//num 32位长的数，str将结果输出到
//返回：输出的字符个数
//2013-04-15 by zpyws
extern uint8 SprintUint32AsDecimal(uint32 num,uint8 *str)
{
	uint8 i;

	i = 0;
	if(num>=100000UL)goto SprintUint32AsDecimal_1;//10位数
	else goto SprintUint32AsDecimal_2;//五位或以下
	
SprintUint32AsDecimal_1:
	if(num>=1000000000UL)goto PLACE10;
	if(num>=100000000UL)goto PLACE9;
	if(num>=10000000UL)goto PLACE8;
	if(num>=1000000UL)goto PLACE7;
	if(num>=100000UL)goto PLACE6;
SprintUint32AsDecimal_2:
	if(num>=10000UL)goto PLACE5;
	if(num>=1000UL)goto PLACE4;
	if(num>=100UL)goto PLACE3;
	if(num>=10UL)goto PLACE2;
	goto PLACE1;
	
PLACE10:
	str[i++] = num / 1000000000UL;//10位数
	num %= 1000000000UL;
PLACE9:
	str[i++] = num / 100000000UL;//9位数
	num %= 100000000UL;
PLACE8:
	str[i++] = num / 10000000UL;//8位数
	num %= 10000000UL;
PLACE7:
	str[i++] = num / 1000000UL;//7位数
	num %= 1000000UL;
PLACE6:
	str[i++] = num / 100000UL;//6位数
	num %= 100000UL;
PLACE5:
	str[i++] = num / 10000UL;//5位数
	num %= 10000UL;
PLACE4:
	str[i++] = num / 1000UL;//4位数
	num %= 1000UL;
PLACE3:
	str[i++] = num / 100UL;//3位数
	num %= 100UL;
PLACE2:
	str[i++] = num / 10;//2位数
PLACE1:
	str[i++] = num % 10;//1位数

	for(num=0; num<i; num++)
	{
		str[num] = TAB_HEX_NUM_ASCII[ str[num] ];
	}
	str[i] = '\0';//最后放上结束符
	return(i);
}
//******************************************************************************************************************************
//将16进制数据输出为字符串到某一内存地址中
//num 32位长的数，str将结果输出到
//返回：输出的字符个数
extern uint8 SprintUint32AsHex(uint32 num,uint8 *str)
{
	uint8 i;

	for(i=0; i<8; i++)
	{
		str[i] = TAB_HEX_NUM_ASCII[ (num>>(28-i*4))&0x0fUL ];
	}
	return(i);
}
//******************************************************************************************************************************
//2012-01-07 by zpyws
extern void *MemCpy(void *dest,const void *src,uint32 count)//目标地址，源地址和拷贝的长度
{
// 	assert((dest!=0)&&(src!=0));
	char *d = (char *)dest;
	char *s = (char *)src;
	
	while(count--)
	{
		*d++ = *s++;
	}
	return(dest);
}
//******************************************************************************************************************************
//2012-01-07 by zpyws
extern char *StrCpy(char *strDst, const char *strSrc)//目标字符串存放起始地址，源字符串起始地址
{
//     assert((strDest!=NULL) && (strSrc !=NULL));
    char *address = strDst;
	
//     while( (*strDest++ = * strSrc++) != ‘\0’ );
	while(*strSrc!='\0')
	{
		*strDst++ = *strSrc++;
	}
	*strDst = '\0';		//注意：标准的字符串拷贝函数并不复制结束符
    return address ;
}
//******************************************************************************************************************************
//看Asic码，str1>str2，返回值 > 0；两串相等，返回0
//2013-04-16 by zpyws
extern sint8 StrCmp(char *p1, char *p2)
{
	while( *p1 != '\0' && *p2 != '\0' )
	{
		if( *p1 == *p2 )
		{
			p1++ ; p2++ ;
			continue;
		}
		if( *p1 > *p2 ) return 1 ;
		else return -1;
	}
	if( *p1 == '\0' )
	{
		if( *p2 == '\0') return 0 ;
		else return -1;
	}
	else return 1;
}
//******************************************************************************************************************************
//void *srcAddr:要格式化的内存块起始地址
//char pattern: 要格式化的内容
//ysize_t size: 要格式化的内存块字节数
//2015-05-11  by zpyws
extern void MemSet(void *srcAddr, char pattern, ysize_t size)
{
	char * s;
	
	s = (char *)srcAddr;
	for(; size>0; size--)
	{
		*s++ = pattern;
	}
}
//******************************************************************************************************************************
//功能：比较内存区域buf1和buf2的前count个字节。
//当buf1<buf2时，返回值<0
//当buf1=buf2时，返回值=0
//当buf1>buf2时，返回值>0
//2015-05-13  by zpyws
extern int MemCmp(const void *buffer1,const void *buffer2, ysize_t count)
{
	if (!count)return(0);
	
	while ( --count && *(char *)buffer1 == *(char *)buffer2)
	{
		buffer1 = (char *)buffer1 + 1;
		buffer2 = (char *)buffer2 + 1;
	}
	return( *((unsigned char *)buffer1) - *((unsigned char *)buffer2) );
}
//******************************************************************************************************************************
//输出字节数组
//2015-05-13  by zpyws
//extern void PrintHexArray( uint8 (*put)(uint8 *,ysize_t), uint8 *dat, ysize_t length)
extern void PrintHexArray(uint8 *dat, ysize_t length)
{
	uint8 str[8];
	ysize_t i;
	
	OSSemPend( &SemUart1Tx, 0 );
//===================================================================
	i = SprintUint32AsHex((uint32)(&dat), str);
	UART1_PRINT_STRING_RAW("addr = 0x");
	Uart1PutRaw(str, i);
	UART1_PRINT_STRING_RAW(", len = ");
	i = SprintUint32AsDecimal(length, str);
	Uart1PutRaw(str, i);
	UART1_PRINT_STRING_RAW("\r\n");
//===================================================================
	for(i=0; i<length; i++)
	{
		str[0] = TAB_HEX_NUM_ASCII[ dat[i]>>4 ];
		str[1] = TAB_HEX_NUM_ASCII[ dat[i]&0x0f ];
		str[2] = ' ';
		Uart1PutRaw(str,3);
	}
	UART1_PRINT_STRING_RAW("\r\n");
	OSSemPost(&SemUart1Tx);//释放资源
}
//******************************************************************************************************************************
//Swaps the endian-ness of a DWORD.
//BY ZPYWS 2013-02-22
extern uint32 EndianSwap32(uint32 dat)
{
	// Swap bytes 0 and 3
	((UN32_t*)&dat)->B[0] ^= ((UN32_t*)&dat)->B[3];
	((UN32_t*)&dat)->B[3] ^= ((UN32_t*)&dat)->B[0];
	((UN32_t*)&dat)->B[0] ^= ((UN32_t*)&dat)->B[3];

	// Swap bytes 1 and 2
	((UN32_t*)&dat)->B[1] ^= ((UN32_t*)&dat)->B[2];
	((UN32_t*)&dat)->B[2] ^= ((UN32_t*)&dat)->B[1];
	((UN32_t*)&dat)->B[1] ^= ((UN32_t*)&dat)->B[2];

	return dat;
}
//******************************************************************************************************************************
//Swaps the endian-ness of a WORD.
//BY ZPYWS 2013-02-22
extern uint16 EndianSwap16(uint16 dat)
{
	UN16_t t;
	uint8 b;

	t.Val   = dat;
	b       = t.B[1];
	t.B[1]  = t.B[0];
	t.B[0]  = b;

	return t.Val;
}
//******************************************************************************************************************************
//Swaps the endian-ness of a WORD.
//BY ZPYWS 2013-02-22
#ifndef ARCH_STM8
extern uint64 EndianSwap64(uint64 x)
{
	return( \
   (((x) & 0x00000000000000FFULL) << 56) | \
   (((x) & 0x000000000000FF00ULL) << 40) | \
   (((x) & 0x0000000000FF0000ULL) << 24) | \
   (((x) & 0x00000000FF000000ULL) << 8) | \
   (((x) & 0x000000FF00000000ULL) >> 8) | \
   (((x) & 0x0000FF0000000000ULL) >> 24) | \
   (((x) & 0x00FF000000000000ULL) >> 40) | \
   (((x) & 0xFF00000000000000ULL) >> 56));
}
#endif
//******************************************************************************************************************************
//计算字符串长度(不含结束符)
//2015-07-24 by zpyws
extern uint8 StrLen(char *str)
{
    uint8 cnt = 0;;
	
	while(*str++)
	{
		cnt++;
	}
    return cnt ;
}
//******************************************************************************************************************************
