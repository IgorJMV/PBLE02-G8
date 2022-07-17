/* 
 * File:   serial.h
 * Author: igorj
 *
 * Created on July 17, 2022, 4:38 PM
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include "mcc_generated_files/system.h"
#include <stdint.h>

void serialUpdate(uint32_t millis);
void serialAlarm(uint8_t a, uint32_t millis);

#endif	/* SERIAL_H */

