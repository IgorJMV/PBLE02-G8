/* 
 * File:   keypad.h
 * Author: igorj
 *
 * Created on 6 de Junho de 2022, 20:57
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include <stdbool.h>
#include "mcc_generated_files/adc1.h"

typedef enum {
    B1, B2, B3, B4, B5, NOTHING
}kpType;

kpType kpRead(void);
bool isKpPressed(kpType key);

#endif	/* KEYPAD_H */

