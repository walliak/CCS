/*
 * motor.h
 *
 *  Created on: 2019年7月23日
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

	void SetMotorSpeed(char channel, int speed);			//设置速度
	void Car_Forward(int speed,int time);					//小车前进
	void Car_Left(int speed,int time);						//小车左转
	void Car_Right(int speed,int time);					//小车右转
	void Car_Spinleft(int speed,int time);					//小车左旋转
	void Car_Spinright(int speed,int time);					//小车右旋转
	void Car_Brake(void);
#endif /* SRC_MOTOR_H_ */
