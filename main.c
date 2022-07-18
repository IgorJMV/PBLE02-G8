/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC32MM0064GPM048
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "lcd.h"
#include "keypad.h"
#include "memory.h"
#include "adc.h"
#include "menu.h"
#include "pwm.h"
#include "mcc_generated_files/tmr1.h"
#include "statemachine.h"
#include "alarm.h"
#include "serial.h"

/*
                         Main application
 */

#define Alarm_Period 150

uint32_t lastTime = 0;
uint32_t lastAlarm = 0;
uint8_t lastAlarmStatus = 0;

static uint32_t millis = 0;

kpType button = NOTHING;

void *timer1(void);

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TMR1_SetInterruptHandler(timer1);
    
    LED1_SetHigh();
    LED2_SetHigh();
    LED3_SetHigh();
    LED4_SetHigh();
    
    alarmsInit();
    statemachine_init();
    statemachine_update(NOTHING, millis);
    
    
    while (1){
        serialUpdate(millis);
        
        button = kpRead();
        if(button != NOTHING){
            statemachine_update(button, millis);
            updateLimits();
        }
        
        if(millis - lastAlarm >= Alarm_Period){
            lastAlarm = millis;
            uint8_t alarmStatus = alarmsStatusUpdate(millis);
            if(lastAlarm != alarmStatus){
                serialAlarm(alarmStatus, millis);
                lastAlarmStatus = alarmStatus;
                
                if((((alarmStatus) >> (0)) & 0x01))
                    LED1_SetLow();
                else
                    LED1_SetHigh();
                
                if((((alarmStatus) >> (1)) & 0x01))
                    LED2_SetLow();
                else
                    LED2_SetHigh();
                
                if((((alarmStatus) >> (2)) & 0x01))
                    LED3_SetLow();
                else
                    LED3_SetHigh();
                
                if((((alarmStatus) >> (3)) & 0x01))
                    LED4_SetLow();
                else
                    LED4_SetHigh();
            }
        }
        if(millis - lastTime >= 200){
            lastTime = millis;
            updateData(millis);
        }
    }
    return 1; 
}
/**
 End of File
*/

void *timer1(void){
    millis++;
}