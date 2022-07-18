#include "menu.h"
#include "lcd.h"
#include "var.h"
#include "adc.h"

const char menus[7][2][2][16] = {
    {
        {
            "<<  Alarme 1  >>",
            ""
        },
        {
            "<<  Alarm 1   >>",
            ""
        }
    },
    {
        {
            "|Alarme 1 Alto| ",
            "Alto: "
        },
        {
            " |High Alarm 1| ",
            "High: "
        }
    },

    {
        {
            "|Alarme 1 Baixo|",
            "Baixo: "
        },
        {
            " |Low Alarm 1|  ",
            "Low  : "
        }
    },

    {
        {
            "<<  Alarme 2  >>",
            ""
        },
        {
            "<<  Alarm 2   >>",
            ""
        }
    },
    {
        {
            "|Alarme 2 Alto|",
            "Alto: "
        },
        {
            " |High Alarm 2| ",
            "High: "
        }
    },
    {
        {
            "|Alarme 2 Baixo|",
            "Baixo: "
        },
        {
            " |Low Alarm 2|  ",
            "Low  : "
        }
    },
    {
        {
            "<<Temporizador>>",
            "Tempo: "
        },
        {
            "<<   Timer    >>",
            "Time : "
        }
    },
    {
        {
            "<<   Atraso  >>",
            "Tempo: "
        },
        {
            "<<   Delay    >>",
            "Time : "
        }
    },
    {
        {
            "<<   IDIOMA   >>",
            ""
        },
        {
            "<<  LANGUAGE  >>",
            ""
        }
    }
};

void updateMenu(uint32_t millis) {
    uint8_t state = getState();
    uint8_t language = getLanguage() % 2;

    lcdCommand(LCD_CLEAR);

    lcdString(menus[(uint8_t) state][language][0]);
    lcdCommand(LCD_SECOND_LINE);
    lcdString(menus[(uint8_t) state][language][1]);

    switch (state) {
        case ALARM1:
            lcdCommand(LCD_SECOND_LINE);
            lcdInt(getAlarmLow1());
            lcdString("|      |");
            lcdInt(getAlarmHigh1());
            break;

        case HIGH_ALARM1:
            //TODO
            break;

        case LOW_ALARM1:
            //TODO
            break;

        case ALARM2:
            lcdCommand(LCD_SECOND_LINE);
            lcdInt(getAlarmLow2());
            lcdString("|      |");
            lcdInt(getAlarmHigh2());
            break;

        case HIGH_ALARM2:
            //TODO
            break;

        case LOW_ALARM2:
            //TODO
            break;

        case TIME:
            //TODO
            break;

        case LANGUAGE:
            //TODO
            break;
    }
    updateData(millis);
}

void updateData(uint32_t millis) {
    uint8_t state = getState();
    
    switch (state) {
        case ALARM1:
            lcdCommand(0xC6);
            lcdInt(readPot());
            break;

        case ALARM2:
            lcdCommand(0xC5);
            lcdString("      ");
            lcdCommand(0xC5);
            lcdInt(readDifferential());
            break;

        case TIME:
            lcdCommand(0xC7);
            uint32_t t = getTimer();
            if(t > millis)
                lcdInt((t-millis)/1000);
            else lcdInt(0);
            break;

        case LANGUAGE:
            lcdCommand(LCD_FIRST_LINE);
            if(!getLanguage()) lcdString("<  Portugues   >");
            else lcdString("<   English    >");
            lcdCommand(LCD_SECOND_LINE);
            lcdString("                ");
            break;
    }
}

void updateLimits(void){
    uint8_t state = getState();
    
    switch(state){
    
        case HIGH_ALARM1:
            lcdCommand(0xC6);
            lcdInt(getAlarmHigh1());
            break;
        
        case LOW_ALARM1:
            lcdCommand(0xC6);
            lcdInt(getAlarmLow1());
            break;
            
        case HIGH_ALARM2:
            lcdCommand(0xC6);
            lcdInt(getAlarmHigh2());
            break;
        
        case LOW_ALARM2:
            lcdCommand(0xC6);
            lcdInt(getAlarmLow2());
            break;
            
        case SET_TIME:
            lcdCommand(0xC7);
            lcdInt((getTimer())/1000);
            break;
    }
}