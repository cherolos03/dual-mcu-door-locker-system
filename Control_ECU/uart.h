#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum {
    UART_5_BIT ,
    UART_6_BIT,
    UART_7_BIT,
    UART_8_BIT,
    UART_9_BIT
} UART_BitDataType;

typedef enum {
    UART_PARITY_DISABLE ,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UART_ParityType;

typedef enum {
    UART_ONE_STOP_BIT ,
    UART_TWO_STOP_BITS
} UART_StopBitType;

typedef enum {
    UART_BAUD_2400 = 2400,
    UART_BAUD_4800 = 4800,
    UART_BAUD_9600 = 9600,
    UART_BAUD_14400 = 14400,
    UART_BAUD_19200 = 19200,
    UART_BAUD_38400 = 38400,
    UART_BAUD_57600 = 57600,
    UART_BAUD_115200 = 115200
} UART_BaudRateType;

typedef struct {
    UART_BitDataType bit_data;
    UART_ParityType parity;
    UART_StopBitType stop_bit;
    UART_BaudRateType baud_rate;
} UART_ConfigType;

void UART_init(const UART_ConfigType * Config_Ptr);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
