/*
 * my_ADC.c
 *
 *  Created on: 2019年7月9日
 *      Author: JOJO
 */

#include "my_ADC.h"

/*
 *说明：初始化后需要 start_adc12()  才能进行采样   ；
 * 			当不提供start 时，不会进入中断；
 * 			stop  关闭中断 ；
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

static  float  sfLightness[100];							//亮度参数 : L = -14 +1.82X     【距离X】

static float sfAvg;
/******************************************************************************************************
 * 名       称：ADC12_ISR_HOOK
 * 功       能：ADC转换完成后触发，写入数据，并开启下一次AD采样
 * 入口参数：无
 * 出口参数：无
 * 说       明：null
 * 范       例：无
 ******************************************************************************************************/
#pragma vector=ADC12_VECTOR
__interrupt void adc12_ISR_hook(void)
{
	static int siLightCount = 0;
	int iSum = 0;
	char i = 0;
	sfLightness[siLightCount++] = ADC12MEM0;    //ADC结果存入数组
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

