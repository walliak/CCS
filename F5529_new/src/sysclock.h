/*
 * sysclock.h
 *
 *  Created on: 2019��7��19��
 *      Author: Think
 */

#ifndef SRC_SYSCLOCK_H_
#define SRC_SYSCLOCK_H_

//��ʱ�����Ķ��壬ʹ����ϵͳ�Դ��ľ�ȷ��ʱ
#define CPU_CLOCK       25000000		//ʱ�Ӵ���1M
#define Delay_us(us)    __delay_cycles(CPU_CLOCK/1000000*(us))
#define Delay_ms(ms)    __delay_cycles(CPU_CLOCK/1000*(ms))

void SetVcoreUp (unsigned int level);
void CLK_Init(void);
#endif /* SRC_SYSCLOCK_H_ */
