#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>

void TWI_init(const TWI_ConfigType *Config_Ptr)
{
    TWBR = (F_CPU / (2 * Config_Ptr->bit_rate)) - 8;
    TWSR = 0x00;

    if (Config_Ptr->address == is_10bit) {
          TWAR = (Config_Ptr->address == address_10bit << 1) | 0x01;
      } else {
          TWAR = (Config_Ptr->address == address_7bit << 1);
      }
    TWCR = (1 << TWEN); // Enable TWI
}

void TWI_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (BIT_IS_CLEAR(TWCR, TWINT));
}

void TWI_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (BIT_IS_CLEAR(TWCR, TWINT));
}

uint8 TWI_readByteWithACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (BIT_IS_CLEAR(TWCR, TWINT));
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (BIT_IS_CLEAR(TWCR, TWINT));
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    status = TWSR & 0xF8; // Masking to get status bits
    return status;
}
