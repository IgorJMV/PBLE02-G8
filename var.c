#include "var.h"
#include "memory.h"
#include "lcd.h"

#define STATE_ADDR 0x00
#define ALARM_HIGH_1 0x01
#define ALARM_LOW_1 0x03
#define ALARM_HIGH_2 0x05
#define ALARM_LOW_2 0x07

uint8_t getState(void){
    uint8_t state[1];
    readMem(STATE_ADDR, state, 1);
    return state[0];
}

void setState(uint8_t state){
    uint8_t pstate[1];
    pstate[0] = state;
    writeMem(STATE_ADDR, pstate, 1);
}

uint16_t getAlarmHigh1(void){
    uint8_t alarmHigh1[2];
    readMem(ALARM_HIGH_1, alarmHigh1, 2);
    uint8_t LSB = alarmHigh1[0];
    uint8_t MSB = alarmHigh1[1];
    //lcdUInt16(MSB<<8+LSB);
    lcdData('|');
    lcdInt(alarmHigh1[0]);
    lcdData('|');
    lcdInt(alarmHigh1[1]);
    lcdData('|');
    return 0;
};

void setAlarmHigh1(uint16_t alarmHigh1){
    uint8_t palarmHigh1[2];
    palarmHigh1[0] = alarmHigh1 & 0xFF;
    palarmHigh1[1] = alarmHigh1 >> 8;
    writeMem(ALARM_HIGH_1, palarmHigh1, 2);
}

uint16_t getAlarmLow1(void){
    uint8_t alarmLow1[2];
    readMem(ALARM_LOW_1, alarmLow1, 2);
    return (alarmLow1[1]<<8+alarmLow1[0]);
}

void setAlarmLow1(uint16_t alarmLow1){
    uint8_t palarmLow1[2];
    palarmLow1[0] = alarmLow1>>8;
    palarmLow1[1] = alarmLow1&0xFF;
    writeMem(ALARM_HIGH_1, palarmLow1, 2);
}
