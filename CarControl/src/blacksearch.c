/*
 * blacksearch.c
 *
 *  Created on: 2019��7��24��
 *      Author: Think
 */
#include "blacksearch.h"

/************************************************************
 *		���⴫������������
 *
 *		P8.1 -> ���
 *		P8.2 -> �ұ�
 *
 *		ģ�����룬��������
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
