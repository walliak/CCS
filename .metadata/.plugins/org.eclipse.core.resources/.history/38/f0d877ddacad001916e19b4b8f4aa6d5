/*
 * sysclock.h
 *
 *  Created on: 2019年7月19日
 *      Author: Think
 */

#ifndef SRC_SYSCLOCK_H_
#define SRC_SYSCLOCK_H_

//延时函数的定义，使用了系统自带的精确延时
#define CPU_CLOCK       25000000		//时钟大于1M
#define Delay_us(us)    __delay_cycles(CPU_CLOCK/1000000*(us))
#define Delay_ms(ms)    __delay_cycles(CPU_CLOCK/1000*(ms))

void SetVcoreUp (unsigned int level);
void CLK_Init(void);
#endif /* SRC_SYSCLOCK_H_ */
