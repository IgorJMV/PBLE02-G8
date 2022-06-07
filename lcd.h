#ifndef _LCD_H
#define _LCD_H

#define LCD_CLEAR 1
#define LCD_FIRST_LINE 128
#define LCD_SECOND_LINE 192

void delayMS(unsigned char ms);
void pulseEnablePin();
void pushNibble(int value, int rs);
void pushByte(int value, int rs);
void lcdChar(int value);
void lcdCommand(int value);
void lcdCommand4bits(int nibble);
void lcdInit();
void lcdString(char msg[]);
void lcdData(unsigned char value);
void lcdInt(int val);

#endif	// _LCD_H