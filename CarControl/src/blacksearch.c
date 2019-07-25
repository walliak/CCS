/*
 * blacksearch.c
 *
 *  Created on: 2019年7月24日
 *      Author: Think
 */
#include "blacksearch.h"

/************************************************************
 *		红外传感器引脚配置
 *
 *		P8.1 -> 左边
 *		P8.2 -> 右边
 *
 *		模拟输入，上拉输入
 ************************************************************/
void SearchPort_Init()
{
	P8DIR &=~(BIT1+BIT2);
	P8REN |=(BIT1+BIT2) ;
	P8OUT |=(BIT1+BIT2);
}


void SearchBlack()
{
	switch(READ_ALL)
	{
		case(FLAG_LEFT):
				Car_Turn(5);
				break;
		case(FLAG_RIGHT):
				Car_Turn(5);
				break;
		default:
				Car_Forward(13,10);
				break;
	}
}

