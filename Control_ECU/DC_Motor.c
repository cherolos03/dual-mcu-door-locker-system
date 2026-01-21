#include "DC_Motor.h"
#include "gpio.h"
#include "PWM_Timer.h"

void DcMotor_init(void){
	GPIO_setupPinDirection(DcMotor_PORT_ID, DcMotor_PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor_PORT_ID, DcMotor_PIN2_ID, PIN_OUTPUT);

	GPIO_setupPinDirection(DcMotor_E_PORT_ID, DcMotor_E_PIN_ID, PIN_OUTPUT);


	 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN1_ID, LOGIC_LOW);
	 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN2_ID, LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
   switch(state){
	case OFF :
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN1_ID, LOGIC_LOW);
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN2_ID, LOGIC_LOW);
		PWM_Timer0_Start(0);
		break;
	case CW :
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN1_ID, LOGIC_HIGH);
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN2_ID, LOGIC_LOW);
		PWM_Timer0_Start(speed);
		 break;
	case ACW :
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN1_ID, LOGIC_LOW);
		 GPIO_writePin(DcMotor_PORT_ID, DcMotor_PIN2_ID, LOGIC_HIGH);
		PWM_Timer0_Start(speed);
		break;


	}

}
