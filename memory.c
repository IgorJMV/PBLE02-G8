#include "mcc_generated_files/i2c2.h"
//#include "Utils.h"

#define MEMADDR 0x50

uint8_t writeMem(uint16_t address, uint8_t* pData, uint16_t ncount) {
    I2C2_MESSAGE_STATUS pstatus;

    uint8_t pd[2 + ncount];

    uint8_t* data = pData;

    pd[0] = address >> 8;
    pd[1] = address & 0xFF;
    for (uint16_t i = 0; i < ncount; i++) {
        pd[i + 2] = *data;
        data++;
    }
    while (pstatus != I2C2_MESSAGE_FAIL) {
        I2C2_MasterWrite(pd, 3, MEMADDR, &pstatus);

        while (pstatus == I2C2_MESSAGE_PENDING);
        if (pstatus == I2C2_MESSAGE_COMPLETE) break;
    }

    return pstatus;

}

#define MCHP24AA512_RETRY_MAX       100  // define the retry count
#define MCHP24AA512_DEVICE_TIMEOUT  50   // define slave timeout 

uint8_t readMem(int16_t address, uint8_t *pData, uint16_t nCount) {

    I2C2_MESSAGE_STATUS status;
    uint8_t writeBuffer[3];

    writeBuffer[0] = address >> 8;
    writeBuffer[1] = address & 0xFF;


    while (status != I2C2_MESSAGE_FAIL) {
        I2C2_MasterWrite(writeBuffer, 2, MEMADDR, &status);
        while (status == I2C2_MESSAGE_PENDING);
        if (status == I2C2_MESSAGE_COMPLETE) break;
    }

    while (status != I2C2_MESSAGE_FAIL) {
        I2C2_MasterRead(pData, 1, MEMADDR, &status);

        while (status == I2C2_MESSAGE_PENDING);
        if (status == I2C2_MESSAGE_COMPLETE)
            break;
    }
    return status;

}