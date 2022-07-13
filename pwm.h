/* 
 * File:   pwm.h
 * Author: igorj
 *
 * Created on July 13, 2022, 1:32 PM
 */

#ifndef PWM_H
#define	PWM_H

#include <stdint.h>

#define PWM_MAX_FREQ 1000000
#define PWM_MIN_FREQ 100

void PWM_init(uint32_t frequency);
void PWM_setDutyCycle(uint8_t new_duty_cycle);
uint8_t PWM_getDutyCycle();

#endif	/* PWM_H */

