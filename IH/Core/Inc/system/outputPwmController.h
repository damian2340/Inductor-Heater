/*
 * outputPwmController.h
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */

#ifndef INC_SYSTEM_OUTPUTPWMCONTROLLER_H_
#define INC_SYSTEM_OUTPUTPWMCONTROLLER_H_

#include "hrtim.h"

typedef enum outputState{
    OutputOff   = 0x0,
    OutputOn    = 0x1,
    OutputError = 0x2
}outputState_t;

void outputTurnOn();
void outputTurnOff();
void outputSetPhaseValue( float value);
void outputSetFrequencyValue(float value);
float outputConstrainFrequency(float value);
float outputConstrainPhase(float value);
float outputGetFreq();
float outputGetPhase();
#endif /* INC_SYSTEM_OUTPUTPWMCONTROLLER_H_ */
