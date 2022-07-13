/* 
 * File:   statemachine.h
 * Author: igorj
 *
 * Created on 27 de Junho de 2022, 15:08
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include <stdint.h>

#include "keypad.h"

typedef enum{
    ALARM1,
    HIGH_ALARM1,
    LOW_ALARM1,
    ALARM2,
    HIGH_ALARM2,
    LOW_ALARM2,
    TIME,
    SET_TIME,
    LANGUAGE,
    STATES_END
}state;

void statemachine_init(void);
void statemachine_update(kpType button, uint32_t millis);

#endif	/* STATEMACHINE_H */

