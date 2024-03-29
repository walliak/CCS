/*
 * HCSR04.h
 *
 *  Created on: 2019��7��25��
 *      Author: JOJO
 */

#ifndef SRC_HCSR04_H_
#define SRC_HCSR04_H_

#include "MSP430F5529.h"
#include "sysclock.h"
#include <lcd.h>
#include <stdio.h>
#include "motor.h"
#include "led.h"

void Car_AvoidBlock();
void pwm_catch_init();
void Left_Try();
void Right_Try();
void Open_HCSR();
void Close_HCSR();

#endif /* SRC_HCSR04_H_ */
