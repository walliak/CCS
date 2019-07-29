/*
 * SpeedCatch.c
 *
 *  Created on: 2019��7��25��
 *      Author: JOJO
 */


#include "SpeedCatch.h"

float  speed ;
long lPulseTotal =0;
void Speed_Catch_Init ()
{
	SpeedCatch_Channel_Init();
}

void SpeedCatch_Channel_Init()
{
		P3DIR &=~BIT5;			//����  IO����
		P3SEL  |= BIT5;

		TBCTL = 0;
		TBCTL |= TBSSEL_2 + ID_0  + MC_2+ TACLR ;
		TBCCTL5 |= CCIE + CM_1 +SCS + CAP +CCIS_0;		//�½��ز���
}


#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer0_B1 (void)
{
	static long Pulse_Num = 0;
	static long Time = 0;

	switch(TBIV)
	{
		case TB0IV_TBCCR5 :
				Pulse_Num++;
				lPulseTotal++;
				if(Pulse_Num == 0)															//���ָտ�ʼ��ת
					Time = 0;
				if(Pulse_Num ==200)			//��Լ�߰�Ȧ��һ���ٶ�
				{
					speed = (200/390)*(1000*14.8) / (Time*2.621);   			// ��λ: cm/s
					Time = 0;
					Pulse_Num=0;
				}
				break;

		case TB0IV_TBIFG:
				Time++;
				break;

		default:
				break;
	}

}