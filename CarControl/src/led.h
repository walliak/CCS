/*
 * led.h
 *
 *  Created on: 2019��7��13��
 *      Author: Think
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_


#define LED1_HIGH (P1OUT |=BIT0)
#define LED1_LOW  (P1OUT &=~BIT0)
#define LED2_HIGH (P4OUT |=BIT7)
#define LED2_LOW  (P4OUT &=~BIT7)
	void LedInit(void);





#endif /* SRC_LED_H_ */
