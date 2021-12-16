/*
 * com.h
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */

#ifndef INC_SYSTEM_COMM_H_
#define INC_SYSTEM_COMM_H_

#include "usart.h"
#include "system/outputPwmController.h"

typedef enum TX_STATE {
    StateTxSTOPPED = 0x00,
    StateTxIDLE = 0x01,
    StateTxBUSY = 0x02,
    StateSetDataBuffer = 0x04,
    StateSetStdoBuffer = 0x08,
    StateResetDataBuffer = 0x0F,
    StateResetStdoBuffer = 0x10,
    StateTxERROR = 0x40
} txState_t;

typedef struct TX_CONTEXT {
    txState_t TxState;
    cBufferHandler_t * CurrentBuffer;
} txContext_t;

typedef enum RX_STATE {
    StateRxSTOPPED = 0x00,
    StateRxIDLE = 0x01,
    StateRxBUSY = 0x02,
    StateRxERROR = 0x40,
} rxState_t;

typedef struct RX_CONTEXT {
    rxState_t RxState;
} rxContext_t;


void txTask();
void rxTask();

void txInitialize(txContext_t * txContext) ;
void rxInitialize(rxContext_t * rxContext);

#endif /* INC_SYSTEM_COMM_H_ */
