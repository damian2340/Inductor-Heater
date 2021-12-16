/*
 * CircularBufferHandler.h
 *
 *  Created on: 8 mar. 2021
 *      Author: damian
 */

#ifndef SRC_SYSTEM_CIRCULARBUFFER_H_
#define SRC_SYSTEM_CIRCULARBUFFER_H_
#include "stm32f3xx_hal.h"

typedef enum {
    BufferError = -0x1,
    BufferIdle  =  0x0,
    BufferBusy  =  0x1
} BufferStatus;

typedef struct cBufferHandler {
    BufferStatus bufferStatus;
    uint8_t* bufferPtr;
    size_t dataStarOffset;
    size_t dataStopOffset;
    size_t dataAvailable;
    size_t length;
}cBufferHandlerTypedef;

void cBufferInit(cBufferHandlerTypedef * cbh, uint8_t *buffer, size_t size);
uint8_t cBHgetData(cBufferHandlerTypedef * cbh);
BufferStatus cBHsetData(cBufferHandlerTypedef* cbh,uint8_t data);
BufferStatus cBHgetBufferStatus(cBufferHandlerTypedef* cbh);



#endif /* SRC_SYSTEM_CIRCULARBUFFER_H_ */
