/* 
 * File:   alarm.h
 * Author: igorj
 *
 * Created on July 17, 2022, 4:56 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#include "mcc_generated_files/system.h"
#include <stdint.h>

void alarmsInit(void);
uint8_t alarmsStatusUpdate(uint32_t millis);

#endif	/* ALARM_H */

