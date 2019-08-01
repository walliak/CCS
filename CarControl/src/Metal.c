/*
 * Metal.c
 *
 *  Created on: 2019年7月25日
 *      Author: JOJO
 */


#include "Metal.h"

int Metal_Num = 0;
int iMetalDistance = 0;
char cLedFlag = 0;

void Metal_Detect_Init ()
{
	Catch_Channel_Init();
}

void Catch_Channel_Init()
{
		P2DIR &=~BIT0;			//捕获  IO输入
		P2SEL |= BIT0;
		P7DIR |= BIT4;			//彩灯输出

		TA1CTL = 0;
		TA1CTL |= TASSEL_2 + ID_0  + MC_2+ TACLR ;
		TA1CCTL1 |= CCIE + CM_2 +SCS + CAP +CCIS_0;		//下降沿捕获
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1 (void)
{
	switch(TA1IV)
	{
		case TA1IV_TACCR1:
				Metal_Num++;
				iMetalDistance =(int)((lPulseTotal/390)*14.8);
				if(Metal_Num==4)
				{
					MODE = AVOID;
					Car_Brake();
					Show_Stop();
				}
				cLedFlag =1;
				break;
		default:
				break;
	}

}

void Show_Stop()
{
	P7OUT|=BIT4;
	Delay_ms(1000);
	P7OUT&=~BIT4;
	Delay_ms(1000);
	P7OUT|=BIT4;
	Delay_ms(1000);
	P7OUT&=~BIT4;
	Delay_ms(1000);
	P7OUT|=BIT4;
	Delay_ms(1000);
	P7OUT&=~BIT4;
}
