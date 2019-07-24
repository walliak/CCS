/*
 * sysclock.c
 *
 *  Created on: 2019��7��19��
 *      Author: Think
 */
#include "MSP430F5529.h"
#include "sysclock.h"
void SetVcoreUp (unsigned int level)
 {
     // Open PMM registers for write
     PMMCTL0_H = PMMPW_H;
     // Set SVS/SVM high side new level
     SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
     // Set SVM low side to new level
     SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
     // Wait till SVM is settled
     while ((PMMIFG & SVSMLDLYIFG) == 0);
    // Clear already set flags
     PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
     // Set VCore to new level
     PMMCTL0_L = PMMCOREV0 * level;
     // Wait till new level reached
     if ((PMMIFG & SVMLIFG))
     while ((PMMIFG & SVMLVLRIFG) == 0);
     // Set SVS/SVM low side to new level
     SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
     // Lock PMM registers for write access
     PMMCTL0_H = 0x00;
 }


/*****************************************************
	���ʱ���߼�ʱ��Դ������
	ACLK  -> P1.0		XT2IN  ->P5.2
	SMCLK -> P2.2		XT2OUT ->P5.3
	MCLK  -> P7.7		XIN	   ->P5.4
						XOUT   ->P5.5

*****************************************************/
void CLK_Init(void) //ϵͳʱ������
{
    WDTCTL = WDTPW+WDTHOLD;

    P7SEL |= BIT7; 			//MCLK
    P7DIR |= BIT7;
    P5SEL |= BIT4|BIT5;

    UCSCTL6 |= XCAP_3;
    UCSCTL6 &= ~XT1OFF;//�� XT1������ XT1LFOFFG ���ܱ���

    SetVcoreUp(3); 			//��� Vcore ��ѹ����߼��������㱶Ƶ���󡣸ú���λ��HAL_PMM.H �С�
    __bis_SR_register(SCG0);//���﷨Ϊ�̶���ʽ����Ϊ�������ڵı�����λ��SCG0��ϵͳ����ģʽ�йأ���ʱ MCLK ��ͣ����

    UCSCTL0 = 0; 			//�����㣬FLL ����ʱ���üĴ���ϵͳ���Զ����ã����ù�
    UCSCTL1 = DCORSEL_5;
    UCSCTL2 = FLLD_1 |380;	//FLLD=1,FLLN=380,��Ƶ��Ϊ2*��380+1��*32.768=24.969MHZ

    __bic_SR_register(SCG0);
    __delay_cycles(782000);//ϵͳ�Դ��ľ�ȷ��ʱ����λ us
    while(SFRIFG1 & OFIFG)
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;
    }
    UCSCTL4 &=~(SELS_7|SELM_7);				//// �Ƚ���Ӧ����λ����
    UCSCTL4 |= SELS__DCOCLK|SELM__DCOCLK;	//// SMCLK MCLK ��ѡ��DCOCLK;
}

void Mydelayms(int time)
{	int i;
	for(i=0;i<time;i++)
	{
		Delay_ms(1);
	}
}

