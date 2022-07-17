#include "serial.h"
#include "lcd.h"
#include "var.h"
#include "menu.h"
#include "statemachine.h"
#include "mcc_generated_files/uart1.h"

#define BitRead(value, bit) (((value) >> (bit)) & 0x01)
#define startCommand '$'
#define commandSize 8

static uint8_t lstAS = 0;

const char msgAlarm[5][2][19] = {
    {
        "ALARME 1 BAIXO em ",
        "ALARM 1 LOW in "
    },
    {
        "ALARME 1 ALTO em ",
        "ALARM 1 HIGH in "
    },
    {
        "ALARME 2 BAIXO em ",
        "ALARM 2 LOW in "
    },
    {
        "ALARME 2 ALTO em ",
        "ALARM 2 HIGH in "
    },
    {
        "TEMPORIZADOR em ",
        "TIMER in "
    }
};

void serialUpdate(uint32_t millis) {
    uint8_t a = 0;
    uint8_t index = 0;

    char read[commandSize];

    if (UART1_IsRxReady())
        for (unsigned long i = 0; i < 10; i++)
            for (volatile unsigned int l = 0; l < 787; l++);

    while (UART1_IsRxReady()) {
        if (index < commandSize)
            read[index] = UART1_Read();
        index++;
        a = 1;
    }
    if (!a) return;


    if (index != commandSize)
        return;

    if (read[0] != startCommand)
        return;


    for (uint8_t i = 0; i < commandSize; i++)
        UART1_Write(read[i]);
    UART1_Write('\n');
    uint32_t value;

    switch (read[1]) {
        case 'A':

            value = (read[4] - 48)*1000 + (read[5] - 48)*100 + (read[6] - 48)*10 + (read[7] - 48);

            if (read[2] == 'H') {
                if (read[3] == '1') {
                    setAlarmHigh1(value);
                } else if (read[3] == '2') {
                    setAlarmHigh2(value);
                }
            } else if (read[2] == 'L') {
                if (read[3] == '1') {
                    setAlarmLow1(value);
                } else if (read[3] == '2') {
                    setAlarmLow2(value);
                }
            }

            break;

        case 'T':
            value = (read[2] - 48)*100000 + (read[3] - 48)*10000 + (read[4] - 48)*1000 + (read[5] - 48)*100 + (read[6] - 48)*10 + (read[7] - 48);

            setTimer(value * 1000 + millis);

            break;

        case 'L':
            if (read[7] == 'P') {
                setLanguage(0);
            } else if (read[7] == 'E') {
                setLanguage(1);
            }
            break;
    }
    statemachine_update(0, millis);
}

void serialAlarm(uint8_t a, uint32_t millis) {
    uint8_t l = getLanguage() % 2;

    while (!UART1_IsTxReady());

    if (BitRead(a, 0) != BitRead(lstAS, 0) && BitRead(a, 0)) {
        uint8_t i = 0;
        while (msgAlarm[0][l][i] != 0) {
            UART1_Write(msgAlarm[0][l][i]);
            i++;
        }
        UART1_Write(((millis / 1000) / 1000) % 10 + 48);
        UART1_Write(((millis / 1000) / 100) % 10 + 48);
        UART1_Write(((millis / 1000) / 10) % 10 + 48);
        UART1_Write(((millis / 1000) / 1) % 10 + 48);
        UART1_Write('\n');
    }

    if (BitRead(a, 1) != BitRead(lstAS, 1) && BitRead(a, 1)) {
        uint8_t i = 0;
        while (msgAlarm[1][l][i] != 0) {
            UART1_Write(msgAlarm[1][l][i]);
            i++;
        }
        UART1_Write(((millis / 1000) / 1000) % 10 + 48);
        UART1_Write(((millis / 1000) / 100) % 10 + 48);
        UART1_Write(((millis / 1000) / 10) % 10 + 48);
        UART1_Write(((millis / 1000) / 1) % 10 + 48);
        UART1_Write('\n');
    }

    if (BitRead(a, 2) != BitRead(lstAS, 2) && BitRead(a, 2)) {
        uint8_t i = 0;
        while (msgAlarm[2][l][i] != 0) {
            UART1_Write(msgAlarm[2][l][i]);
            i++;
        }
        UART1_Write(((millis / 1000) / 1000) % 10 + 48);
        UART1_Write(((millis / 1000) / 100) % 10 + 48);
        UART1_Write(((millis / 1000) / 10) % 10 + 48);
        UART1_Write(((millis / 1000) / 1) % 10 + 48);
        UART1_Write('\n');
    }

    if (BitRead(a, 3) != BitRead(lstAS, 3) && BitRead(a, 3)) {
        uint8_t i = 0;
        while (msgAlarm[3][l][i] != 0) {
            UART1_Write(msgAlarm[3][l][i]);
            i++;
        }
        UART1_Write(((millis / 1000) / 1000) % 10 + 48);
        UART1_Write(((millis / 1000) / 100) % 10 + 48);
        UART1_Write(((millis / 1000) / 10) % 10 + 48);
        UART1_Write(((millis / 1000) / 1) % 10 + 48);
        UART1_Write('\n');
    }

    if (BitRead(a, 4) != BitRead(lstAS, 4) && BitRead(a, 4)) {
        uint8_t i = 0;
        while (msgAlarm[4][l][i] != 0) {
            UART1_Write(msgAlarm[4][l][i]);
            i++;
        }
        UART1_Write(((millis / 1000) / 1000) % 10 + 48);
        UART1_Write(((millis / 1000) / 100) % 10 + 48);
        UART1_Write(((millis / 1000) / 10) % 10 + 48);
        UART1_Write(((millis / 1000) / 1) % 10 + 48);
        UART1_Write('\n');
    }
    lstAS = a;
}