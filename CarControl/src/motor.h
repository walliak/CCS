/*
 * motor.h
 *
 *  Created on: 2019��7��23��
 *      Author: Think
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_
#include "sysclock.h"
#include "Math.h"
#include "sysclock.h"
	void PWM_Init(void);
	void MotorPort_Init();

	void L1_Forward(void);
	void L1_Backward(void);
	void L1_Stop(void);
	void L2_Forward(void);
	void L2_Backward(void);
	void L2_Stop(void);
	void R1_Forward(void);
	void R1_Backward(void);
	void R1_Stop(void);
	void R2_Forward(void);
	void R2_Backward(void);
	void R2_Stop(void);

	void SetMotorSpeed(char channel, int speed);			//�����ٶ�
	void Car_Forward(int speed,int time);					//С��ǰ��
	void Car_Left(int speed,int time);						//С����ת
	void Car_Right(int speed,int time);					//С����ת
	void Car_Spinleft(int speed,int time);					//С������ת
	void Car_Spinright(int speed,int time);					//С������ת
	void Car_Brake(void);
#endif /* SRC_MOTOR_H_ */