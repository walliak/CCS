/*
 * my_ADC.h
 *
 *  Created on: 2019年7月9日
 *      Author: JOJO
 */

#ifndef SRC_MY_ADC_H_
#define SRC_MY_ADC_H_

#include "MSP430F5529.h"

#define N_ADC 12 //采样个数

int adc12_init();
void Start_ADC12IT();
void Stop_ADC12IT();
void Car_SearchLight();
int  filter();

#endif /* SRC_MY_ADC_H_ */
