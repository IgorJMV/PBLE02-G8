/* 
 * File:   menu.h
 * Author: igorj
 *
 * Created on July 3, 2022, 9:53 PM
 */

#ifndef MENU_H
#define	MENU_H

#include <stdint.h>
#include "statemachine.h"

void updateMenu(uint32_t millis);
void updateData(uint32_t millis);
void updateLimits(void);

#endif	/* MENU_H */

