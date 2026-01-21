/*
 * PWM_Timer.h
 *
 *  Created on: Oct 4, 2024
 *      Author: egypt
 */

#ifndef PWM_TIMER_H_
#define PWM_TIMER_H_

#include "std_types.h"

#define PWM_PORT_ID              PORTB_ID

#define PWM_PIN1_ID               PIN3_ID

#define DcMotor_compare_value        OCR0


void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_TIMER_H_ */
