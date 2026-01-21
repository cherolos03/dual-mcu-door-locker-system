#include "uart.h"
#include "external_eeprom.h"
#include "Timer.h"
#include "twi.h"
#include "DC_Motor.h"
#include "Buzzer.h"
#include "PWM_Timer.h"
#include <util/delay.h>

#define PASS_LEN 7
#define EEPROM_BASE_ADDR 0x0000 // Starting EEPROM address for password storage

// Function prototypes
void storePasswordInEEPROM(uint8 *password);
uint8 verifyPassword(uint8 *password);
void stopMotorAfterTimeout(void);


int main() {
    uint8 pass1[PASS_LEN];

    // UART Configuration
    UART_ConfigType uartConfig = {
         UART_8_BIT,
         UART_PARITY_DISABLE,
         UART_ONE_STOP_BIT,
         UART_BAUD_9600
    };
    UART_init(&uartConfig);

    // TWI (I2C) Configuration for EEPROM communication
    TWI_ConfigType twiConfig = {
        address_7bit, // Assuming 7-bit addressing
        Fast_Mode     // Configuring for fast mode (400 kbps)
    };
    TWI_init(&twiConfig);
    Timer_ConfigType timerConfig = {
            0,
           46875, // Value for 15 seconds (assuming prescaler is set to 1024)
            Timer1,
			F_CPU_1024,
           CompareValue_Mode
       };

    DcMotor_init();
    Buzzer_init();

    while (1) {

        // Receive the password from UART
        UART_receiveString(pass1);


        // Check if the first character is '*', indicating storage command
        if (pass1[0] == '*') {
            storePasswordInEEPROM(pass1);
            UART_sendByte(1);

        }

        if(pass1[0] == '&'){
        	 uint8 match1 = verifyPassword(pass1);
        	        if(match1 == 1 ){
        	        	DcMotor_Rotate(CW, 100) ;
        	        	 Timer_init(&timerConfig);

        	        		        Buzzer_on();
        	        }
        }


    }
}

// Function to store the password in EEPROM
void storePasswordInEEPROM(uint8 *password) {
    for (uint8 i = 1; i < PASS_LEN; i++) {
        EEPROM_writeByte(EEPROM_BASE_ADDR + i, password[i]);
        _delay_ms(10);  // Small delay for EEPROM write stability
    }
}

// Function to verify password stored in EEPROM with a given password
uint8 verifyPassword(uint8 *password) {
    uint8 stored_pass_byte;
    for (uint8 i = 1; i < PASS_LEN; i++) {
        EEPROM_readByte(EEPROM_BASE_ADDR + i, &stored_pass_byte);

        if (stored_pass_byte != password[i]) {
            return 0;  // Passwords do not match
        }
    }
    return 1;  // Passwords match
}
void stopMotorAfterTimeout(void) {
	DcMotor_Rotate(OFF, 0) ;
    Timer_deInit(Timer1); // Stop the timer after timeout
}
