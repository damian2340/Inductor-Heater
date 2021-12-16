/*
 * com.c
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"
#include "system/outputPwmController.h"
#include "system/comm.h"

extern cBufferHandler_t TxbufferHandler;
extern bufferType_t CurrentBufferType;
extern uint8_t stdInBuffer[SDIN_BUFFER_SIZE];
extern float freq;
extern float phase;

void txTask() {
    static txState_t requestState = StateTxIDLE;
    static txContext_t txContext = { .TxState = StateTxSTOPPED, };

    switch (txContext.TxState) {
        case StateTxSTOPPED:
            txInitialize(&txContext);
            break;
        case StateTxIDLE:
            if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
                txContext.TxState = requestState;
                if (txContext.TxState == StateTxIDLE) {
                    if (txContext.CurrentBuffer->BufferDataLength > 0) {
                        TransmitionStart(txContext.CurrentBuffer);
                    }
                } else {
                    requestState = StateTxIDLE;
                }
            }
            break;
        case StateTxBUSY:
            break;
        case StateSetDataBuffer:
            if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
                txContext.TxState = StateTxIDLE;
            }
            break;
        case StateSetStdoBuffer:
            if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
                txContext.CurrentBuffer = &TxbufferHandler;
                CurrentBufferType = sdoutBufferType;
                txContext.TxState = StateTxIDLE;
            }
            break;
        case StateResetDataBuffer:
            if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
                txContext.TxState = StateTxIDLE;
            }
            break;
        case StateResetStdoBuffer:
            if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
                txContext.TxState = StateTxIDLE;
            }
            break;
        case StateTxERROR:
            break;
    }
}

void rxTask() {
    static rxContext_t rxContext = { .RxState = StateRxSTOPPED, };

    switch (rxContext.RxState) {
        case StateRxSTOPPED: {
            rxInitialize(&rxContext);
        }
            break;
        case StateRxIDLE: {
            if (sdinIsBusy() == BUFFER_busy) {
                rxContext.RxState = StateRxBUSY;
            }
        }
            break;
        case StateRxBUSY: {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            switch (stdInBuffer[0]) {
                case 'S':
                case 's':
                    if (stdInBuffer[2] == 'A' || stdInBuffer[2] == 'a') {
                        outputTurnOn();
                    } else if (stdInBuffer[2] == 'O' || stdInBuffer[2] == 'o') {
                        outputTurnOff();
                    }
                    break;
                case 'F':
                case 'f':
                    freq = atof((char const *) (stdInBuffer + 1));
                    outputSetFrequencyValue(freq);
                    printf("Frecuencia: %5.2f kHz\n\r", outputGetPhase()/1000.0);
                    break;
                case 'P':
                case 'p':
                    phase = atof((char const *) (stdInBuffer + 1));
                    outputSetPhaseValue(phase);
                    printf("Fase: %5.2f%% del periodo\n\r", outputGetPhase()*100.0);
                    break;
                default: {
                    printf("Comando Desconocido\n\r");
                }
            }
            printf("Comando recivido: %s \n\r", stdInBuffer);
            stdinSetter(BUFFER_idle);
            rxContext.RxState = StateRxIDLE;
        }
            break;
        case StateRxERROR: {
        }
            break;
    }
}

void txInitialize(txContext_t * txContext) {
    txContext->TxState = StateTxIDLE;
    txContext->CurrentBuffer = &TxbufferHandler;
}

void rxInitialize(rxContext_t * rxContext) {
    rxContext->RxState = StateRxIDLE;
}
