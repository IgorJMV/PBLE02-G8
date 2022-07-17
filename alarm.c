#include "mcc_generated_files/system.h"
#include "alarm.h"
#include "var.h"
#include "adc.h"

uint8_t timerValue;

void alarmsInit(void){
    timerValue = 0;
}

uint8_t alarmsStatusUpdate(uint32_t millis){
    uint8_t status = 0;
    
    uint16_t high1 = getAlarmHigh1();
    uint16_t low1 = getAlarmLow1();
    uint16_t high2 = getAlarmHigh2();
    uint16_t low2 = getAlarmLow2();
    uint32_t timer = getTimer();
    
    uint16_t potValue = readPot();
    int diffValue = readDifferential();
    
    if(potValue <= low1)    ((status) |= (1UL << (0)));
    if(potValue >= high1)   ((status) |= (1UL << (1)));
    if(diffValue <= low2)   ((status) |= (1UL << (2)));
    if(diffValue >= high2)  ((status) |= (1UL << (3)));
    
    if(millis >= timer){
        ((status) |= (1UL << (4)));
        timerValue = 0;
    }
    
    return status;
}