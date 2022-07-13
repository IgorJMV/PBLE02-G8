#include "statemachine.h"
#include "var.h"
#include "lcd.h"

void statemachine_init(void){
    uint8_t state = getState();
    state %= STATES_END;
    setState(state);
    lcdInit();
    lcdCommand(LCD_CLEAR);
}

void statemachine_update(kpType button, uint32_t millis){
    uint8_t state = getState();
    
    switch(state){
        case ALARM1:
            if(button == B3){
                setState(HIGH_ALARM1);
            }
            if(button == B1){
                setState(ALARM2);
            }
            if(button == B2){
                setState(LANGUAGE);
            }
            
            break;
            
        case HIGH_ALARM1:
            //MENU CHANGE
            if(button == B2 || button == B1){
                setState(LOW_ALARM1);
            }
            
            if(button == B3){
                setState(ALARM1);
            }
            //MENU CHANGE
            
            //LIMITS CONFIG
            if(button == B4){
                setAlarmHigh1(getAlarmHigh1()+10);
            }
            if(button == B5){
                setAlarmHigh1(getAlarmHigh1()-10);
            }
            //LIMITS CONFIG
            break;
            
        case LOW_ALARM1:
            //MENU CHANGE
            if(button == B2 || button == B1){
                setState(HIGH_ALARM1);
            }
            
            if(button == B3){
                setState(ALARM1);
            }
            //MENU CHANGE
            
            //LIMITS CONFIG
            if(button == B4){
                setAlarmLow1(getAlarmLow1()+10);
            }
            if(button == B5){
                setAlarmLow1(getAlarmLow1()-10);
            }
            //LIMITS CONFIG
            break;
            
        case ALARM2:
            if(button == B3){
                setState(HIGH_ALARM2);
            }
            if(button == B1){
                setState(TIME);
            }
            if(button == B2){
                setState(ALARM1);
            }
            break;
            
        case HIGH_ALARM2:
            //MENU CHANGE
            if(button == B2 || button == B1){
                setState(LOW_ALARM2);
            }
            
            if(button == B3){
                setState(ALARM2);
            }
            //MENU CHANGE
            
            //LIMITS CONFIG
            if(button == B4){
                setAlarmHigh2(getAlarmHigh2()+10);
            }
            if(button == B5){
                setAlarmHigh2(getAlarmHigh2()-10);
            }
            //LIMITS CONFIG
            break;
            
        case LOW_ALARM2:
            //MENU CHANGE
            if(button == B2 || button == B1){
                setState(HIGH_ALARM2);
            }
            
            if(button == B3){
                setState(ALARM2);
            }
            //MENU CHANGE
            
            //LIMITS CONFIG
            if(button == B4){
                setAlarmLow2(getAlarmLow2()+10);
            }
            if(button == B5){
                setAlarmLow2(getAlarmLow2()-10);
            }
            //LIMITS CONFIG
            break;
            
        case TIME:
            if(button == B1){
                setState(LANGUAGE);
            }
            if(button == B2){
                setState(ALARM2);
            }
            
            if(button == B3){
                setState(SET_TIME);
            }
            
            break;
            
        case SET_TIME:
            if(button == B3){
                setState(TIME);
            }
            
            if(button == B4){
                setTimer(millis + 5000);
            }
            if(button == B5){
                setTimer(millis > 5000 ? millis - 5000 : 0);
            }
            
            break;
            
        case LANGUAGE:
            if(button == B1){
                setState(ALARM1);
            }
            if(button == B2){
                setState(TIME);
            }
            
            if(button == B4 || button == B5){
                setLanguage(getLanguage() ? 0 : 1);
            }
            
            break;
    }
    
    updateMenu(millis);
}