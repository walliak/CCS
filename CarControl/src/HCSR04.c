/*
 * HCSR04.c
 *
 *  Created on: 2019��7��25��
 *      Author: JOJO
 */

#include "HCSR04.h"

static long period[5];									//��ž�������
static int  avg = 0;
/*
 * ˵��:
 *			    _________
 * 			__|	          |____________   ECON�źŵĸߵ�ƽ�����������������ص�ʱ��
 * 			���ߵ�ƽ�ĳ���ʱ��������ܳ���һ������ʱ��(�ô�ΪTA2CCTL0)������ [65535]
 * 			OutTime ��Ϊ"����" �����¼�������, ���ݴ���ʱ���ò��ֲ���.
 *
 * */
static int  OutTime = 0;								//���ʱ��Ĵ���

/*
 * PWM�� ;����ͨ��  ��ʼ��
 * ����:
 * 			1. PWM��(TA2CCTL1)    [ P2.4��� ]   ΪHC-SR04�ṩ�����ź� (�ߵ�ƽ20us)
 * 			2. ����ͨ��( TA2CCTL2)  [ P2.5��� ]   �����HC-SR04����������
 * 				�����ز�����½��ز�������� (����ߵ�ƽ)
 * */
void pwm_catch_init()
{
		 P2OUT &=~BIT5;			//����  IO����
		 P2SEL  |= BIT5;

		 P2DIR |= BIT4;				//PWM IO�����
		 P2SEL |= BIT4;

		 TA2CTL = 0;
		 TA2CTL  |=  TASSEL_2 + ID_0 + MC_2+ TACLR + TAIE ;				//SMCLK ; ������ģʽ
		 TA2CCTL1 |= OUTMOD_7;																//PWM

		 TA2CCR1 = 500;				// ʱ��Ϊ25M,  500 ��������Ϊ20us

		 TA2CCTL2 |= CCIE + CM_1 +SCS + CAP +CCIS_0;	//����ͨ��,��ʼΪ�����ز���
		 TA2CCTL2 &=~BIT4;		//��ֹ����ͨ���ж�
}

// �������ݵĴ���
void Deal_Distance()
{
//	int avg;
	avg = (period[0] + period[1] +period[2] +period[3] +period[4])/5;
}

/*
 * �����¼��Ĵ���
 * ����:
 * 			1. ����������ز���,������ʱ������ֵ����,��תΪ�½��ز���,�ȴ���һ�β����ж�
 * 			2. ������½��ز���,��ȡ������ֵ  [TA2CCR2] , �������ʱ��,���һ�ξ���Ĳɼ�
 * 			3. �Բɼ����ľ������ݽ��д���
 * */
void event_Catch()
{
	static int  arr_num =0;
	static int  count_Lcd_num =0;

	switch((TA2CCTL2 & CM_2) )		//�ж��Ƿ�Ϊ�½���
			{
				case 0 :								//������
					TA2CCTL2 &=~CM_1;
					TA2CCTL2  |=CM_2;		   			//��תΪ�½��ش���
					TA2R = 0;						   	//��ռ���ֵ
					OutTime = 0;
					break;

				default:								//�½���
					period[arr_num] = (TA2CCR2 + OutTime*65535)/(25*58);		// ʱ��Ƶ��25M ,  ���� (cm) = �ߵ�ƽʱ�� (us)  /  58
					if(period[arr_num]>400 || period[arr_num]<=0 )						// ����ɼ������ݲ�����, ����
						{
							arr_num=arr_num-1;
						}
					TA2CCTL2 &=~CM_2;
					TA2CCTL2  |=CM_1;					//��תΪ�����ش���
					 OutTime = 0;
					arr_num++;
					break;
			}

		if(arr_num == 5)								//���ɼ���5�ξ�������
			{
				arr_num=0;
				avg = (period[0] + period[1] +period[2] +period[3] +period[4])/5;
				if(count_Lcd_num++ == 30)				//LCD ����ʾ
				{
					count_Lcd_num=0;
					 Deal_Distance();
				}
			}

}

void Car_Avoid(void)
{
//	char Go_on = 0;
	if(avg<=30)
	{
		Car_Spinleft(95,1000);
	}


}
/*
 * �����������½���ʱ�����ж�
 * */
#pragma vector=TIMER2_A1_VECTOR
__interrupt void Timer2_A1 (void)
{
	TA2CCTL1 &=~TAIFG;
	switch(TA2IV)							//���ж�Դ�����ж�
	{
		case TA2IV_TACCR2:					//����ͨ��2�ж�
					event_Catch(); break;

		case TA2IV_TAIFG:					//����ʱ������ж�
					OutTime++; break;

		default: break;
	}
}