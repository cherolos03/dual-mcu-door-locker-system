/*
 * DC_Motor.h
 *
 *  Created on: Oct 4, 2024
 *      Author: egypt
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include <avr/io.h>
#include "std_types.h"


typedef enum{
	OFF,
	CW,
	ACW
}DcMotor_State;


#define DcMotor_PORT_ID              PORTD_ID

#define DcMotor_PIN1_ID               PIN6_ID
#define DcMotor_PIN2_ID               PIN7_ID

#define DcMotor_E_PORT_ID             PORTB_ID

#define DcMotor_E_PIN_ID              PIN3_ID




void DcMotor_init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed) ;

#endif
