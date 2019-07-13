#ifndef ZPYWS_H
#define ZPYWS_H
//***************************************************************************************************************
//*****************************************************************************
//
// Helper Macros for Ethernet Processing
//
//*****************************************************************************
//Big-endian machine?
#ifdef _BIG_ENDIAN

//Host byte order to network byte order
#define YHTONS(value) (value)
#define YHTONL(value) (value)
#define yhtons(value) (value)
#define yhtonl(value) (value)

//Network byte order to host byte order
#define YNTOHS(value) (value)
#define YNTOHL(value) (value)
#define yntohs(value) (value)
#define yntohl(value) (value)

//Host byte order to little-endian byte order
#define YHTOLE16(value) EndianSwap16(value)
#define YHTOLE32(value) EndianSwap32(value)
#define YHTOLE64(value) EndianSwap64(value)
#define yhtole16(value) EndianSwap16(value)
#define yhtole32(value) EndianSwap32(value)
#define yhtole64(value) EndianSwap64(value)

//Little-endian byte order to host byte order
#define YLETOH16(value) EndianSwap16(value)
#define YLETOH32(value) EndianSwap32(value)
#define YLETOH64(value) EndianSwap64(value)
#define yletoh16(value) EndianSwap16(value)
#define yletoh32(value) EndianSwap32(value)
#define yletoh64(value) EndianSwap64(value)

//Host byte order to big-endian byte order
#define YHTOBE16(value) (value)
#define YHTOBE32(value) (value)
#define YHTOBE64(value) (value)
#define yhtobe16(value) (value)
#define yhtobe32(value) (value)
#define yhtobe64(value) (value)

//Big-endian byte order to host byte order
#define YBETOH16(value) (value)
#define YBETOH32(value) (value)
#define YBETOH64(value) (value)
#define ybetoh16(value) (value)
#define ybetoh32(value) (value)
#define ybetoh64(value) (value)

//Little-endian machine?
#else

//Host byte order to network byte order
#define YHTONS(value) EndianSwap16(value)
#define YHTONL(value) EndianSwap32(value)
#define yhtons(value) EndianSwap16(value)
#define yhtonl(value) EndianSwap32(value)

//Network byte order to host byte order
#define YNTOHS(value) EndianSwap16(value)
#define YNTOHL(value) EndianSwap32(value)
#define yntohs(value) EndianSwap16(value)
#define yntohl(value) EndianSwap32(value)

//Host byte order to little-endian byte order
#define YHTOLE16(value) (value)
#define YHTOLE32(value) (value)
#define YHTOLE64(value) (value)
#define yhtole16(value) (value)
#define yhtole32(value) (value)
#define yhtole64(value) (value)

//Little-endian byte order to host byte order
#define YLETOH16(value) (value)
#define YLETOH32(value) (value)
#define YLETOH64(value) (value)
#define yletoh16(value) (value)
#define yletoh32(value) (value)
#define yletoh64(value) (value)

//Host byte order to big-endian byte order
#define YHTOBE16(value) EndianSwap16(value)
#define YHTOBE32(value) EndianSwap32(value)
#define YHTOBE64(value) EndianSwap64(value)
#define yhtobe16(value) EndianSwap16(value)
#define yhtobe32(value) EndianSwap32(value)
#define yhtobe64(value) EndianSwap64(value)

//Big-endian byte order to host byte order
#define YBETOH16(value) EndianSwap16(value)
#define YBETOH32(value) EndianSwap32(value)
#define YBETOH64(value) EndianSwap64(value)
#define ybetoh16(value) EndianSwap16(value)
#define ybetoh32(value) EndianSwap32(value)
#define ybetoh64(value) EndianSwap64(value)

#endif
//***************************************************************************************************************
extern void MemCopy(uint8 *source,uint8 *target,uint16 len);//源地址，目标地址和拷贝的长度
extern uint8 MemCompare(uint8 *source,uint8 *target,uint16 len);//源地址，目标地址和比较的的长度
extern uint8 SprintUint16AsDecimal(uint16 num,uint8 *str);
extern uint8 SprintUint32AsHex(uint32 num,uint8 *str);
extern void *MemCpy(void *dest,const void *src,uint32 count);//目标地址，源地址和拷贝的长度
extern char *StrCpy(char *strDest, const char *strSrc);//目标字符串存放起始地址，源字符串起始地址
extern uint8 SprintUint32AsDecimal(uint32 num,uint8 *str);
extern sint8 StrCmp(char *p1, char *p2);
extern void MemSet(void *srcAddr, char pattern, ysize_t size);
extern int MemCmp(const void *buffer1,const void *buffer2, ysize_t count);
extern void PrintHexArray(uint8 *dat, ysize_t length);
extern uint16 EndianSwap16(uint16 dat);
extern uint32 EndianSwap32(uint32 dat);
#ifndef ARCH_STM8
	extern uint64 EndianSwap64(uint64 dat);
#endif
extern uint8 StrLen(char *str);
//***************************************************************************************************************
extern ROM uint32 TAB_BIT_MASK32[];
extern ROM uint8 TAB_HEX_NUM_ASCII[];
extern ROM uint8 TAB_BIT_MASK8[];
extern ROM uint8 TAB_CHN_NUM_ASCII[];
//***************************************************************************************************************
#endif
