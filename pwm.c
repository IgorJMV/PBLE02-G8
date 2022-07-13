#include <xc.h>
#include "pwm.h"

uint8_t pwm_duty_cycle;

void PWM_init(uint32_t frequency){
    if(frequency > PWM_MAX_FREQ)        frequency = PWM_MAX_FREQ;
    else if(frequency < PWM_MIN_FREQ)   frequency = PWM_MIN_FREQ;
    
    CCP1PR = ((8000000/frequency)-1); //Período do timer
    CCP1TMR = 0; //Limpa o timer
    
    //Configura o duty cycle inicial
    pwm_duty_cycle = 50;
    CCP1RA = 0;
    CCP1RB = (pwm_duty_cycle*(CCP1PR+1))/100;
    
    CCP1CON1bits.MOD = 0x05; //Configura o modo de operação
    CCP1CON1bits.TMRPS = 0; //Configura o prescaler como 1
    CCP1CON2bits.OCAEN = 1; //Habilita o pino para o pwm
    CCP1CON2bits.PWMRSEN = 1; //Habilita o restart automático do pwm
    CCP1CON3bits.OUTM = 0; //Modo de saída do PWM
    CCP1CON1bits.ON = 1; //Habilita o módulo CCP
}

void PWM_setDutyCycle(uint8_t new_duty_cycle){
    pwm_duty_cycle = new_duty_cycle;
    CCP1RB = (pwm_duty_cycle*(CCP1PR+1))/100;
}

uint8_t PWM_getDutyCycle(){
    return pwm_duty_cycle;
}