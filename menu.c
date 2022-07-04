#include "menu.h"
#include "lcd.h"

const char menus[7][2][2][16] = {
    {
        {
            "<<  Alarme 1  >>",
            ""
        },
        {
            "<<   Alarm 1  >>",
            ""
        }
    },
    {
        {
            "  |Alarme Alto| ",
            "Alto: "
        },
        {
            "  |High Alarm|  ",
            "High: "
        }
    },

    {
        {
            "TESTE5",
            "TESTE6"
        },
        {
            "TESTE7",
            "TESTE8"
        }
    },

    {
        {
            "TESTE9",
            "TESTE10"
        },
        {
            "TESTE11",
            "TESTE12"
        }
    },
    {
        {
            "TESTE13",
            "TESTE14"
        },
        {
            "TESTE15",
            "TESTE16"
        }
    },
    {
        {
            "TESTE17",
            "TESTE18"
        },
        {
            "TESTE19",
            "TESTE20"
        }
    },
    {
        {
            "TESTE21",
            "TESTE22"
        },
        {
            "TESTE23",
            "TESTE24"
        }
    }
};

void updateMenu(uint8_t state) {
    lcdCommand(LCD_CLEAR);

    switch (state) {
        case ALARM1:
            lcdString(menus[ALARM1][0][0]);
            lcdCommand(LCD_SECOND_LINE);
            lcdString(menus[ALARM1][0][1]);

            lcdCommand(LCD_SECOND_LINE);
            lcdInt(getAlarmLow1());
            lcdString("|      |");
            lcdInt(getAlarmHigh1());

            lcdCommand(0xC6);
            lcdInt(readPot());
            break;

        case HIGH_ALARM1:
            lcdString(menus[HIGH_ALARM1][0][0]);
            lcdCommand(LCD_SECOND_LINE);
            lcdString(menus[HIGH_ALARM1][0][1]);


            break;

        case LOW_ALARM1:

            break;

        case HIGH_ALARM2:

            break;

        case LOW_ALARM2:

            break;

        case TIME:

            break;

        case LANGUAGE:

            break;
    }
}

void updateData(char state) {
    switch (state) {
        case ALARM1:
            lcdCommand(0xC6);
            lcdInt(readPot());
            break;

        case HIGH_ALARM1:

            break;

        case LOW_ALARM1:

            break;

        case HIGH_ALARM2:

            break;

        case LOW_ALARM2:

            break;

        case TIME:

            break;

        case LANGUAGE:

            break;
    }
}