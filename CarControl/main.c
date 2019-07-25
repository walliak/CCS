#include <key.h>
#include "led.h"
#include "lcd.h"
#include "sysclock.h"
#include "motor.h"
#include "MSP430F5529.h"
#include "compositeChars.h"
#include "blacksearch.h"

#define sec 1000

char str_L[4],str_R[4];

void Show(void);
void Converse(void);
void MCU_Init(void);
void fix(void);

void main (void)
{
	char key;
	MCU_Init();
	while(1)
	{
		Show();
		key = KeyScan();
		if(key)
		{
			switch(key)
			{
				case 1:
						Show();
						while(1)
						{
							SearchBlack();
						}
				case 2:
						Show();
						Car_Turn(3*sec);
						break;
				case 3:
						Show();
						Car_Turn(3*sec);
						break;
				case 4:
						Clear();
						Turn_time+=5;
						fix();

						Converse();
						Clear();
						break;
				case 5:
						Clear();
						Turn_time-=5;
						fix();
						Converse();
						Clear();
						break;
				case 6:

					Clear();
					L_speed +=5;
					fix();

					Converse();
					Clear();
					break;
				case 7:

					Clear();
					L_speed -=5;
					fix();

					Converse();
					Clear();
					break;
				case 8:

					Clear();
					R_speed +=5;
					fix();

					Converse();
					Clear();
					break;
				case 9:

					Clear();
					R_speed -=5;
					fix();
					Converse();
					Clear();
					break;
			}
		}

	}

}

void fix(void)
{
	if(L_speed<0||R_speed<0||Turn_time<0)
	{
		L_speed = 0;
		R_speed = 0;
		Turn_time = 0;
	}
}
 void Show(void)
{
		DrawcharS("Yes ,fix!!!",0,0);
		DrawcharS(" L_s",1,1);DrawcharS(str_L,1,8);//DrawcharS(",",1,11);DrawcharS(str_P_y1,1,12);
		DrawcharS(" R_s",2,1);DrawcharS(str_R,2,8);//DrawcharS(",",2,11);DrawcharS(str_P_y2,2,12);
		DrawcharS(" Time",3,1);DrawcharS(str_R,3,8);
}

void Converse(void)
{
	itoa(L_speed,str_L);
	itoa(R_speed,str_R);
}


void MCU_Init(void)
{
	WDTCTL=WDTPW+WDTHOLD; //关闭看门狗
	CLK_Init();
	LCDInit();
	LedInit();
	KeyPort_Init();
	MotorPort_Init();
	PWM_Init();
	SearchPort_Init();

	Clear();
	DrawcharS("Project-5",1,4);
	DrawcharS("5.1--now",2,4);
	Delay_ms(1000);
	Clear();
	_enable_interrupts();							//使能总中断

}
