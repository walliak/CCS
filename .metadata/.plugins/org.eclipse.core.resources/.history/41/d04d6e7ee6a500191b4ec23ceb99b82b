#include "driverlib.h"
#include <key.h>
#include "led.h"
#include "lcd.h"

void delay(int ms)
{
  int i = 0,j=0;
  for(;i<500;i++)
  {
    for(j = 0;j<ms;j++);
  }
}

void main (void)
{

	unsigned  key;

	WDTCTL=WDTPW+WDTHOLD; //关闭看门狗

	newLCDInit();
	LedInit();
	KeyPort_Init();

	Clear();
	LCDWrite(W_CMD,0xA7);	  //反显命令
	DrawcharS("00:00:00",1,4);
	delay(2000);
	Clear();

	while(1)
	{
		key = KeyScan();
		if(key!=0)
		{
			switch(key)
			{
			case 1:
				P1OUT |= BIT0;
				break;
			case  2:
				P1OUT&=~BIT0;
				break;
			case 3:
				P4OUT |= BIT7;
				break;
			case 4:
				P4OUT&=~BIT7;
				break;
			case 5:
				P1OUT |= BIT0;
				break;
			case 6:
				P1OUT&=~BIT0;
				break;
			case 7:
				P4OUT |= BIT7;
				break;
			case 8:
				P4OUT&=~BIT7;
				break;
			default:
				break;
			}
		}
	}
}
