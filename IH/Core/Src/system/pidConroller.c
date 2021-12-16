/*
 * pidConroller.c
 *
 *  Created on: 7 dic. 2021
 *      Author: damian
 */

#include "system/pidController.h"
#include "system/outputPwmController.h"

pid_t ejeX;
pid_t ejeY;
pid_t ejeZ;

void pidInt(pid_t* pid) {

    pid->a[0] = pid->kp + pid->ki + pid->kd;
    pid->a[1] = -pid->kp - 2 * pid->kd;
    pid->a[2] = pid->kd;

    pid->record[0] = 0;
    pid->record[1] = 0;
    pid->record[2] = 0;
}

void pidReset(pid_t* pid) {
    pid->record[0] = 0;
    pid->record[1] = 0;
    pid->record[2] = 0;
}

float pidUpdateInRuntime(pid_t* pid, float feedBack) {

    pid->record[2] = pid->record[1];
    pid->record[1] = pid->record[0];
    pid->record[0] = pid->target - feedBack;
    /*
     y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
     */
    pid->output += pid->record[0] * pid->a[0] + pid->record[1] * pid->a[1] + pid->record[2] * pid->a[2];

    /*AntiWindUp*/
    pid->output = outputConstrainFrequency(pid->output);

    return pid->output;
}
