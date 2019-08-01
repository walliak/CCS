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
	  ADC12CTL1 = ADC12SHP + ADC12SSEL_1 ;                   // Use sampling timer 32KHZ
	  ADC12CTL0 |= ADC12ENC+ADC12SC;						 // Enable conversion and start conversion
	  P6SEL |= BIT0 + BIT6;                            		 // P6.0 ADC option select
	  ADC12IE = 0x01;                          				 // Enable interrupt
      return 0;
}

void Start_ADC12IT()
{
	 ADC12IE = 1;
}

void Stop_ADC12IT()
{
	ADC12IE = 0;
}

static  int  siLightness[N_ADC];							//���Ȳ��� : L = -14 +1.82X     ������X��

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
	siLightness[siLightCount++] = ADC12MEM0;    //ADC�����������
	if(siLightCount == N_ADC)
	{
		siLightCount = 0;
		Stop_ADC12IT();
	}
}

void Car_SearchLight()
{

}

/***********************************
 * 	�Բ����õ��Ĺ�ǿ����
 * 	ȥ�����ֵ����Сֵ������ƽ����
 *
 *********************************/

int filter()
{
   char count,i,j;
   int  sum=0,temp=0;
   for (j=0;j<N_ADC-1;j++)
   {
      for (i=0;i<N_ADC-j;i++)
      {
         if ( siLightness[i]>siLightness[i+1] )
         {
            temp = siLightness[i];
            siLightness[i] = siLightness[i+1];
            siLightness[i+1] = temp;
         }
      }
   }
   for(count=1;count<N_ADC-1;count++)
      sum += siLightness[count];
   return (int)(sum/(N_ADC-2));
}
