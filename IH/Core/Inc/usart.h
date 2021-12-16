/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE BEGIN Private defines */
#define DMA_TX_BUFFER_SIZE 256
#define DMA_RX_BUFFER_SIZE 64
#define SDIN_BUFFER_SIZE 256

typedef enum State {
    BUFFER_idle = 0, BUFFER_busy
} BufferStateTypeDef;

typedef enum BUFFER_TYPE {
    dataBufferType, sdoutBufferType, errorBufferType, sdinBufferType
} bufferType_t;

typedef struct C_BUFFER_HANDLER {
    uint8_t * BufferStart_p;                // marca el inicio del buffer
    size_t BufferLength;                // indica la cantidad de datos en el buffer
    size_t BufferStartOffset; /* El encargado de cambiar el offset es la interrupción sobre el final de la transmisión*/
    size_t BufferEndOffset; /* Es la posición donde se va a escribir el próximo dato */
    size_t ToSend;
    size_t BufferNextStartOffset;
    size_t BufferDataLength; /* Usado para indicarle al modulo DMA cuantos datos se van a enviar */
    size_t DataSize;
    BufferStateTypeDef BufferState;
    bufferType_t Type;
} cBufferHandler_t;

/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void TransmitionStart(cBufferHandler_t*);
HAL_StatusTypeDef sendChar(char ch);
void receptionStart();
void uartSetReady();
void uartOnReceive();
HAL_UART_StateTypeDef uartReceive();
uint8_t* uartGetData();
uint8_t uartIsReady();
BufferStateTypeDef sdinIsBusy();
void stdinSetter(BufferStateTypeDef state);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
