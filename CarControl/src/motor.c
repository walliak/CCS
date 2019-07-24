/*
 * motor.c
 *
 *  Created on: 2019��7��23��
 *      Author: Think
 */

#include "MSP430F5529.h"
#include "motor.h"


void PWM_Init(void)
{
	TA0CTL = TASSEL__SMCLK+MC__UP+TACLR;

	TA0CCR0 = 1500;				//PWMƵ�� 16.67KHZ

	TA0CCTL1=OUTMOD_7;
	TA0CCR1 = 1250;

	TA0CCTL2=OUTMOD_7;
	TA0CCR2 = 1250;

	TA0CCTL3=OUTMOD_7;
	TA0CCR3= 1250;

	TA0CCTL4=OUTMOD_7;
	TA0CCR4 = 1250;
}

/***************************************************************************
 *				PWM�����������
 * P1.2 ->TA0.1
 * P1.3 ->TA0.2
 * P1.4 ->TA0.3
 * P1.5 ->TA0.4
 *
 * 				���������������
 * P2.0 ->L1.IN1
 * P2.2 ->L1.IN2
 *
 * P2.4 ->L2.IN1
 * P2.5 ->L2.IN2
 *
 * P4.0 ->R1.IN2
 * P4.1 ->R1.IN1
 *
 * P4.2 ->R2.IN2
 * P4.3 ->R2.IN1
 ****************************************************************************/
void MotorPort_Init()
{
	P1DIR |=(BIT2+BIT3+BIT4+BIT5);//��ʱ��A0��P1.2,P1.3,P1.4,P1.5�������
	P1SEL |=(BIT2+BIT3+BIT4+BIT5);

	P2DIR |=(BIT0+BIT2+BIT4+BIT5);
	P4DIR |=(BIT0+BIT1+BIT2+BIT3);
}




/*************************************************************************
 * 			����������
 * xx_Forward  �����ת	ǰ��
 * xx_Backward �����ת	����
 * xx_stop	      ���ֹͣ
 *
 *************************************************************************/
void L1_Backward(void)
{
	P2OUT |=BIT0;
	P2OUT &=~BIT2;
}

void L1_Forward(void)
{
	P2OUT &=~BIT0;
	P2OUT |=BIT2;
}

void L1_Stop(void)
{
	P2OUT &=~BIT0;
	P2OUT &=~BIT2;
}

void L2_Backward(void)
{
	P2OUT |=BIT4;
	P2OUT &=~BIT5;
}

void L2_Forward(void)
{
	P2OUT &=~BIT4;
	P2OUT |=BIT5;
}

void L2_Stop(void)
{
	P2OUT &=~BIT4;
	P2OUT &=~BIT5;
}

void R1_Backward(void)
{
	P4OUT |=BIT0;
	P4OUT &=~BIT1;
}

void R1_Forward(void)
{
	P4OUT &=~BIT0;
	P4OUT |=BIT1;
}

void R1_Stop(void)
{
	P4OUT &=~BIT0;
	P4OUT &=~BIT1;
}

void R2_Backward(void)
{
	P4OUT |=BIT2;
	P4OUT &=~BIT3;
}

void R2_Forward(void)
{
	P4OUT &=~BIT2;
	P4OUT |=BIT3;
}

void R2_Stop(void)
{
	P4OUT &=~BIT2;
	P4OUT &=~BIT3;
}

void L1_SetPWM(int sPWM)
{
	TA0CCR1 = sPWM;
}

void L2_SetPWM(int sPWM)
{
	TA0CCR2 = sPWM;
}

void R1_SetPWM(int sPWM)
{
	TA0CCR3 = sPWM;
}

void R2_SetPWM(int sPWM)
{
	TA0CCR4 = sPWM;
}



/**********************************************************************************
 * 						�˶�����
 * channel 1 ����  0 �Ҳ���
 * speed   ʹ��0~100������
 *
 * void SetMotorSpeed(char channel, char Speed)			//�����ٶ�
 * void Car_Forward(char speed,int time)				//С��ǰ��
 * void Car_Left(char speed,int time)					//С����ת
 * void Car_Right(char speed,int time)					//С����ת
 * void Car_Spinleft(char speed,int time)				//С������ת
 * void Car_Spinleft(char speed,int time)				//С������ת
 * void Car_Brake(void)
 *********************************************************************************/




void SetMotorSpeed(char channel, int speed)			//�����ٶ�
{
	int sPWM;

	if(speed>100)
		{
			speed = 100;
		}
	if(speed<(-100))
		{
			speed = -100;
		}

	sPWM = fabs(speed)*15;
	switch(channel)
	{
		case 0://R1,R2
			R1_SetPWM(sPWM);
			R2_SetPWM(sPWM);
			if(speed>=0)
			{
				R1_Forward();
				R2_Forward();
			}
			if(speed<0)
			{
				R1_Backward();
				R2_Backward();
			}
			break;
		case 1://L1,L2
			L1_SetPWM(sPWM);
			L2_SetPWM(sPWM);
			if(speed>=0)
			{
				L1_Forward();
				L2_Forward();
			}
			if(speed<0)
			{
				L1_Backward();
				L2_Backward();
			}
			break;
	}
}

void Car_Forward(int speed,int time)				//С��ǰ��
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
}

void Car_Left(int speed,int time)					//С����ת
{
	SetMotorSpeed(1,0);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
}

void Car_Right(int speed,int time)					//С����ת
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,0);
	Mydelayms(time);
}

void Car_Backward(int speed,int time)				//С������
{
	SetMotorSpeed(1,-speed);
	SetMotorSpeed(0,-speed);
	Mydelayms(time);
}

void Car_Spinleft(int speed,int time)				//С������ת
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,-speed);
	Mydelayms(time);
}

void Car_Spinright(int speed,int time)				//С������ת
{
	SetMotorSpeed(1,-speed);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
}

void Car_Brake(void)
{
	L1_Stop();
	L2_Stop();
	R1_Stop();
	R2_Stop();
}