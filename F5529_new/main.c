#include <key.h>
#include "led.h"
#include "lcd.h"
#include "sysclock.h"
#include "motor.h"
#include "MSP430F5529.h"
#include "compositeChars.h"

char switchFlag=0;
char str_P_x1[4],str_P_y1[4],str_P_x2[4],str_P_y2[4],str_P_r[4];

void Show(void);
void Converse(void);
void MCU_Init(void);

void main (void)



{
	char key=3,m2=5,m1=0,n2=5,n1=0;
	char flag_1=0,flag_2=0,flag_3=0;
	MCU_Init();
	 while(1)
		 {
		 	Show();
		 	key = KeyScan();
			if(key!=0)
			{
				switch(key)
				{
				 	case 1:	//两点连线
							function = 1;
							Converse();
							Clear();
							Show();
							/***************************/
							if(flag_1==1)
							{
								Work_PTP(P_x1+0.5,P_y1-2.5,P_x2+0.5,P_y2-2.5);
							}
							flag_1++;
							/**************************/
							Clear();
							break;
					case 2:	//循迹
							function = 2;
							Converse();
							Clear();
							Show();
							/***************************/
							 if(flag_2==1)
							 {
							 	Motor_black();
							 }
							 flag_2++;

							/**************************/
							Clear();
							break;
					case 3:	//圆
							function=3;
							Converse();
							Clear();
							Show();
							/***************************/
							if(flag_3==1)
							{
								Motor_Circle();
							}
							 flag_3++;
							/**************************/
							Clear();
							break;
					case 4://退出

							Converse();
							Clear();
							Show();
							/***************************/
							function=0,switchFlag=0;
							m2=5,m1=0,n2=5,n1=0;
							flag_1=0,flag_2=0,flag_3=0;
							/**************************/
							Clear();
							break;
					case 6://
							switch(function)
							{
								case 1:
								case 2:
								case 3:
										if(switchFlag%2==0)
										{
											if(m2>12)
											{
												m2=0;
											}
											P_x1=10*m2+m1;
											m2++;
										}
										else
										{
										  if(m2>12)
											{
												m2=0;
											}
											P_x2=10*m2+m1;
											m2++;
										}
										break;
								default: break;
							}
							Clear();
							Converse();
							break;
					case 7://
							switch(function)
							{
								case 1:
								case 2:
								case 3:
										if(switchFlag%2==0)
										{
											if(m1>9)
											{
												m1=0;
											}
											P_x1=10*m2+m1;
											m1++;
										}
										else
										{
										  if(m1>9)
											{
												m1=0;
											}
											P_x2=10*m2+m1;
											m1++;
										}
										break;
							}
							Clear();
							Converse();
							break;
					case 8://
							switch(function)
							{
								case 1:
								case 2:
										if(switchFlag%2==0)
										{
											if(n2>12)
											{
												n2=0;
											}
											P_y1=10*n2+n1;
											n2++;
										}
										else
										{
										  if(n2>12)
											{
												n2=0;
											}
											P_y2=10*n2+n1;
											n2++;
										}
										break;
								case 3:
										if(switchFlag%2==0)
										{
											if(n2>12)
											{
												n2=0;
											}
											P_y1=10*n2+n1;
											n2++;
										}
										else
										{
										  if(n2>12)
											{
												n2=0;
											}
											P_r=10*n2+n1;
											n2++;
										}
										break;
							}
							Clear();
							Converse();
							break;

					case 9://
							switch(function)
							{
								case 1:
								case 2:
										if(switchFlag%2==0)
										{
											if(n1>9)
											{
												n1=0;
											}
											P_y1=10*n2+n1;
											n1++;
										}
										else
										{
										  if(n1>9)
											{
												n1=0;
											}
											P_y2=10*n2+n1;
											n1++;
										}
										break;
								case 3:
										if(switchFlag%2==0)
										{
											if(n1>9)
											{
												n1=0;
											}
											P_y1=10*n2+n1;
											n1++;
										}
										else
										{
										  if(n1>9)
											{
												n1=0;
											}
											P_r=10*n2+n1;
											n1++;
										}
										break;
							}
							Clear();
							Converse();
							break;
					case 5://切换下一个坐标点
							if(switchFlag==10)
							{
								switchFlag=0;
							}
							switchFlag++;
							Converse();
							Clear();
							Show();
							break;
				}
			}
		 }
}

void Show(void)
{

	if(function==1)
	{
		DrawcharS("1.line",0,0);
		DrawcharS(" start",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
		DrawcharS(" end  ",2,1);DrawcharS(str_P_x2,2,8);DrawcharS(",",2,11);DrawcharS(str_P_y2,2,12);
	}
	else if(function==2)
	{
		DrawcharS("2.Straight",0,0);
		DrawcharS(" start",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
		DrawcharS(" end  ",2,1);DrawcharS(str_P_x2,2,8);DrawcharS(",",2,11);DrawcharS(str_P_y2,2,12);
	}
	else if(function==3)
	{
		DrawcharS("3.Circle",0,0);
		DrawcharS(" point",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
		DrawcharS(" raduis",2,1);DrawcharS(str_P_r,2,8);
	}
	else
	{
		DrawcharS("1.line",0,0);
		DrawcharS("2.Straight",1,0);
		DrawcharS("3.Circle",2,0);
	}

	if(function!=0)
	{
		if(switchFlag%2==0)
		{
			DrawcharS("*",1,0);
			DrawcharS("  ",2,0);
		}
		else
		{
			DrawcharS("*",2,0);
			DrawcharS("  ",1,0);
		}
	}

}

void Converse(void)
{
	itoa(P_x1,str_P_x1);
	itoa(P_x2,str_P_x2);
	itoa(P_y1,str_P_y1);
	itoa(P_y2,str_P_y2);
	itoa(P_r ,str_P_r);
}


void MCU_Init(void)
{
	WDTCTL=WDTPW+WDTHOLD; //关闭看门狗
	CLK_Init();
	LCDInit();
	LedInit();
	KeyPort_Init();
	Motor_Init();

	Clear();
	DrawcharS("Project-5",1,4);
	DrawcharS("5.1--now",2,4);
	Delay_ms(1000);
	Clear();
	_enable_interrupts();							//使能总中断

}
