/*
 * CircularBuffer.cpp
 *
 *  Created on: 8 mar. 2021
 *      Author: damian
 */

#include "system/cBufferHandler.h"

/****
 *
 */
void cBufferInit(cBufferHandlerTypedef * cbh, uint8_t * buffer, size_t size) {
    if (cbh != NULL) {
        if (buffer != NULL) {
            cbh->bufferPtr = buffer;
            cbh->length = size;
            cbh->dataStarOffset = 0;
            cbh->dataStopOffset = 0;
            cbh->dataAvailable = 0;
            cbh->bufferStatus = BufferIdle;
        } else {
            cbh->bufferStatus = BufferError;
        }
    }
}

uint8_t cBHgetData(cBufferHandlerTypedef * cbh) {
    if ((cbh->bufferStatus == BufferError) || (cbh->bufferStatus == BufferBusy)) {
        cbh->bufferStatus = BufferError;
        return 0;
    }
    cbh->bufferStatus = BufferBusy;
    uint8_t data = cbh->bufferPtr[cbh->dataStarOffset];

    if (cbh->dataStarOffset < cbh->length - 1) {
        cbh->dataAvailable--;
        cbh->dataStarOffset++;
    } else {
        cbh->dataStarOffset = 0;
    }
    cbh->bufferStatus = BufferIdle;
    return data;
}

BufferStatus cBHsetData(cBufferHandlerTypedef* cbh, uint8_t data) {
    if (((cbh->bufferStatus & BufferError) == BufferError) || ((cbh->bufferStatus & BufferBusy) == BufferBusy)) {
        cbh->bufferStatus = BufferError;
        return BufferError;
    }

        cbh->bufferStatus = BufferBusy;

        cbh->bufferPtr[cbh->dataStopOffset] = data;
        if (cbh->dataStopOffset < cbh->length - 1) {
            cbh->dataAvailable++;
            cbh->dataStopOffset++;
        } else {
            cbh->dataStopOffset = 0;
        }
        cbh->bufferStatus = BufferIdle;
    return cbh->bufferStatus;

}

BufferStatus cBHgetBufferStatus(cBufferHandlerTypedef* cbh) {
    return cbh->bufferStatus;
}

