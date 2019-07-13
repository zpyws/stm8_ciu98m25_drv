#ifndef LED_H
#define LED_H
//******************Òý½Å¶¨Òå************************************************************************************************************
#define LED1_PORT   PB
#define LED1_PIN    (4)

//#define LED1        PD_ODR_ODR3
//#define LED1        POx(LED1_PORT,LED1_PIN)
#define LED2_PORT   PB
#define LED2_PIN    (5)

#define LED3_PORT   PE
#define LED3_PIN    (2)

#define LED4_PORT   PE
#define LED4_PIN    (1)

#define LED5_PORT   PE
#define LED5_PIN    (0)

#define LED6_PORT   PD
#define LED6_PIN    (0)
//===============================================
//********************************************************
#define LED1_ON()         IO_CLR(LED1_PORT,LED1_PIN)
#define LED1_OFF()        IO_SET(LED1_PORT,LED1_PIN)
#define LED1_TOG()        IO_FLP(LED1_PORT,LED1_PIN)

#define LED2_ON()         IO_CLR(LED2_PORT,LED2_PIN)
#define LED2_OFF()        IO_SET(LED2_PORT,LED2_PIN)
#define LED2_TOG()        IO_FLP(LED2_PORT,LED2_PIN)
//===============================================
//#define LED3_TOG()        IO_TOG(LED3_PORT,LED3_PIN)
//#define LED4_TOG()        IO_TOG(LED4_PORT,LED4_PIN)
//#define LED5_TOG()        IO_TOG(LED5_PORT,LED5_PIN)
//#define LED6_TOG()        IO_TOG(LED6_PORT,LED6_PIN)
//******************************************************************************************************************************
extern void InitLED(void);
//******************************************************************************************************************************
#endif
