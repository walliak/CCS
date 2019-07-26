#include <key.h>
#include "led.h"
#include "lcd.h"
#include "sysclock.h"
#include "motor.h"
#include "MSP430F5529.h"
#include "compositeChars.h"
#include "blacksearch.h"
#include "metal.h"
#include "hcsr04.h"
#include <stdio.h>


void Show(void);
void MCU_Init(void);

void main (void)
{
	char key,i;
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
						while(1)
						{
							SearchBlack();
						}
				case 2:
						Car_Forward(50,10*1000);
						break;
				case 3:
						Car_Spinleft(95,1000);
						break;
				case 4:
						for(i=0;i<5;i++)
						Car_Spinleft(95,1000);
						break;
				case 5:
						break;
				default: break;
			}
		}

	}

}

void Show(void)
{
	char str_T[8],str_M[8];
	sprintf(str_T,"%d",second);
	sprintf(str_M,"%d",Metal_Num);
	DrawcharS(" Time",1,1); DrawcharS(str_T,1,7);
	DrawcharS(" Dista",1,1);
	DrawcharS(" Metal",3,1);DrawcharS(str_M,3,7);

}


void MCU_Init(void)
{
	WDTCTL=WDTPW+WDTHOLD; //关闭看门狗
	CLK_Init();
	LCDInit();
	LedInit();
	Metal_Detect_Init();
	KeyPort_Init();
	MotorPort_Init();
	PWM_Init();
	pwm_catch_init();
	SearchPort_Init();

	Clear();
	DrawcharS("Project-5",1,4);
	DrawcharS("5.1--now",2,4);
	Delay_ms(1000);
	Clear();
	DrawcharS("	Car Contol ",0,0);
	_enable_interrupts();							//使能总中断

}
