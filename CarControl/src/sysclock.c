/*
 * sysclock.c
 *
 *  Created on: 2019年7月19日
 *      Author: Think
 */

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
	相关时钟线及时钟源的引脚
	ACLK  -> P1.0		XT2IN  ->P5.2
	SMCLK -> P2.2		XT2OUT ->P5.3
	MCLK  -> P7.7		XIN	   ->P5.4
						XOUT   ->P5.5

*****************************************************/
void CLK_Init(void) //系统时钟配置
{
    WDTCTL = WDTPW+WDTHOLD;

    P7SEL |= BIT7; 			//MCLK
    P7DIR |= BIT7;
    P5SEL |= BIT4|BIT5;

    UCSCTL6 |= XCAP_3;
    UCSCTL6 &= ~XT1OFF;//打开 XT1，否则 XT1LFOFFG 可能报错

    SetVcoreUp(3); 			//提高 Vcore 电压到最高级，以满足倍频需求。该函数位于HAL_PMM.H 中。
    __bis_SR_register(SCG0);//该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时 MCLK 暂停工作

    UCSCTL0 = 0; 			//先清零，FLL 运行时，该寄存器系统会自动配置，不用管
    UCSCTL1 = DCORSEL_5;
    UCSCTL2 = FLLD_1 |380;	//FLLD=1,FLLN=380,则频率为2*（380+1）*32.768=24.969MHZ

    __bic_SR_register(SCG0);
    __delay_cycles(782000);//系统自带的精确延时，单位 us
    while(SFRIFG1 & OFIFG)
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;
    }
    UCSCTL4 &=~(SELS_7|SELM_7);				//// 先将相应控制位清零
    UCSCTL4 |= SELS__DCOCLK|SELM__DCOCLK;	//// SMCLK MCLK 均选择DCOCLK;
}

void Mydelayms(int time)
{	int i;
	for(i=0;i<time;i++)
	{
		Delay_ms(1);
	}
}


