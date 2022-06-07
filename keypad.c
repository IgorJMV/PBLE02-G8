#include "keypad.h"

kpType kpRead(void){
    ADC1_Enable(); 
    ADC1_ChannelSelect(CHANNEL_KP);
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    int i;
    for(i=0;i <1000;i++);
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(CHANNEL_KP));
    unsigned int value = ADC1_ConversionResultGet(CHANNEL_KP);
        
    ADC1_Disable();
    
    if(value >= 80 && value < 97) return B1;
    else if(value >= 97 && value < 120) return B2;
    else if(value >= 120 && value < 140) return B4;
    else if(value >= 140 && value < 200) return B3;
    else if(value >= 200) return B5;
    
    return NOTHING;
}

bool isKpPressed(kpType key){
    return (key == kpRead()) ? true : false;
}