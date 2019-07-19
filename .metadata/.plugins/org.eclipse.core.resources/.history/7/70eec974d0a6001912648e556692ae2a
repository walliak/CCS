#include "driverlib.h"
/****************************************
  	PA1 ->P3.3	PA2->P1.6 	PA3->P6.6		OUTPUT
	PB1 ->P6.1	PB2->P6.2	PB3->P6.3		INPUT
****************************************/
#define CLRPA1  P3OUT &= ~BIT3
#define SETPA1  P3OUT |= BIT3
#define	CLRPA2	P1OUT &= ~BIT6
#define SETPA2  P1OUT |= BIT6
#define	CLRPA3 	P6OUT &= ~BIT6
#define SETPA3  P6OUT |= BIT6

#define	READPB123	(P6IN&BIT1)+(P6IN&BIT2)+(P6IN&BIT3)
#define FLAGPB1		BIT2+BIT3
#define FLAGPB2		BIT1+BIT3
#define FLAGPB3		BIT1+BIT2

void KeyPort_Init ()
{
	P3DIR |= BIT3;
	P1DIR |= BIT6;
	P6DIR |= BIT6;
	//设置P6.1、P6.2、P6.3为输入方向
	P6DIR &=~(BIT1+BIT2+BIT3) ;
	P6REN |=(BIT1+BIT2+BIT3) ;
	P6OUT |=(BIT1+BIT2+BIT3);
}


/**********************************************************************************************************
* 函数名称：KeyScan
* 函数功能：按键扫描，返回0表示无键按下，1-9是正常返回
**********************************************************************************************************/
unsigned char KeyScan(void)
{
  unsigned long i;
  CLRPA1;
  CLRPA2;
  CLRPA3;
  if((BIT1+BIT2+BIT3)==READPB123)
	  return 0;
  for(i = 0;i < 12000;i ++);  // 有键按下，延时先 可修改
 // 扫描KEY1 - KEY3
  CLRPA1;
  SETPA2;
  SETPA3;
  if((BIT1+BIT2+BIT3)!=READPB123)
  {
    switch(READPB123)
    {
		case FLAGPB1:
		  return 1;
		case FLAGPB2:
		  return 2;
		case FLAGPB3:
		  return 3;
		default:
		  return 0;
    }
  } 
  // 扫描KEY4 - KEY6
  CLRPA2;
  SETPA1;
  SETPA3;
  if((BIT1+BIT2+BIT3)!= READPB123)
  {
	switch(READPB123)
    {
    case FLAGPB1:
      return 4;
    case FLAGPB2:
      return 5;
    case FLAGPB3:
      return 6;     
    default:
      return 0; 
    }
  }    

  // 扫描KEY7 - KEY9
  CLRPA3;
  SETPA1;
  SETPA2;
  if((BIT1+BIT2+BIT3)!= READPB123)
  {
    switch(READPB123)
    {
    case FLAGPB1:
      return 7;
    case FLAGPB2:
      return 8;
    case FLAGPB3:
      return 9;      
    default:
      return 0; 
    }
  }  
  return 0;
}
