/*
 * blacksearch.h
 *
 *  Created on: 2019Äê7ÔÂ24ÈÕ
 *      Author: Think
 */

#ifndef SRC_BLACKSEARCH_H_
#define SRC_BLACKSEARCH_H_
#include "MSP430F5529.h"
#include "motor.h"

#define READ_ALL (P8IN&BIT1)+(P8IN&BIT2)
#define FLAG_LEFT  BIT1
#define FLAG_RIGHT BIT2

void SearchPort_Init();
void Car_SearchBlack();

#endif /* SRC_BLACKSEARCH_H_ */
