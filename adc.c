#include "adc.h"

uint16_t readPot(void) {
    ADC1_Enable();
    ADC1_ChannelSelect(CHANNEL_POT);
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    int i;
    for (i = 0; i < 1000; i++);
    ADC1_SoftwareTriggerDisable();
    while (!ADC1_IsConversionComplete(CHANNEL_POT));
    uint16_t value = ADC1_ConversionResultGet(CHANNEL_POT);

    ADC1_Disable();

    return value;
}

int readDifferential(void) {
    uint32_t positiveValue = 0;
    uint32_t negativeValue = 0;
    for (int i = 0; i < 16; i++) {
        ADC1_Enable();
        ADC1_ChannelSelect(CHANNEL_A);
        ADC1_SoftwareTriggerEnable();
        //Provide Delay
        for (int i = 0; i < 1000; i++);
        ADC1_SoftwareTriggerDisable();
        while (!ADC1_IsConversionComplete(CHANNEL_A));
        positiveValue += ADC1_ConversionResultGet(CHANNEL_A);

        ADC1_Disable();

        ADC1_Enable();
        ADC1_ChannelSelect(CHANNEL_B);
        ADC1_SoftwareTriggerEnable();
        //Provide Delay
        for (int i = 0; i < 1000; i++);
        ADC1_SoftwareTriggerDisable();
        while (!ADC1_IsConversionComplete(CHANNEL_B));
        negativeValue += ADC1_ConversionResultGet(CHANNEL_B);

        ADC1_Disable();
    }

    return (int) (positiveValue >> 4) - (int) (negativeValue >> 4);
}