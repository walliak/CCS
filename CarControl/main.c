#include <key.h>
#include "led.h"
#include "lcd.h"
#include "sysclock.h"
#include "motor.h"
#include "MSP430F5529.h"
#include "compositeChars.h"


//char switchFlag=0;
//char str_P_x1[4],str_P_y1[4],str_P_x2[4],str_P_y2[4],str_P_r[4];

void Show(void);
void Converse(void);
void MCU_Init(void);
void main (void)
{
	char key;
	MCU_Init();
	while(1)
	{
		key = KeyScan();
		if(key)
		{
			switch(key)
			{
				case 1:
					L1_Stop();
					L2_Stop();
					R1_Stop();
					R2_Stop();
					Delay_ms(200);
					L1_Forward();
					L2_Forward();
					R1_Forward();
					R2_Forward();
					LED1_HIGH;
					break;
				case 2:
					L1_Stop();
					L2_Stop();
					R1_Stop();
					R2_Stop();
					Delay_ms(200);
					L1_Backward();
					L2_Backward();
					R1_Backward();
					R2_Backward();
					LED1_LOW;
					break;
				case 3:
					Car_Forward(30,0);
					break;
				case 4:
					Car_Forward(40,0);
					break;
				case 5:
					Car_Forward(50,0);
					break;
				case 6:
					Car_Forward(60,0);
					break;
				case 7:
					Car_Forward(70,0);
					break;
				case 8:
					Car_Forward(80,0);
					break;
				case 9:
					Car_Forward(90,0);
					break;

			}
		}

	}

}

//void Show(void)
//{
//
//	if(function==1)
//	{
//		DrawcharS("1.line",0,0);
//		DrawcharS(" start",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
//		DrawcharS(" end  ",2,1);DrawcharS(str_P_x2,2,8);DrawcharS(",",2,11);DrawcharS(str_P_y2,2,12);
//	}
//	else if(function==2)
//	{
//		DrawcharS("2.Straight",0,0);
//		DrawcharS(" start",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
//		DrawcharS(" end  ",2,1);DrawcharS(str_P_x2,2,8);DrawcharS(",",2,11);DrawcharS(str_P_y2,2,12);
//	}
//	else if(function==3)
//	{
//		DrawcharS("3.Circle",0,0);
//		DrawcharS(" point",1,1);DrawcharS(str_P_x1,1,8);DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
//		DrawcharS(" raduis",2,1);DrawcharS(str_P_r,2,8);
//	}
//	else
//	{
//		DrawcharS("1.line",0,0);
//		DrawcharS("2.Straight",1,0);
//		DrawcharS("3.Circle",2,0);
//	}
//
//	if(function!=0)
//	{
//		if(switchFlag%2==0)
//		{
//			DrawcharS("*",1,0);
//			DrawcharS("  ",2,0);
//		}
//		else
//		{
//			DrawcharS("*",2,0);
//			DrawcharS("  ",1,0);
//		}
//	}
//
//}
//
//void Converse(void)
//{
//	itoa(P_x1,str_P_x1);
//	itoa(P_x2,str_P_x2);
//	itoa(P_y1,str_P_y1);
//	itoa(P_y2,str_P_y2);
//	itoa(P_r ,str_P_r);
//}
//

void MCU_Init(void)
{
	WDTCTL=WDTPW+WDTHOLD; //�رտ��Ź�
	CLK_Init();
	LCDInit();
	LedInit();
	KeyPort_Init();
	MotorPort_Init();
	PWM_Init();

	Clear();
	DrawcharS("Project-5",1,4);
	DrawcharS("5.1--now",2,4);
	Delay_ms(1000);
	Clear();
	_enable_interrupts();							//ʹ�����ж�

}