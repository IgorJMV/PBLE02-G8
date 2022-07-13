/* 
 * File:   var.h
 * Author: igorj
 *
 * Created on 27 de Junho de 2022, 14:34
 */

#ifndef VAR_H
#define	VAR_H

#include "stdint.h"

    uint8_t getState(void);
    void setState(uint8_t state);
    
    uint16_t getAlarmHigh1(void);
    void setAlarmHigh1(uint16_t alarmHigh1);

    uint16_t getAlarmLow1(void);
    void setAlarmLow1(uint16_t alarmLow1);

    uint16_t getAlarmHigh2(void);
    void setAlarmHigh1(uint16_t alarmHigh2);

    uint16_t getAlarmLow2(void);
    void setAlarmLow1(uint16_t alarmLow2);
    
    uint32_t getTimer(void);
    void setTimer(uint32_t timer);
    
    uint8_t getLanguage(void);
    void setLanguage(uint8_t language);

#endif	/* VAR_H */

