/*
 * motor.c
 *
 *  Created on: 2019年7月23日
 *      Author: Think
 */


#include "motor.h"

int L_speed = 15,R_speed = 15,Turn_time = 10;
void PWM_Init(void)
{
	TA0CTL = TASSEL__SMCLK+MC__UP+TACLR;

	TA0CCR0 = 1500;				//PWM频率 16.67KHZ

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
 *				PWM输出引脚设置
 * P1.2 ->TA0.1
 * P1.3 ->TA0.2
 * P1.4 ->TA0.3
 * P1.5 ->TA0.4
 *
 * 				电机方向引脚设置
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
	P1DIR |=(BIT2+BIT3+BIT4+BIT5);//定时器A0，P1.2,P1.3,P1.4,P1.5复用输出
	P1SEL |=(BIT2+BIT3+BIT4+BIT5);

	P2DIR |=(BIT0+BIT2+BIT4+BIT5);
	P4DIR |=(BIT0+BIT1+BIT2+BIT3);
}




/*************************************************************************
 * 			电机方向控制
 * xx_Forward  电机正转	前进
 * xx_Backward 电机反转	后退
 * xx_stop	      电机停止
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
	TA0CCR1 = (int)(sPWM*0.99);
}

void L2_SetPWM(int sPWM)
{
	TA0CCR2 =(int)(sPWM*1.024) ;
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
 * 						运动函数
 * channel 1 左部轮  0 右部轮
 * speed   使用0~100的整数
 *
 * void SetMotorSpeed(char channel, char Speed)			//设置速度
 * void Car_Forward(char speed,int time)				//小车前进
 * void Car_Left(char speed,int time)					//小车左转
 * void Car_Right(char speed,int time)					//小车右转
 * void Car_Spinleft(char speed,int time)				//小车左旋转
 * void Car_Spinleft(char speed,int time)				//小车右旋转
 * void Car_Brake(void)
 *********************************************************************************/

void SetMotorSpeed(char channel, int speed)			//设置速度
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

	sPWM = 900+fabs(speed)*6;
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

void Car_Forward(int speed,int time)				//小车前进
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
	Car_Brake();
}

void Car_Turn(int time)	//小车转弯，可左右转
{
	SetMotorSpeed(1,L_speed);
	SetMotorSpeed(0,R_speed);
	Mydelayms(time);
	Car_Brake();
}

void Car_Left(int speed,int time)					//小车左转
{
	SetMotorSpeed(1,0);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
	Car_Brake();
}
void Car_Right(int speed,int time)					//小车右转
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,0);
	Mydelayms(time);
	Car_Brake();
}

void Car_Backward(int speed,int time)				//小车后退
{
	SetMotorSpeed(1,-speed);
	SetMotorSpeed(0,-speed);
	Mydelayms(time);
	Car_Brake();
}

void Car_Spinleft(int speed,int time)				//小车左旋转
{
	SetMotorSpeed(1,speed);
	SetMotorSpeed(0,-speed);
	Mydelayms(time);
	Car_Brake();
}

void Car_Spinright(int speed,int time)				//小车右旋转
{
	SetMotorSpeed(1,-speed);
	SetMotorSpeed(0,speed);
	Mydelayms(time);
	Car_Brake();
}

void Car_Brake(void)
{
	L1_Stop();
	L2_Stop();
	R1_Stop();
	R2_Stop();
}
