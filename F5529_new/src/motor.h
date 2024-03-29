/*
 * motor.h
 *
 *  Created on: 2019年7月14日
 *      Author: JOJO
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_


/**************************************变量定义********************************/

#define DISTANCE 110					//两定滑轮的间距
#define CIRCUMFERENCE_LEFT 5.1			//左滑轮的周长
#define CIRCUMFERENCE_RIGHT 5.1			//右滑轮的周长
#define PI 3.1415
#define N1	100							//圆的点数
#define N2	80							//直线的点数
#define INITSPEED	29766				//定时器重载值
#define OPENTIMA       TA0CTL |=TAIE
#define CLOSETIMA	   TA0CTL &=~TAIE

extern int P_x1,P_y1,P_x2,P_y2,P_r;
extern char function;

struct Point array_1[N1+1];
struct Point array_2[N2];

/************************************枚举及结构体定义******************************************/

//电机旋转方向（正，反）
typedef enum {
	FORWAED = 0,
	REVERSE
}Dir;

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {ZERO,FIR,SEC,TIR,FOR} Quadrant;

/**************************************
 * P4.0	->UP
 * P4.1 ->DOWN
 * P4.2 ->RIGHT
 **************************************/
//#define READ_UP 	(P4IN&BIT0)
//#define READ_DOWN 	(P4IN&BIT1)
//#define READ_RIGHT 	(P4IN&BIT2)
//#define	READ_U_R	((P4IN&BIT0)+(P4IN&BIT2))
//#define READ_D_R	((P4IN&BIT1)+(P4IN&BIT2))
#define READ_ALL	((P4IN&BIT0)+(P4IN&BIT1)+(P4IN&BIT2))

#define FLAG_UP		BIT0
#define FLAG_DOWN 	BIT1
#define FLAG_RIGHT  BIT2
#define	FLAG_U_R	(BIT0+BIT2)
#define FLAG_D_R	(BIT1+BIT2)
#define	FLAG_ALL	(BIT0+BIT1+BIT2)
#define	FLAG_NONE	0

enum Direction
{
	UP = 1,//P6.4
	DOWN,  //P6.5
	RIGHT, //P6.6
	UP_RIGHT,
	DOWN_RIGHT,
	ALL,	 // 全高电平
	LIGHT,	 // 全低电平
};

typedef struct Point
{
	float x;
	float y;
}Point;

typedef struct Motor
{
	/**********电机运行速率（即定时器触发时间）为确定值 *********/
	bool   status ;        					//电机运行状态（true：运行中，false：停止）
	unsigned  long  number  ;		//运行脉冲数
	Dir    dir;									//旋转方向
}Motor;

void Motor_Init();
void Motor1_IO_Out( unsigned char data);
void Motor2_IO_Out(unsigned char data);
void Set_run_message(float x1, float y1, float x2, float y2);
void Timer_Motor_Init();
void Motor_Circle(void);
void get_circle_xy(int x,int y ,int r,int n );
void Motor_line(void);
void Work_PTP(float x1, float y1, float x2, float y2);
void set_correction(float Left_Put,float Left_Close,float Right_Put,float Right_Close);
void get_Quadrant( float x2, float y2);
void Error_correction(Quadrant quadrant);
void Motor_black();

#endif /* SRC_MOTOR_H_ */


