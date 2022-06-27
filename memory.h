/* 
 * File:   memory.h
 * Author: igorjmv
 *
 * Created on June 19, 2022, 5:00 PM
 */

#ifndef _MEMORY_H_
#define	_MEMORY_H_

#include "mcc_generated_files/i2c2.h"

    uint8_t writeMem(uint8_t address, uint8_t* pData, uint16_t ncount);
    uint8_t readMem(uint16_t address, uint8_t *pData, uint16_t nCount);

#endif	/* _MEMORY_H_ */

