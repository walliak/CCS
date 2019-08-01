/*
 * Metal.h
 *
 *  Created on: 2019Äê7ÔÂ25ÈÕ
 *      Author: JOJO
 */

#ifndef SRC_METAL_H_
#define SRC_METAL_H_

#include "MSP430F5529.h"
#include <lcd.h>
#include <stdio.h>
#include "motor.h"
#include "sysclock.h"
#include "speedcatch.h"

extern char cLedFlag;
extern int Metal_Num;
extern int iMetalDistance;
void Metal_Detect_Init ();
void Catch_Channel_Init();
void Show_Stop();
#endif /* SRC_METAL_H_ */
