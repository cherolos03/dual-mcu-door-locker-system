#include "Buzzer.h"

#include "gpio.h"


void Buzzer_init(void) {

	GPIO_setupPinDirection(BUZER_PORT_ID,BUZER_PIN_ID,PIN_OUTPUT);

	GPIO_writePin(BUZER_PORT_ID, BUZER_PIN_ID, LOGIC_LOW);

}

void Buzzer_on(void) {

		GPIO_writePin(BUZER_PORT_ID, BUZER_PIN_ID, LOGIC_HIGH);


}
void Buzzer_off(void) {

	GPIO_writePin(BUZER_PORT_ID, BUZER_PIN_ID, LOGIC_LOW);
}
