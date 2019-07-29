/*
 * my_ADC.c
 *
 *  Created on: 2019��7��9��
 *      Author: JOJO
 */

#include "my_ADC.h"

/*
 *˵������ʼ������Ҫ start_adc12()  ���ܽ��в���   ��
 * 			�����ṩstart ʱ����������жϣ�
 * 			stop  �ر��ж� ��
 * */
int adc12_init()
{
	  ADC12CTL0 = ADC12SHT02 + ADC12ON;        				 // Sampling time, ADC12 on
	  ADC12CTL1 = ADC12SHP + ADC12SSEL_1 ;                     // Use sampling timer   32KHZ
	  ADC12IE = 0x01;                          									 // Enable interrupt
	  ADC12CTL0 |= ADC12ENC;
	  P6SEL |= 0x01;                            									// P6.0 ADC option select
      return 0;
}

void start_adc12()
{
	 ADC12CTL0 |=ADC12SC;
}

void stop_adc12()
{
	ADC12IE = 0;
}

static  float  sfLightness[100];							//���Ȳ��� : L = -14 +1.82X     ������X��

static float sfAvg;
/******************************************************************************************************
 * ��       �ƣ�ADC12_ISR_HOOK
 * ��       �ܣ�ADCת����ɺ󴥷���д�����ݣ���������һ��AD����
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����null
 * ��       ������
 ******************************************************************************************************/
#pragma vector=ADC12_VECTOR
__interrupt void adc12_ISR_hook(void)
{
	static int siLightCount = 0;
	int iSum = 0;
	char i = 0;
	sfLightness[siLightCount++] = ADC12MEM0;    //ADC�����������
	if(siLightCount == 100)
	{
		siLightCount = 0;
		for(i;i<100;i++)
		{
			iSum+=sfLightness[i];
		}
		sfAvg = iSum/100.0;
	}
	start_adc12();
}


void Search_Light();
{

}
