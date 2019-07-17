#ifndef RS485_H
#define RS485_H
//******************************************************************************************************************************
extern void RS485_Init(void);
extern void UartRxDataProcess(uint8 *buff, uint16 len);
extern void RS485_Send(uint8 *buff,uint8 len);
//******************************************************************************************************************************
#define MODBUS_FRAME_SIZE_MIN     4       /*!< Minimum size of a Modbus RTU frame. */
#define MODBUS_FRAME_SIZE_MAX     SER_BUFF_SIZE/*!< Maximum size of a Modbus RTU frame. */

#define MODBUS_FRAME_SENSOR_OFF   0       /*!< Offset of slave address in Ser-PDU. */
#define MODBUS_FRAME_ADDR_OFF     1       /*!< Offset of slave address in Ser-PDU. */
#define MODBUS_FRAME_FUNC_OFF     2		  /*!< Offset of Modbus-PDU in Ser-PDU. */
#define MODBUS_FRAME_DATA_OFF     3		  /*!< Offset of Data Field in Ser-PDU. */
#define MODBUS_CRC_SIZE           1       /*!< Size of CRC field in PDU. */

#define MY_DEV_ADDRESS              Setting.Member.Address
//********************************************************************************************
#endif
