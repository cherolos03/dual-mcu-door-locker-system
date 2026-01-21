

#include <avr/io.h>
#include "PWM_Timer.h"
#include  "gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle){

	GPIO_setupPinDirection(PWM_PORT_ID, PWM_PIN1_ID, PIN_OUTPUT);

	         TCNT0 = 0;

	    DcMotor_compare_value = (duty_cycle * 255) / 100;


	    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);



}
