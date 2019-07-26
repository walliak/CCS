/*
 * Metal.c
 *
 *  Created on: 2019年7月25日
 *      Author: JOJO
 */


#include "Metal.h"
#include "motor.h"
#include "sysclock.h"

int Metal_Num = 0;

void Metal_Detect_Init ()
{
	Catch_Channel_Init();
}


void Catch_Channel_Init()
{
		P2DIR &=~BIT0;			//捕获  IO输入
		P2SEL  |= BIT0;

		TA1CTL = 0;
		TA1CTL |= TASSEL_2 + ID_0  + MC_2+ TACLR ;
		TA1CCTL1 |= CCIE + CM_2 +SCS + CAP +CCIS_0;		//下降沿捕获
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1 (void)
{
	TA1CCTL1 &=~TAIFG;
	switch(TA1IV)
	{
		case TA1IV_TACCR1:
				Metal_Num++;
				if(Metal_Num==4)
				{
					Car_Brake();
					Delayms(5000);
					TA2CCTL2 |=BIT4;	//使能超声波捕获通道中断
				}
				break;
		default:
				break;
	}

}
