#include "lcd.h"
#include <util/delay.h>
#include "uart.h"
#include "keypad.h"

#define PASS_LEN 8
 uint8 value;
 uint8 flag = 0;
 uint8 i = 1;
 uint8 pass1[PASS_LEN] = {'*',0, 0, 0, 0, 0, '#'};
 uint8 pass2[PASS_LEN] = {'&',0, 0, 0, 0, 0, '#'};

void lcd_display(void) {

    LCD_displayStringRowColumn(0, 0, "Door Lock System");
   	    _delay_ms(2);

   	    LCD_clearScreen();
   	    LCD_displayStringRowColumn(0, 0, "Plz enter pass: ");

    while (1) {
        value = KEYPAD_getPressedKey();

        if (value != 0xFF) {
            _delay_ms(50);  // Debounce delay

            if (value != 0xFF) {
                if (value != '=') {
                    if (i < PASS_LEN - 2 && flag == 0) {  // First password entry
                        LCD_moveCursor(1, i-1);
                        LCD_displayCharacter('*');
                        pass1[i++] = value;
                    }
                } else if (flag == 0) {  // '=' pressed after entering first password
                    // Send pass1 over UART
                    flag = 1;
                    i = 1;  // Reset index for second password entry

                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "Plz re-enter the");
                    LCD_displayStringRowColumn(1, 0, "same pass: ");
                }

                // Second password entry
                if (flag == 1 && value != '=') {
                    if (i < PASS_LEN - 2) {
                        LCD_moveCursor(1, i + 9);
                        LCD_displayCharacter('*');
                        pass2[i++] = value;
                    }
                } else if (flag == 1 && i == PASS_LEN - 2 && value == '=') {
                    flag = 0 ;
                    i=1;
                    break ;
                }

            }
        }

    }

}
void open_door(void) {
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Plz enter old");
    LCD_displayStringRowColumn(1, 0, "pass:");
    flag = 0;
    i = 1;

    while (1) {
        value = KEYPAD_getPressedKey();

        if (value != 0xFF) {
            _delay_ms(50);  // Debounce delay

            if (value != '=') {
                if (i < PASS_LEN - 2 && flag == 0) {  // Old password entry
                    LCD_moveCursor(1, i + 4);
                    LCD_displayCharacter('*');
                    pass2[i++] = value;
                }
            } else if (flag == 0) {  // '=' pressed after old password entry
                UART_sendString(pass2);


                flag = 1;
                i = 1;  // Reset index

                LCD_clearScreen();
            }
        }

        if (flag == 1) {
            uint8 match_status = UART_recieveByte();
            if (match_status == 1) {
                LCD_displayStringRowColumn(0, 0, "Access Granted");
                _delay_ms(2000);  // Display success message
                break;
            } else {
                LCD_displayStringRowColumn(0, 0, "Access Denied");
                _delay_ms(2000);  // Display failure message
                break;
            }
        }
    }
}


int main(void) {
	UART_ConfigType uartConfig = {
	        UART_8_BIT,
	        UART_PARITY_DISABLE,
	        UART_ONE_STOP_BIT,
	        UART_BAUD_9600
	    };
	    UART_init(&uartConfig);

	    LCD_init();



	    while(1) {

	    	 lcd_display();

               uint8 match = 1;
              for (uint8 i = 1; i < PASS_LEN-2; i++) {
                         if (pass1[i] != pass2[i]) {
                             match = 0;
                             break;
                         }
                     }
                     if(match == 1){
                   UART_sendString(pass1);
                     }

                     else{
                    	 LCD_clearScreen();
                    	 _delay_ms(5);
                    	 lcd_display();
                     }



	         if(UART_recieveByte()==1){
	        	  LCD_clearScreen();
	        	 LCD_displayStringRowColumn(0, 0, "+ : Open Door");
	        	 LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	        	 if(KEYPAD_getPressedKey() == '+'){
	        	 	        		 open_door();

	        	 	        	 }

	        	 	        	 if(KEYPAD_getPressedKey() == '-'){
	        	 	        		 lcd_display();
	        	 	        	 }
	         }


}
}
