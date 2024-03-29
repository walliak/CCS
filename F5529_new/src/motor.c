/*
 * motor.c
 *
 *  Created on: 2019年7月14日
 *      Author: JOJO
 */
#include "motor.h"
#include "math.h"
#include "MSP430F5529.h"
#include "led.h"
/*******************************************变量定义*********************************************/

//八拍	CCW = CounterClockWise ; CW = ClockWise
unsigned char  eightCCW[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09} ; //逆时钟旋转相序表
unsigned char  eightCW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表
//四拍
unsigned char  fourCCW[4]={0x01,0x08,0x04,0x02};
unsigned char  fourCW[4]={0x02,0x04,0x08,0x01};

//定点、直线、圆起始坐标
int P_x1=55,P_y1=80,P_x2=55,P_y2=20,P_r=25;
char function =0;

//循迹部分，起始坐标
float startPoint_x = 30,startPoint_y = 80;
float nextPoint_x,nextPoint_y;

// 左,右电机初始化
Motor motor_Left={FALSE,0};
Motor motor_Right = {FALSE,0};

//以圆心分四象限纠错
static 	Quadrant quadrant = FIR;
/********************************************************************************************************/


/*******************************************函数定义*****************************************************/
void Set_Next_Point(enum Direction direction)
{
	float up_dis=-0.2,down_dis=0.2,right_dis=0.2,del_1=0.05,del_2=-0.5;
	switch(direction)
	{
		case UP:	//
			nextPoint_x = startPoint_x;
			nextPoint_y = startPoint_y+up_dis;
			break;

		case DOWN:	//
			nextPoint_x = startPoint_x;
			nextPoint_y = startPoint_y+down_dis;
			break;

		case RIGHT:
			nextPoint_x = startPoint_x+right_dis;
			nextPoint_y = startPoint_y;
			break;

		case UP_RIGHT:
			nextPoint_x = startPoint_x+right_dis;
			nextPoint_y = startPoint_y+up_dis;
			break;

		case DOWN_RIGHT:
			nextPoint_x = startPoint_x+right_dis;
			nextPoint_y = startPoint_y+down_dis;
			break;

		case ALL: //
			nextPoint_x = startPoint_x;
			nextPoint_y = startPoint_y+up_dis;
			break;

		case LIGHT:	//
			nextPoint_x = startPoint_x+del_1;
			nextPoint_y = startPoint_y+del_2;
			break;
	}
}

void Timer0_Init()
{
	 TA0CCR0 =INITSPEED;
	 TA0CTL |=TASSEL_2+MC_1 ;//选择SCLK作为时钟，选用增模式，并开启中断
}


/**
 * 		Author: JOJO    19.7.15
 * 		参数: null
 * 		返回值: null
 * 		功能:  电机Io初始化   P1.2 P1.3 P1.4 P1.5      ||    P2.2   P2.3  P2.4  P2.5
 ****0*/
void Motor_Init()
{
	P1DIR  |= BIT2 + BIT3 +BIT4 +BIT5;   //输出模式
	P2DIR  |= BIT2 + BIT3 +BIT4 +BIT5;

	//输入模式 	P4.0 P4.1 P4.2 模拟输入 ,上拉输入。
	P4DIR &=~(BIT0+BIT1+BIT2);
	P4REN |=(BIT1+BIT2+BIT0) ;
	P4OUT |=(BIT1+BIT2+BIT0);
	Timer0_Init();
}


/**
 * 		Author: JOJO    19.7.15
 * 		参数: null
 * 		返回值: null
 * 		功能:  将相序表中输出至相应IO口
 * */
void Motor1_IO_Out( unsigned char data)
{
		P1OUT =0;
		P1OUT  |= (data << 2);   //左移两位至 P1.2
}


void Motor2_IO_Out(unsigned char data)
{
		P2OUT 	 = 0;
		P2OUT  |= ( data <<2);  //P2.2
}


/***************************************/
/**
 * 		Author: JOJO    19.7.15
 * 		参数: Point1(x1,y1)   Point2(x2,y2)
 * 		返回值: null
 * 		功能: 判断单次点到点时,左右电机需要转动的方向(dir)及脉冲数(number) ; 写入电机(Mortor)中
 * */
void Set_run_message(float x1, float y1, float x2, float y2)
{
	float a1,a2,b1,b2;
	a1 = sqrt(x1*x1+y1*y1);
	a2 = sqrt(x2*x2+y2*y2);
	b1 = sqrt((DISTANCE-x1)*(DISTANCE-x1)+y1*y1);
	b2 = sqrt((DISTANCE-x2)*(DISTANCE-x2)+y2*y2);

/******************将参数写入motor_Left,motor_Right 中******************************/

	if(a1>a2)//左边线缩短
	{
		motor_Left.status =TRUE;
		motor_Left.number = (long)((a1-a2)*4096*1.125/(CIRCUMFERENCE_LEFT));
		motor_Left.dir    =  FORWAED;
	}
	else    	 //左边线伸长
	{
		motor_Left.status =TRUE;
		motor_Left.number =(long)((a2-a1)*4096*1.125/(CIRCUMFERENCE_LEFT));
		motor_Left.dir    = REVERSE;
	}

	if(b1>b2) //右边线缩短
	{
		motor_Right.status = TRUE;
		motor_Right.number = (long)((b1-b2)*4096*1.065/(CIRCUMFERENCE_RIGHT));
		motor_Right.dir    =  FORWAED;
	}
	else	 	  //右边线伸长
	{
		motor_Right.status = TRUE;
		motor_Right.number = (long)((b2-b1)*4096*1.065/(CIRCUMFERENCE_RIGHT));
		motor_Right.dir    =  REVERSE ;
	}
	if(function==3)
	{
		Error_correction(quadrant);
	}
	OPENTIMA;						//定时器中断使能 ,电机开启
}

/******************定时器(控制电机速率)*********************
 *		注意:  定时器中断标志位不会自动清零
 * 		时钟信号:	SCLK
 * 		模式:		自增
 * 		分频:		默认1
 *
 *
 	TAxCTL	————定时器Ax的控制寄存器。

	TAxCCTLn————定时器Ax里的捕获比较单元n的控制寄存器，多了个C是Capture/Compare。

	TAxR	————定时器Ax的计数器，这个不归我们管。

	TAxCCRn	————定时器Ax里的捕获比较寄存器，用到这个捕获比较的时候直接写就行，或者是写CCR0。

	TAxIV	————定时器Ax的中断向量寄存器。进这个中断时查看就行，switch。

	TAxEX0	————定时器A扩增的寄存器，里面只有一个TAIDEX对时钟再分频，可以忽略。
 ***********************************************************/


/**
 * 		Author: JOJO    19.7.15
 * 		参数: null
 * 		返回值: null
 * 		功能:  输出一次电机脉冲 ;  判断单次点到点的过程是否执行完毕(Mortors_Status)
 * 		说明:  定时器中断函数 ;  64*64 = 4096  个脉冲为电机完整一圈
 * */
#pragma vector= TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
	TA0CTL &=~TAIFG;					//定时器中断标志位清零

	/*****根据左电机状态输出脉冲****/
	if(motor_Left.status  && (motor_Left.number>0) )
	{
			switch (motor_Left.dir)
			{
				case FORWAED  :	Motor1_IO_Out(eightCW[motor_Left.number%8]);   break;       //正转
				case REVERSE  :	Motor1_IO_Out(eightCCW[motor_Left.number%8]); break;		//反转
				default:	break;
			}
			motor_Left.number--;						//完成一次脉冲输出,待输出脉冲数自减一
	}
	if(motor_Left.number == 0)						//当待输出脉冲为0时,电机状态为关闭
			motor_Left.status =FALSE;

	/*****根据右电机状态输出脉冲****/
	if(motor_Right.status && (motor_Right.number>0))
	{
			switch (motor_Right.dir)
			{
				case FORWAED  :	Motor2_IO_Out(eightCW[motor_Right.number%8]);   break;
				case REVERSE  :	Motor2_IO_Out(eightCCW[motor_Right.number%8]);  break;
				default:	break;
			}
			motor_Right.number--;
	}
	if(motor_Right.number ==0)
				motor_Right.status = FALSE;

	if( !motor_Left.status && !motor_Right.status )
	LPM0_EXIT;		//退出低功耗

}


/****************************************************************************************/
void get_circle_xy(int x,int y ,int r,int n )
{
	int i = 1;
	float xx,yy;
	//第0个存放坐标原点，其后n个存放轨迹坐标
	// 输入已确定的四点坐标
	array_1[0].x = x;
	array_1[0].y = y;

	array_1[1].x = x;
	array_1[1].y = y - r;

	array_1[n/4+1].x = x - r;
	array_1[n/4+1].y = y;

	array_1[(n/2) + 1].x = x;
	array_1[(n/2) + 1].y = y + r;

	array_1[(3*n)/4+1].x = x + r;
	array_1[(3*n)/4+1].y = y;

	array_1[n+1].x = x;
	array_1[n+1].y = y-r;
	// 计算第一象限之间的点坐标，并赋值
	for( ;i<=(n/4)-1;i++){
		xx = r*cos((2*PI/n)*i) + x;
		yy = y - r*sin((2*PI/n)*i);
		//第一象限
		array_1[3*n/4 +1+ i].x = xx;
		array_1[3*n/4 +1+ i].y = yy;
		//第三象限
		array_1[n/4+1+i].x = 2*x - xx;
		array_1[n/4+1+i].y = 2*y - yy;
		//第二象限
		array_1[n/4+1- i].x = 2*x - xx;
		array_1[n/4+1- i].y = yy;
		//第四象限
		array_1[3*n/4 +1-i].x = xx;
		array_1[3*n/4 +1-i].y = 2*y - yy;
	}
}

/**
 * 		Author: JOJO    19.7.15
 * 		参数: Point1(x1,y1)   Point2(x2,y2)
 * 		返回值: null
 * 		功能: 实现点到点的电机控制
 * 		说明:
 * */
void Work_PTP(float x1, float y1, float x2, float y2)
{
	get_Quadrant(x2,y2);
	Set_run_message(x1,y1,x2,y2);
	LPM0 ;									//进入低功耗
	CLOSETIMA;							//关闭定时器
}

/*
@Description 直线点轨迹坐标
		   返回结构体数组指针
*/
void Get_line_xy(int x0,int y0,int x1,int y1,int n)
{
	float a,b;
	int i = 1;
	a = (x1-x0)/(n-1);
	b = (y1-y0)/(n-1);
	array_2[0].x = x0;
	array_2[0].y = y0;

	array_2[n-1].x = x1;
	array_2[n-1].y = y1;

	for(;i<n-1;i++)
	{
		array_2[i].x = x0+a*i;
		array_2[i].y = y0+b*i;
	}
}

//生成直线
void Motor_line(void)
{
	int n;
	float x1,y1,x2,y2;
	Get_line_xy(P_x1,P_y1,P_x2,P_y2,N2);
	for(n=0;n<N2-1;n++)
	{
	 	x1 = array_2[n].x;
		y1 = array_2[n].y;
		x2 = array_2[n+1].x;
		y2 = array_2[n+1].y;
		Work_PTP(x1, y1, x2, y2);
	}
}

//生成圆
void Motor_Circle(void)
{
	int n;
	float x1,y1,x2,y2;
	get_circle_xy(P_x1,P_y1,P_r,N1);
	for(n=0;n<N1+1;n++)
	{
		x1 = array_1[n].x;
		y1 = array_1[n].y;
		x2 = array_1[n+1].x;
		y2 = array_1[n+1].y;
		Work_PTP(x1, y1, x2, y2);
	}
}


enum Direction  next_Direction()
{
	switch (READ_ALL)
	{
		case FLAG_UP:
			return UP;
		case FLAG_DOWN:
			return DOWN;
		case FLAG_RIGHT:
			return RIGHT;
		case FLAG_U_R:
			return UP_RIGHT;
		case FLAG_D_R:
			return DOWN_RIGHT;
		case FLAG_ALL:
			return ALL;
		case FLAG_NONE:
			return LIGHT;
	}
	return LIGHT;
}

void Motor_black()
{
	char stopFlag=0;
	int number = 0;
	enum Direction working;
	while(stopFlag<=25)
	{
		working = next_Direction();
		number++;
		if(working == LIGHT)
		{
			stopFlag++;
		}
		Set_Next_Point(working);
		Work_PTP(startPoint_x,startPoint_y,nextPoint_x,nextPoint_y);
		startPoint_x = nextPoint_x;
		startPoint_y = nextPoint_y;
	}
}
//
/***************************************/
/**
 * 		Author: JOJO
 * 		参数: 	float Left_Put			(左电机伸长时脉冲调整比例)
 * 					float Left_Close      (左电机收缩时脉冲调整比例)
 * 					float Right_Put     float Right_Close
 * 		返回值: null
 * 		功能:		根据实际情况调整电机不同情况下(正反转)输出的脉冲数
 * 		用法:		REVERSE : 伸长			 FORWAED: 收缩
 * 					不调整脉冲数:	set_correction(1,1,1,1)
 * 					左电机收缩不足: set_correction(1,1.01,1,1)
 *
 * 		说明:motor_Right   motor_Left为定义好的静态全局变量
 * */
void set_correction(float Left_Put,float Left_Close,float Right_Put,float Right_Close)
{
	if(motor_Right.dir ==FORWAED )						//右电机逆时针旋转(收缩)
			motor_Right.number *=Right_Close;
	else																		//右电机顺时针旋转(伸长)
			motor_Right.number *=Right_Put;

	if(motor_Left.dir == REVERSE)							//左电机顺时针旋转(伸长)
			motor_Left.number *=Left_Put;
	else																		//左电机逆时针旋转(收缩)
			motor_Left.number *=Left_Close;
}
/**
 * 		Author: JOJO    19.7.17
 * 		参数: Quadrant quadrant
 * 		返回值: null
 * 		功能:  根据点对应的象限,对电机脉冲数进行修正
 * */
void Error_correction(Quadrant quadrant)
{
		switch(quadrant)
		{
		case ZERO:			set_correction(1,1,1,1);     		break;

		case FIR:			set_correction(1,1,1.115,0.94);		break;

		case SEC:			set_correction(1,0.915,1.02,1);		break;

		case TIR:			set_correction(0.98,0.998,1.01,1.04);   break;

		case  FOR:			set_correction(0.98,1.015,1.01,1.04); 	break;
		}
}

/**
 * 		Author: JOJO    19.7.17
 * 		参数: float x2, float y2
 * 		返回值: null
 * 		功能:  获得下一点对应的象限值
 * */
void get_Quadrant( float x2, float y2)
{
	if((x2 > P_x1)&&(y2 <= P_y1 ))
		quadrant = FIR;							//第一象限
	if((x2 >= P_x1)&&(y2 > P_y1 ))
		quadrant = FOR;							//第四象限
	if((x2 <= P_x1)&&(y2 <= P_y1))
		quadrant = SEC;							//第二象限
	if(x2 <P_x1 && y2> P_y1)
		quadrant = TIR;							//第三象限

	if(x2 == P_x1 && y2 == P_y1-P_r)
		quadrant = ZERO;						//圆点出发
}



