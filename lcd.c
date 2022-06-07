#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"
#include "lcd.h"

//fun√ß√µes de bit
#define BitSet(arg,bit) ((arg) |= (1<<bit))
#define BitClr(arg,bit) ((arg) &= ~(1<<bit)) 
#define BitFlp(arg,bit) ((arg) ^= (1<<bit)) 
#define BitTst(arg,bit) ((arg) & (1<<bit)) 



void delayUS(unsigned char ms) {
    volatile unsigned int i;
    for (; ms > 0; ms--);
    {
        for (i = 0; i < 30; i++);
    }
}

void delayMS(unsigned char ms) {
    volatile unsigned int i;
    for (; ms > 0; ms--);
    {
        for (i = 0; i < 30000; i++);
    }
}

void pulseEnablePin() {
    EN_SetHigh();
    EN_SetLow();
}

void pushNibble(int value, int rs) {
    if (BitTst(value, 4)) D4_SetHigh();
    else D4_SetLow();
    if (BitTst(value, 5)) D5_SetHigh();
    else D5_SetLow();
    if (BitTst(value, 6)) D6_SetHigh();
    else D6_SetLow();
    if (BitTst(value, 7)) D7_SetHigh();
    else D7_SetLow();
    if (rs) RS_SetHigh();
    else RS_SetLow();
    pulseEnablePin();
}

void pushByte(int value, int rs) {
    int val_lower = (value << 4) &0xf0;
    int val_upper = value & 0xF0;
    pushNibble(val_upper, rs);
    pushNibble(val_lower, rs);
}

void lcdChar(int value) {
    //let pushByte worry about the intricacies of Enable, nibble order.
    pushByte(value, 1);
    delayUS(40);
}

void lcdCommand(int value) {
    pushByte(value, 0);
    delayUS(40);
    if (value == 0x01){
        delayMS(2);
    }
}

void lcdCommand4bits(int nibble) {
    pushNibble(nibble << 4, 0);
}

void lcdInit() {
    EN_SetDigitalOutput();
    RS_SetDigitalOutput();
    D4_SetDigitalOutput();
    D5_SetDigitalOutput();
    D6_SetDigitalOutput();
    D7_SetDigitalOutput();
    RW_SetLow();

    delayMS(15); //15ms

    //The first 4 nibbles and timings are not in my DEM16217 SYH datasheet, but apparently are HD44780 standard...
    lcdCommand4bits(0x03);
    delayMS(1);
    lcdCommand4bits(0x03);
    delayMS(1); //100us
    lcdCommand4bits(0x03);
    delayMS(5);

    // needed by the LCDs controller
    //this being 2 sets up 4-bit mode.
    lcdCommand4bits(0x02);
    delayMS(1);

    //configura o display
    lcdCommand(0x28); //4bits, 2 linhas, 5x8
    lcdCommand(0x06); //modo incremental
    lcdCommand(0x0c); //display e cursor on, com blink
    lcdCommand(0x03); //zera tudo
    lcdCommand(0x80); //posiÁ„o inicial
    lcdCommand(0x01); //limpar display
}

void lcdString(char msg[]) {
    unsigned char i = 0; //fancy int.  avoids compiler warning when comparing i with strlen()'s uint8_t
    while (msg[i]) {
        lcdChar(msg[i]);
        i++;
    }
}

void lcdData(unsigned char value) {
    pushByte(value, 1);
    delayMS(2);
}

void lcdInt(int val) {
    if (val < 0) {
        val = val * (-1);
        lcdData('-');
    }
    //lcdData((val / 10000) % 10 + 48);
    lcdData((val / 1000) % 10 + 48);
    lcdData((val / 100) % 10 + 48);
    lcdData((val / 10) % 10 + 48);
    lcdData((val / 1) % 10 + 48);

}