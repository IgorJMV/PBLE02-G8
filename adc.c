#include "adc.h"

uint16_t readPot(void){
    ADC1_Enable(); 
    ADC1_ChannelSelect(CHANNEL_POT);
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    int i;
    for(i=0;i <1000;i++);
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(CHANNEL_POT));
    uint16_t value = ADC1_ConversionResultGet(CHANNEL_POT);
        
    ADC1_Disable();
    
    return value;
}