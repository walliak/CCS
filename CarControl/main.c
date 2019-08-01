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
#include "speedcatch.h"
#include <stdio.h>
#include "my_adc.h"

int  Show(void);
void MCU_Init(void);

void main (void)
{
	MCU_Init();
	MODE = TRACE;
	while(1)
	{

		Show();

		switch(MODE)
		{
		case TRACE:
				Car_SearchBlack();	//��ѯ��ʽ
			break;
		case AVOID:
				Car_AvoidBlock();
			break;
		case LIGHT:
				Car_SearchLight();
			break;
		case STOP:
				Car_Brake();
			break;
		}
	}

}

int Show(void)
{
	char str_T[8],str_D[8],str_M[8];
	static int siSaveTime;
	if(siSaveTime  == second)
	{
		siSaveTime = second;
		return 0;
	}
	sprintf(str_T,"%d",second);
	sprintf(str_D,"%d",iMetalDistance);
	sprintf(str_M,"%d",Metal_Num);
	Clear();
	DrawcharS("MODE ",0,1);
	DrawcharS("Time ",1,1);DrawcharS(str_T,1,7);
	DrawcharS("Dista",2,1);DrawcharS(str_D,2,7);
	DrawcharS("Metal",3,1);DrawcharS(str_M,3,7);
	switch(MODE)
	{
		case TRACE:
			DrawcharS("1",0,7);
				break;
		case AVOID:
			DrawcharS("2",0,7);
				break;
		case LIGHT:
			DrawcharS("3",0,7);
		case STOP:
			DrawcharS("4",0,7);
	}
	siSaveTime = second;
	return 1;
}

void MCU_Init(void)
{
	WDTCTL=WDTPW+WDTHOLD; //�رտ��Ź�
	CLK_Init();
	LCDInit();
	LedInit();
	KeyPort_Init();

	MotorPort_Init();
	PWM_Init();			//�����ʼ��
	Metal_Detect_Init();
	pwm_catch_init();   //������ģ���ʼ��

	SearchPort_Init();	//����Թ�ѭ��ģ���ʼ��


	Clear();
	DrawcharS("Car-Control",1,4);
	DrawcharS("-----------",2,4);
	Delay_ms(1000);
	Clear();
	_enable_interrupts();							//ʹ�����ж�

}
