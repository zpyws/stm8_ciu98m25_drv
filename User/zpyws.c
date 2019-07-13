#include "common_zpyws.h"
//******************************************************************************************************************************
ROM uint8 TAB_HEX_NUM_ASCII[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
ROM uint8 TAB_CHN_NUM_ASCII[] = "��һ�����������߰˾�ʮ";
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
extern void MemCopy(uint8 *source,uint8 *target,uint16 len)//Դ��ַ��Ŀ���ַ�Ϳ����ĳ���
{
	uint16 i;

	for( i=0; i<len; i++ )
	{
		*target++ = *source++;
	}
}
//******************************************************************************************************************************
//�Ƚ������ڴ��Ƿ�ƥ�䣬ƥ�䷵��0����ƥ�䷵��1
extern uint8 MemCompare(uint8 *source,uint8 *target,uint16 len)//Դ��ַ��Ŀ���ַ�ͱȽϵĵĳ���
{
	uint16 i;

	for( i=0; i<len; i++ )
	{
		if( *target++ != *source++)return(1);
	}
	return(0);
}
//******************************************************************************************************************************
//��16�����������Ϊ�ַ�����ĳһ�ڴ��ַ��
//num 16λ��������str����������
//���أ�������ַ�����
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
//��16�����������Ϊ�ַ�����ĳһ�ڴ��ַ��
//num 32λ��������str����������
//���أ�������ַ�����
//2013-04-15 by zpyws
extern uint8 SprintUint32AsDecimal(uint32 num,uint8 *str)
{
	uint8 i;

	i = 0;
	if(num>=100000UL)goto SprintUint32AsDecimal_1;//10λ��
	else goto SprintUint32AsDecimal_2;//��λ������
	
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
	str[i++] = num / 1000000000UL;//10λ��
	num %= 1000000000UL;
PLACE9:
	str[i++] = num / 100000000UL;//9λ��
	num %= 100000000UL;
PLACE8:
	str[i++] = num / 10000000UL;//8λ��
	num %= 10000000UL;
PLACE7:
	str[i++] = num / 1000000UL;//7λ��
	num %= 1000000UL;
PLACE6:
	str[i++] = num / 100000UL;//6λ��
	num %= 100000UL;
PLACE5:
	str[i++] = num / 10000UL;//5λ��
	num %= 10000UL;
PLACE4:
	str[i++] = num / 1000UL;//4λ��
	num %= 1000UL;
PLACE3:
	str[i++] = num / 100UL;//3λ��
	num %= 100UL;
PLACE2:
	str[i++] = num / 10;//2λ��
PLACE1:
	str[i++] = num % 10;//1λ��

	for(num=0; num<i; num++)
	{
		str[num] = TAB_HEX_NUM_ASCII[ str[num] ];
	}
	str[i] = '\0';//�����Ͻ�����
	return(i);
}
//******************************************************************************************************************************
//��16�����������Ϊ�ַ�����ĳһ�ڴ��ַ��
//num 32λ��������str����������
//���أ�������ַ�����
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
extern void *MemCpy(void *dest,const void *src,uint32 count)//Ŀ���ַ��Դ��ַ�Ϳ����ĳ���
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
extern char *StrCpy(char *strDst, const char *strSrc)//Ŀ���ַ��������ʼ��ַ��Դ�ַ�����ʼ��ַ
{
//     assert((strDest!=NULL) && (strSrc !=NULL));
    char *address = strDst;
	
//     while( (*strDest++ = * strSrc++) != ��\0�� );
	while(*strSrc!='\0')
	{
		*strDst++ = *strSrc++;
	}
	*strDst = '\0';		//ע�⣺��׼���ַ������������������ƽ�����
    return address ;
}
//******************************************************************************************************************************
//��Asic�룬str1>str2������ֵ > 0��������ȣ�����0
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
//void *srcAddr:Ҫ��ʽ�����ڴ����ʼ��ַ
//char pattern: Ҫ��ʽ��������
//ysize_t size: Ҫ��ʽ�����ڴ���ֽ���
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
//���ܣ��Ƚ��ڴ�����buf1��buf2��ǰcount���ֽڡ�
//��buf1<buf2ʱ������ֵ<0
//��buf1=buf2ʱ������ֵ=0
//��buf1>buf2ʱ������ֵ>0
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
//����ֽ�����
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
	OSSemPost(&SemUart1Tx);//�ͷ���Դ
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
//�����ַ�������(����������)
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
