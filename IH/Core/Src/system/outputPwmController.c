/*
 * outputPwmController.c
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */

#include "system/outputPwmController.h"

#define MAX_OUTPUT_FREQ 750000.0
#define MIN_OUTPUT_FERQ 65000.0
#define BASE_FERQ 64000000.0 * 2.0 * 32.0

float freq = 10000;
float phase = 0.5;
outputState_t outState = OutputOff;

extern HRTIM_HandleTypeDef hhrtim1;

/**
 *
 */
void outputTurnOn() {
    outputConstrainFrequency(freq);
    outState = OutputOn;
    HAL_HRTIM_SimpleBaseStart(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
    HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1);
    HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2);
    HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1);
    HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE2);
}

void outputTurnOff() {
    outState = OutputOff;
    HAL_HRTIM_SimpleBaseStop(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
    HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1);
    HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2);
    HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1);
    HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE2);
}

void outputSetFrequencyValue(float value) {
    outputState_t outST = outState;
    freq = outputConstrainFrequency(value);
    uint16_t uintFreq = BASE_FERQ / freq;
    if (outST == OutputOn) {
        outputTurnOff();
    }
    __HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_MASTER, uintFreq);
    __HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, uintFreq);
    __HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, uintFreq);
    outputSetPhaseValue(phase);
    if (outST == OutputOn) {
        outputTurnOn();
    }

}

void outputSetPhaseValue(float value) {
    uint16_t halfPeriod = __HAL_HRTIM_GETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_MASTER) / 2;
    phase = outputConstrainPhase(value);
    value = phase * (halfPeriod-32);
    __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_MASTER, HRTIM_COMPAREUNIT_1, halfPeriod + (uint16_t ) value);
    __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_MASTER, HRTIM_COMPAREUNIT_2,
            halfPeriod - (uint16_t ) (value + 0.5));
}

float outputConstrainFrequency(float value) {
    if (value > MAX_OUTPUT_FREQ) {
        value = MAX_OUTPUT_FREQ;
    } else if (value < MIN_OUTPUT_FERQ) {
        value = MIN_OUTPUT_FERQ;
    }
    return value;
}

float outputConstrainPhase(float value) {
    float period = __HAL_HRTIM_GETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
    float maxPhase = (period-147.0)/period;
    if (value > maxPhase ) {
        value = maxPhase;
    } else if (value < 1e-5) {
        value = 1e-5;
    }
    return value;
}

float outputGetFreq() {
    return (BASE_FERQ / __HAL_HRTIM_GETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_MASTER));
}

float outputGetPhase() {
    float value = __HAL_HRTIM_GETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_MASTER, HRTIM_COMPAREUNIT_1) -
    __HAL_HRTIM_GETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_MASTER, HRTIM_COMPAREUNIT_2);
    return value / ((float) __HAL_HRTIM_GETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_MASTER));
}
