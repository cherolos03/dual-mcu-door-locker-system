#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

/*******************************************************************************

 *                      Preprocessor Macros                                    *

 *******************************************************************************/

// I2C Status Bits in the TWSR Register
#define TWI_START         0x08
#define TWI_REP_START     0x10
#define TWI_MT_SLA_W_ACK  0x18
#define TWI_MT_SLA_R_ACK  0x40
#define TWI_MT_DATA_ACK   0x28
#define TWI_MR_DATA_ACK   0x50
#define TWI_MR_DATA_NACK  0x58

typedef enum {
	address_7bit,
	address_10bit,
	is_10bit
} TWI_AddressType;

typedef enum {
    Standard_Mode = 100000,
    Fast_Mode = 400000,
    Fast_Mode_Plus = 1000000,
    High_Speed_Mode = 3400000
} TWI_BaudRateType;

typedef struct {
    TWI_AddressType address;
    TWI_BaudRateType bit_rate;
} TWI_ConfigType;

/*******************************************************************************

 *                      Functions Prototypes                                   *

 *******************************************************************************/
void TWI_init(const TWI_ConfigType *Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
