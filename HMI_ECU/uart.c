#include "uart.h"
#include "avr/io.h"
#include "common_macros.h"

void UART_init(const UART_ConfigType * Config_Ptr) {
    uint16 ubrr_value = 0;

    UCSRA = (1 << U2X);
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (Config_Ptr->bit_data << UCSZ0) | (Config_Ptr->parity << UPM0) | (Config_Ptr->stop_bit << USBS);

    ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
    UBRRH = ubrr_value >> 8;
    UBRRL = ubrr_value;
}

void UART_sendByte(const uint8 data) {
    while (BIT_IS_CLEAR(UCSRA, UDRE)) {}
    UDR = data;
}

uint8 UART_recieveByte(void) {
    while (BIT_IS_CLEAR(UCSRA, RXC)) {}
    return UDR;
}

void UART_sendString(const uint8 *Str) {
    uint8 i = 0;
    while (Str[i] != '\0') {
        UART_sendByte(Str[i]);
        i++;
    }
}

void UART_receiveString(uint8 *Str) {
    uint8 i = 0;
    Str[i] = UART_recieveByte();
    while (Str[i] != '#') {
        i++;
        Str[i] = UART_recieveByte();
    }
    Str[i] = '\0';
}
